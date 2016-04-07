cmake_minimum_required (VERSION 2.6)
project (Intervals)
# The version number.
set (intervals_VERSION_MAJOR 0)
set (intervals_VERSION_MINOR 1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(GTEST_DIR third_party/gtest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -DDEBUG=1")


include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/libavl/include)

add_subdirectory(libavl)

# add the executable
add_executable(intervals main.cpp)
set_target_properties(intervals
					PROPERTIES
					OUTPUT_NAME intervals)
target_link_libraries (intervals avl)

enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)
add_subdirectory(test)