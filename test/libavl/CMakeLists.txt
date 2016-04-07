add_executable(libavl_test main.cpp)

target_link_libraries(libavl_test gtest gtest_main)

add_test(libavl_test test_libavl)