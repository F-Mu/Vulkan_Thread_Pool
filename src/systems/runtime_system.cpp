#include "runtime_system.hpp"
#include "../global/global_context.hpp"
#include "../resources/game_object_manager.hpp"
#include <cmath>

namespace crp {
    RuntimeSystem::RuntimeSystem(CrpDevice &crpDevice) :
            crpDevice{crpDevice},
            taskQueueSystem{std::make_shared<TaskQueueSystem>(crpDevice)},
            threadPoolSystem{std::make_shared<ThreadPoolSystem>(crpDevice)},
            tasksInQueue{taskQueueSystem->tasksInQueue},
            tasksWait{taskQueueSystem->tasksWait},
            tasksRun{taskQueueSystem->tasksRun} {
        threadPoolSystem->threadsInit(taskQueueSystem->tasksInQueue);
        auto RuntimeRect = CrpGameObject::makeRectangle(crpDevice,
                                                        x, y, z, w, false);
        id = RuntimeRect.getId();
        globalContext.gameObjectManager->gameObjects.emplace(RuntimeRect.getId(), std::move(RuntimeRect));

        float mid = (left + right) / 2;
        points.resize(THREAD_NUM);
        float hCut = (down - up) / float(THREAD_NUM);
        float yFirst = (up + hCut + up) / 2;
        for (int i = 0; i < THREAD_NUM; ++i) {
            points[i] = {mid, yFirst + hCut * i, THREAD_LAYER};
        }
    }

    void RuntimeSystem::tick(FrameInfo &frameInfo) {
        taskQueueSystem->tick(frameInfo);
        threadPoolSystem->tick(frameInfo);
        if (!taskQueueSystem->isSorted())return;
//        std::cout<<"#"<<std::endl;
//        if(tasksInQueue)
//        PRINT(taskQueueSystem->points[0]);
//        PRINT(tasksInQueue.front().center);
        if (threadPoolSystem->availableNum() != 0)
            threadPoolSystem->start.notify_one();
    }

    void RuntimeSystem::roundTick() {
        taskQueueSystem->roundTick();
        threadPoolSystem->roundTick();
    }

    void RuntimeSystem::addTask() {

    }

    void RuntimeSystem::clear() {
        threadPoolSystem->clear();
        threadPoolSystem.reset();
        taskQueueSystem.reset();
    }

}
