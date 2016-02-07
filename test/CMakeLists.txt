set(GTEST_DIR ${CMAKE_SOURCE_DIR}/third_party/gtest)

include_directories(${GTEST_DIR}/include ${GTEST_DIR})

add_subdirectory(${GTEST_DIR} ${GTEST_DIR})

add_subdirectory(libavl)