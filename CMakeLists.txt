cmake_minimum_required(VERSION 3.27)
project(OpenGL_Engine)

set(CMAKE_CXX_STANDARD 23)


add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)

add_subdirectory(external/glfw)
include_directories(external/glfw/include)
#Tell glfw not to src OpenGL
add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory(external/glad)
include_directories(external/glad/include)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
add_subdirectory(external/glm)
include_directories(external/glm)

add_subdirectory(external/entt)
include_directories(external/entt/src)

add_subdirectory(external/imgui)
include_directories(external/imgui)



#if (WIN32)
    #add_compile_definitions(GLE_PLATFORM_WINDOWS)
#elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#    add_compile_definitions(GLE_PLATFORM_LINUX)
#else ()
    add_compile_definitions(GLE_PLATFORM_GLFW)
    add_compile_definitions(GLE_PLATFORM_OPENGL)
#endif ()

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

if(WIN32)
    # OpenGL
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
endif ()

include_directories(src/GLE)
add_executable(
        OpenGL_Engine
        ${HEADERS}
        ${SRC}
        main.cpp
        SandboxLayer.h
        SandboxLayer.cpp
)

target_precompile_headers(
        OpenGL_Engine
        PRIVATE
        src/GLE/glepch.h
)

target_link_libraries(
        OpenGL_Engine
        PRIVATE
        spdlog
        glfw
        glad
        glm
        EnTT
        ImGui
        ${OPENGL_LIBRARY}
)
