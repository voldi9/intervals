cmake_minimum_required (VERSION 2.6)
project (Intervals)
# The version number.
set (Intervals_VERSION_MAJOR 0)
set (Intervals_VERSION_MINOR 1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/libavl/include")

add_subdirectory(libavl) 
 

# add the executable
add_executable(Intervals main.cpp)
set_target_properties(Intervals
					PROPERTIES
					OUTPUT_NAME intervals)
target_link_libraries (Intervals LibAvl)
