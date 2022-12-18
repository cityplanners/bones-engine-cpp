#include "bones/platform/window.h"

using namespace std;

namespace BONES {
    void Window::initWindow() {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(HEIGHT, WIDTH, "Vulkan window", nullptr, nullptr);

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

        // get list of required extensions
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        cout << glfwExtensionCount << " extensions required\n";

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            cout << i+1 << " " << glfwExtensions[i] << '\n';
        }

        // Allocate an array to hold the extension details
        vector<VkExtensionProperties> extensions(extensionCount);

        // Retrieve a list of supported extensions
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        cout << "available extensions:\n";

        for (const auto& extension : extensions) {
            cout << '\t' << extension.extensionName << '\n';
        }

        // Check if required extensions are included in the list of
        // supported extensions
        checkIfRequiredExtensionsAreSupported(glfwExtensionCount, glfwExtensions, extensions);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            throw runtime_error("failed to create Vulkan instance!");
        }
    }

    void Window::checkIfRequiredExtensionsAreSupported(uint32_t extensionCount, const char** glfwExtensions, vector<VkExtensionProperties> extensions){
        for (const auto& extension : extensions) {
            bool found = false;
            for (uint32_t i = 0; i < extensionCount; i++) {
                if (strcmp(extension.extensionName, glfwExtensions[i])) {
                    found = true;
                    break;
                }
            }

            if (!found) throw runtime_error("required extension not supported!");
        }
    }

    void Window::mainLoop() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void Window::cleanup() {

        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();

    }
}
