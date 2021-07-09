cmake_minimum_required(VERSION 3.6)

project(GAME)

# armeabi-v7a requires cpufeatures library
include(AndroidNdkModules)
android_ndk_import_module_cpufeatures()


# SDL sources are in a subfolder named "SDL"
add_subdirectory(SDL2)

#target_include_directories(SDL2 PUBLIC SDL2/include)

# Compilation of companion libraries

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)