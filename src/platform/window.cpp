#include "bones/platform/window.h"

namespace BONES {
    void Window::initWindow() {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(HEIGHT, WIDTH, "Vulkan window", nullptr, nullptr);

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported\n";

        glm::mat4 matrix;
        glm::vec4 vec;
        auto test = matrix * vec;

    };

    void Window::initVulkan() {
        createInstance();
    };

    void Window::createInstance() {
        // Optional struct with application info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Bones Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Required struct
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create Vulkan instance!");
        }
    }

    void Window::mainLoop() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void Window::cleanup() {

        glfwDestroyWindow(window);

        glfwTerminate();

    }
}
