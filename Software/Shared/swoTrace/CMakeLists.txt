cmake_minimum_required(VERSION 3.22)

project(swoTrace)

add_library(swoTrace INTERFACE)
target_include_directories(swoTrace INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(swoTrace INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/swoTrace.c
)