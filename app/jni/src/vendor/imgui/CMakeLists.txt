cmake_minimum_required(VERSION 3.6)

add_library(IMGUI STATIC)

target_sources(IMGUI PRIVATE
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        misc/cpp/imgui_stdlib.cpp
        backends/imgui_impl_sdl.cpp
        backends/imgui_impl_opengl3.cpp)

target_include_directories(IMGUI
        PUBLIC ../imgui
        PUBLIC backends)
