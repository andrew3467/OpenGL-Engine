cmake_minimum_required(VERSION 3.27)
project(OpenGL_Engine)

set(CMAKE_CXX_STANDARD 23)




find_package(spdlog CONFIG REQUIRED)
add_compile_definitions(GLFW_INCLUDE_NONE)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)


add_subdirectory(../external/imgui bin)
include_directories(../external/imgui)



add_compile_definitions(GLE_PLATFORM_GLFW)
add_compile_definitions(GLE_PLATFORM_OPENGL)




file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

include_directories(src/GLE)
add_library(
        OpenGL_Engine
        ${HEADERS}
        ${SRC}
)

target_precompile_headers(
        OpenGL_Engine
        PRIVATE
        src/GLE/glepch.h
)

target_link_libraries(
        OpenGL_Engine
        PRIVATE
        spdlog::spdlog
        glfw
        glad::glad
        glm::glm
        EnTT::EnTT
        imgui
)
