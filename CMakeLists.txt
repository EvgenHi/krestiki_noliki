cmake_minimum_required (VERSION 3.5)

project (krestiki_noliki)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++20")
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${SOURCE_DIR}/*.cpp")

add_executable (krestiki_noliki ${source_files})