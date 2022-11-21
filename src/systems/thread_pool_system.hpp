#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "../crp_game_obejct.hpp"
#include "../core/macro.hpp"
#include "../resources/game_object_manager.hpp"
#include "../crp_frame_info.hpp"
#include "../core/rectangle.hpp"

namespace crp {

    class ThreadPoolSystem {
    public:
        ThreadPoolSystem(CrpDevice &crpDevice, const std::shared_ptr<GameObjectManager> &manager);

        void addMoveTask(Rectangle &thread, glm::vec3 &point);

        void tick(FrameInfo &frameInfo);

        std::vector<glm::vec3> points;
        std::vector<Rectangle> threads;
        std::vector<TaskToMove> moveTasks;
    private:
        float up = -1.1f, down = 1.1f, left = -1.5f, right = -1.0f;
        glm::vec3 x{left, up, QUEUE_LAYER}, y{right, up, QUEUE_LAYER}, z{left, down, QUEUE_LAYER}, w{right, down,
                                                                                                     QUEUE_LAYER};
        GameObjectManager::id_t id;
    };
}