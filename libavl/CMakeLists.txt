set(sources
	include/avl_tree.hpp
	)

include_directories(include)

add_library(avl ${sources})

set_target_properties(avl
					PROPERTIES
					LINKER_LANGUAGE CXX
					OUTPUT_NAME avl)


