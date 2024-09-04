cmake_minimum_required(VERSION 3.27)
project(OpenGL_Editor)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine bin)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src)



file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)


add_library(
        OpenGL_Editor
        ${SRC}
        ${HEADERS}
)

set_target_properties(OpenGL_Editor PROPERTIES LINKER_LANGUAGE CXX)