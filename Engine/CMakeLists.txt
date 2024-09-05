cmake_minimum_required(VERSION 3.27)
project(OpenGL_Engine)

set(CMAKE_CXX_STANDARD 23)




add_subdirectory(${CMAKE_SOURCE_DIR}/external/spdlog bin)
include_directories(external/spdlog/include bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw bin)
include_directories(external/glfw/include)
#Tell glfw not to src OpenGL
add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad bin)
include_directories(external/glad/include)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm bin)
include_directories(${CMAKE_SOURCE_DIR}/external/glm)

add_subdirectory(external/entt bin)
include_directories(external/entt/src)

add_subdirectory(external/imgui)
include_directories(external/imgui bin)




add_compile_definitions(GLE_PLATFORM_GLFW)
add_compile_definitions(GLE_PLATFORM_OPENGL)




file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

if(WIN32)
    # OpenGL
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
endif ()

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
        PUBLIC
        spdlog
        ImGui
        PRIVATE
        glfw
        glad
        glm
        EnTT
        ${OPENGL_LIBRARY}
)
