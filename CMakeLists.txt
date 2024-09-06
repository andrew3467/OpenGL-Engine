cmake_minimum_required(VERSION 3.27)
project(GLE)

set(CMAKE_CXX_STANDARD 23)

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

add_subdirectory(External)

add_subdirectory(Engine)
add_subdirectory(Editor)
