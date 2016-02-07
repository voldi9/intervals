add_executable(libavl main.cpp)

target_link_libraries(libavl gtest gtest_main)

add_test(libavl test_libavl)