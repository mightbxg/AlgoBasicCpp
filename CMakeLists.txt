cmake_minimum_required(VERSION 3.10)

project(AlgoBasicCpp)

add_library(Utils INTERFACE)
target_include_directories(Utils INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(Utils INTERFACE cxx_std_17)
target_compile_options(Utils INTERFACE
    "-Wall;-Wextra;-Wunused;-Wformat=2;-Wshadow")

add_subdirectory(tests)
