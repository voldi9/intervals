#ifndef AVL_TEST_GENERIC_TEST_UTILS_HPP
#define AVL_TEST_GENERIC_TEST_UTILS_HPP

#include "gtest/gtest.h"
#include "avl_tree.hpp"

#include <random>
#include <vector>

namespace avl {
namespace test {

const uint TEST_NUMBER = 100;
const uint TREE_SIZE = 1000;
const uint MAX_TEST_UINT = 10000;

template <typename T>
uint get_subtree_count(const NodePtr& node) {
	if(!node) {
		return 0;
	}
	return 1 + get_subtree_count(node->get_lson()) + get_subtree_count(node->get_rson());
}

template <typename T>
uint get_tree_count(const avl::AvlTree<T>& tree) {
	return get_subtree_count(tree.get_root());
}

inline uint max(uint a, uint b) { return a > b ? a : b; }

template <typename T>
bool validate_depth(const NodePtr& node) {
	if(!node) {
		return true;
	}
	if(!(validate_depth(node->get_lson()) &&
		validate_depth(node->get_rson()))) {
		return false;
	}
	uint depth = 1 + max( 
			node->get_lson_depth(),
			node->get_rson_depth());
	EXPECT_EQ(depth, node->get_depth());
	return depth == node->get_depth();
}

template <typename T>
bool validate_balance(const NodePtr& node) {
	if(!node) {
		return true;
	}
	return validate_balance(node->get_lson()) && 
			validate_balance(node->get_rson()) &&
			node->is_balanced();
}

std::vector<bool> generate_random_add_remove_sequence(uint size) {
	std::random_device r;
    std::mt19937 generator(r());
    std::bernoulli_distribution random_bool(0.5);
    auto sequence = std::vector<bool>();
    uint available_adds = size; 
    uint available_removes = size;
	while(available_adds || available_removes) {
		if(random_bool(generator) && available_adds) {
			sequence.push_back(true);
			available_adds--;
		}
		else if(available_removes > available_adds) {
			sequence.push_back(false);
			available_removes--;
		}
	}
	return std::move(sequence);
}

std::vector<int> generate_random_keys(uint size, uint max_value) {
	std::random_device r;
    std::mt19937 generator(r());
    std::uniform_int_distribution<int> random_value(-max_value, max_value);
    auto keys = std::vector<int>();
	while(size--) {
	    keys.push_back(random_value(generator));
	}
	return std::move(keys);
}

avl::AvlTree<int> generate_random_int_tree(uint size, uint max_value) {
	auto tree = avl::AvlTree<int>();
	for(auto value : generate_random_keys(size, max_value)) {
	    tree.add_key(value);
	}
	return tree;
}

} /* test */
} /* avl */

#endif /* AVL_TEST_GENERIC_TEST_UTILS_HPP */