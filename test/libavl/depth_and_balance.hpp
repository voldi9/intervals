#ifndef AVL_TEST_DEPTH_AND_BALANCE_HPP
#define AVL_TEST_DEPTH_AND_BALANCE_HPP

#include "test_utils.hpp"

namespace avl {
namespace test {
/*
	We brutally check if the node's depths properties are set right.
*/
TEST(LibAvlDepthAndBalance, validate_depth)
{
	auto n = TEST_NUMBER;
	while(n--) {
		auto avl = generate_random_int_tree(TREE_SIZE, MAX_TEST_UINT);
		validate_depth(avl.get_root());
	}
}

/*
	We brutally check if the node's subtrees are balanced.
*/
TEST(LibAvlDepthAndBalance, validate_balance)
{
	auto n = TEST_NUMBER;
	while(n--) {
		auto avl = generate_random_int_tree(TREE_SIZE, MAX_TEST_UINT);
		validate_balance(avl.get_root());
	}
}

} /* test */
} /* avl */

#endif /* AVL_TEST_DEPTH_AND_BALANCE_HPP */