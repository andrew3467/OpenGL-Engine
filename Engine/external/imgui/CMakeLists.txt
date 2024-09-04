cmake_minimum_required(VERSION 3.27)
project(ImGui)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE
        imgui_widgets.cpp
        imgui_tables.cpp
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
)

set(HEADERS
        imstb_truetype.h
        imstb_textedit.h
        imstb_rectpack.h
        imgui_internal.h
        imgui.h
        imconfig.h
)

set(BACKENDS
        backends/imgui_impl_glfw.h
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.h
        backends/imgui_impl_opengl3.cpp
        backends/imgui_impl_opengl3_loader.h
)

include_directories(./)


add_library(ImGui
        ${SOURCE}
        ${HEADERS}
        ${BACKENDS}
)