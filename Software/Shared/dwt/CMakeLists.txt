cmake_minimum_required(VERSION 3.22)

project(dwt)

add_library(dwt INTERFACE)
target_include_directories(dwt INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(dwt INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/dwt.c
)