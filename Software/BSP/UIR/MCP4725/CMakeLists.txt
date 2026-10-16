cmake_minimum_required(VERSION 3.22)

project(MCP4725)

add_library(MCP4725 INTERFACE)
target_include_directories(MCP4725 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(MCP4725 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/MCP4725.c
)