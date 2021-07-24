cmake_minimum_required(VERSION 3.6)

add_library(IMNODES STATIC)

target_sources(IMNODES PRIVATE
        imnodes.cpp
        imnodes.h
        imnodes_internal.h)

target_include_directories(IMNODES
        PUBLIC ../imnodes)