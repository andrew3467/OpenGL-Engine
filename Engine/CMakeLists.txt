cmake_minimum_required(VERSION 3.27)
project(OpenGL_Engine)

set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)


add_library(
        OpenGL_Engine
        ${HEADERS}
        ${SRC}
)


target_compile_definitions(
        OpenGL_Engine
        PRIVATE
        GLFW_INCLUDE_NONE
        GLE_PLATFORM_GLFW
        GLE_PLATFORM_OPENGL

        SPDLOG_HEADER_ONLY
)

target_precompile_headers(
        OpenGL_Engine
        PRIVATE
        src/GLE/glepch.h
)

target_link_libraries(
        OpenGL_Engine
        PUBLIC
        ImGui
        spdlog::spdlog
        glad::glad
        glm::glm
        EnTT::EnTT
        glfw
        stb
)

target_include_directories(
        OpenGL_Engine
        PUBLIC
        src/GLE

        ../External/imgui
        ../External/stb
)
