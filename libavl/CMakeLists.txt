set(sources
	src/avl_tree.cpp
	)

include_directories(include)

add_library(LibAvl ${sources})

set_target_properties(LibAvl
					PROPERTIES
					OUTPUT_NAME avl)


