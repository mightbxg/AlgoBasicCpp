cmake_minimum_required(VERSION 3.10)

project(AlgoBasicCpp)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE Abc_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
add_library(Abc STATIC
    ${Abc_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/white_board.cpp)
target_include_directories(Abc PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(Abc PUBLIC
    Eigen3::Eigen ${OpenCV_LIBS})
target_compile_features(Abc PUBLIC cxx_std_17)
target_compile_options(Abc PUBLIC
    "-Wall;-Wextra;-Wunused;-Wformat=2;-Wshadow")

add_subdirectory(tests)
