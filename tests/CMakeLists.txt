link_libraries(abc)

add_executable(test_sort test_sort.cpp)
add_executable(test_ransac test_ransac.cpp)
add_executable(test_gen_line_pt test_gen_line_pt.cpp)

add_executable(test_fit_line test_fit_line.cpp)
target_link_libraries(test_fit_line GTest::gtest GTest::gtest_main)
