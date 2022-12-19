#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <optional>

using namespace std;

namespace BONES {
    class Window {
    public:
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
        GLFWwindow* window;
    private:
        const uint32_t WIDTH = 600;
        const uint32_t HEIGHT = 800;

        struct QueueFamilyIndices {
            optional<uint32_t> graphicsFamily;

            bool isComplete() {
                return graphicsFamily.has_value();
            }
        };

        const vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        void createInstance();
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void pickPhysicalDevice();
        int rateDeviceSuitability(VkPhysicalDevice device);
        void checkIfRequiredExtensionsAreSupported(uint32_t extensionCount, const char** glfwExtensions, vector<VkExtensionProperties> extensions);
        bool checkValidationLayerSupport();
        vector<const char*> getRequiredExtensions();
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
        void setupDebugMessenger();
    };
}
