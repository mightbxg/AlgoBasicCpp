cmake_minimum_required(VERSION 3.10)

project(AlgoBasicCpp)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE abc_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
add_library(abc STATIC
    ${Abc_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/white_board.cpp)
target_include_directories(abc PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(abc PUBLIC
    Eigen3::Eigen ${OpenCV_LIBS})
target_compile_features(abc PUBLIC cxx_std_17)
target_compile_options(abc PUBLIC
    "-Wall;-Wextra;-Wunused;-Wformat=2;-Wshadow")

add_subdirectory(tests)
