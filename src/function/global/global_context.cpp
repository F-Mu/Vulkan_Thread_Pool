#include "global_context.hpp"

namespace crp {
    class CrpDevice;

    GlobalContext globalContext;

    void GlobalContext::startEngine() {
        windowSystem = std::make_shared<WindowSystem>();
        WindowCreateInfo window_create_info;
        windowSystem->initialize(window_create_info);

        device = std::make_shared<CrpDevice>(*windowSystem);
        renderSystem = std::make_shared<RenderSystem>(*windowSystem, *device);
        globalResources = std::make_shared<GlobalResources>(*device);
        simpleRenderPass = std::make_shared<SimpleRenderPass>(*device,
                                                              renderSystem->getSwapChainRenderPass(),
                                                              globalResources->globalSetLayout->getDescriptorSetLayout());
        gameObjectManager = std::make_shared<GameObjectManager>();
        runTimeSystem = std::make_shared<RuntimeSystem>();
    }

    void GlobalContext::shutdownEngine() {
        vkDeviceWaitIdle(device->device());
        runTimeSystem->clear();
        runTimeSystem.reset();
        gameObjectManager.reset();
        simpleRenderPass.reset();
        globalResources->clear();
        globalResources.reset();
        renderSystem.reset();
        device.reset();
        windowSystem.reset();
    }

}