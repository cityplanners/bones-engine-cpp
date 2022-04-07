cmake_minimum_required(VERSION 3.10)

project(bones VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_library(${PROJECT_NAME} src/engine.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
    PRIVATE
        ${Vulkan_INCLUDE_DIRS}
        glfw
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        glm::glm
    PRIVATE
        ${GLM_LIBRARIES}
        ${Vulkan_LIBRARIES}
        glfw
)