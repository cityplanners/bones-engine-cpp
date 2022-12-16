cmake_minimum_required(VERSION 3.10)

project(bones VERSION 0.0.1 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)

find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} src/engine.cpp)

set_target_properties(bones PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/bones/engine.h
)

configure_file(bones.pc.in bones.pc @ONLY)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
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

install(TARGETS bones
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/mylib.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


