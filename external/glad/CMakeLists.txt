cmake_minimum_required(VERSION 3.27)
project(glad)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_library(glad
        include/Glad/glad.h
        include/Glad/glad_wgl.h
        include/KHR/khrplatform.h

        src/glad_wgl.c
        src/glad.c
)
