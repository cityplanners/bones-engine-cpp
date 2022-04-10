#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

namespace BONES {
    class Window {
    public:
        void InitWindow();
        void MainLoop();
        void Cleanup();
        GLFWwindow* window;
    private:
        const uint32_t WIDTH = 600;
        const uint32_t HEIGHT = 800;
    };
}