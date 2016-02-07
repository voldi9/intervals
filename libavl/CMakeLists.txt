set(sources
	include/avl_tree.hpp
	)

include_directories(include)

add_library(LibAvl ${sources})

set_target_properties(LibAvl
					PROPERTIES
					LINKER_LANGUAGE CXX
					OUTPUT_NAME avl)


