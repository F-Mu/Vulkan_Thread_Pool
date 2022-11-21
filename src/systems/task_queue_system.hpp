#pragma once

#include "../crp_device.hpp"
#include "../core/macro.hpp"
#include "../resources/game_object_manager.hpp"
#include "../core/rectangle.hpp"
#include "../crp_frame_info.hpp"
#include <glm/glm.hpp>

namespace crp {
    class TaskQueueSystem {
    public:
        TaskQueueSystem(CrpDevice &crpDevice, const std::shared_ptr<GameObjectManager> &manager);

        void addMoveTask(Rectangle &thread, glm::vec3 &point);

        void addDeleteTask(Rectangle &thread);

        void tick(FrameInfo &frameInfo);

        std::vector<glm::vec3> points;
        std::vector<Rectangle> tasks;
        std::vector<TaskToMove> moveTasks;
        std::vector<std::pair<GameObjectManager::id_t, float>> deleteTasks;
        std::vector<GameObjectManager::id_t>shouldDelete;
    private:
        float up = -1.1f, down = 1.1f, left = 1.f, right = 1.5f;
        glm::vec3 x{left, up, QUEUE_LAYER}, y{right, up, QUEUE_LAYER}, z{left, down, QUEUE_LAYER}, w{right, down,
                                                                                                     QUEUE_LAYER};
        GameObjectManager::id_t id;
    };
}
