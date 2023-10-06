cmake_minimum_required(VERSION 3.10)

project(AlgoBasicCpp)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)
find_package(Ceres REQUIRED)

file(GLOB_RECURSE ABC_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/algorithms/*.cpp")
add_library(abc SHARED ${ABC_SOURCES})
target_include_directories(abc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(abc PUBLIC Eigen3::Eigen ${OpenCV_LIBS} ceres)
target_compile_features(abc PUBLIC cxx_std_17)
target_compile_options(abc PUBLIC "-Wall;-Wextra;-Wunused;-Wformat=2;-Wshadow")

add_subdirectory(tests)
