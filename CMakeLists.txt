cmake_minimum_required(VERSION 3.10)
project(id_generator)

set(CMAKE_CXX_STANDARD 17)

add_library(id_generator STATIC id_generator.cpp)
target_include_directories (id_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})