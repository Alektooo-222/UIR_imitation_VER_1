cmake_minimum_required(VERSION 3.22)

project(UIR)

add_library(UIR INTERFACE)
target_include_directories(UIR INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(UIR INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/UIR.c
)