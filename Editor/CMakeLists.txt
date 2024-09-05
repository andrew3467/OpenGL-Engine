cmake_minimum_required(VERSION 3.27)
project(OpenGL_Editor)

set(CMAKE_CXX_STANDARD 23)


add_subdirectory(external/spdlog bin)
include_directories(external/spdlog/include)

add_subdirectory(external/imgui bin)
include_directories(external/imgui)

include_directories(../Engine/src)

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)


add_executable(
        OpenGL_Editor
        ${SRC}
        ${HEADERS}
)

target_link_libraries(
        OpenGL_Editor
        PRIVATE
        OpenGL_Engine
)

target_precompile_headers(
        OpenGL_Editor
        PRIVATE
        src/editorpch.h
)

set_target_properties(OpenGL_Editor PROPERTIES LINKER_LANGUAGE CXX)