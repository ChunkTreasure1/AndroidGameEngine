cmake_minimum_required(VERSION 3.6)

add_subdirectory(glm)
add_subdirectory(imgui)

target_include_directories(main PUBLIC
        rapidjson/include)