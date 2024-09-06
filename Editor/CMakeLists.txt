cmake_minimum_required(VERSION 3.27)
project(OpenGL_Editor)

set(CMAKE_CXX_STANDARD 23)



find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)



file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(
        OpenGL_Editor
        ${HEADERS}
        ${SRC}
)

target_precompile_headers(
        OpenGL_Editor
        PRIVATE
        src/editorpch.h
)

target_link_libraries(
        OpenGL_Editor
        PUBLIC
        OpenGL_Engine
)

target_include_directories(
        OpenGL_Editor
        PRIVATE
        src/Editor
        ../Engine/src

        #../external/imgui
)