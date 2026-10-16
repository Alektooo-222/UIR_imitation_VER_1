cmake_minimum_required(VERSION 3.22)

project(INA219)

add_library(INA219 INTERFACE)
target_include_directories(INA219 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(INA219 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/INA219.c
)