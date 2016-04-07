#ifndef AVL_TEST_GENERIC_TEST_UTILS_HPP
#define AVL_TEST_GENERIC_TEST_UTILS_HPP

#include "gtest/gtest.h"
#include "avl_tree.hpp"

#include <random>
#include <vector>
#include <string>

namespace avl {
namespace test {

const uint TEST_NUMBER = 1;
const uint TREE_SIZE = 10;
const uint MAX_TEST_UINT = 10000;

uint digit_number(int x) {
	uint result = 0;
	if(x <= 0) {
		result ++;
	}
	while(x) {
		x /= 10;
		result++;
	}
	return result;
}

void print(const AvlTree<int>& tree) {
	std::cout << "printing tree:\n";
	std::vector<std::shared_ptr<Node<int>>> next_level { tree.get_root() };
	uint level = 0;
	while(next_level.size()) {
		std::vector<std::shared_ptr<Node<int>>> temp {};
		for(auto node : next_level) {
			if(!node) {
				continue;
			}
			std::cout << std::to_string(node->get_value()) << " -> [";
			if(node->has_lson()) {
				temp.push_back(node->get_lson());
				std::cout << std::to_string(node->get_lson()->get_value());
			}
			if(!node->is_leaf()) {
				std::cout << "; ";
			}
			if(node->has_rson()) {
				temp.push_back(node->get_rson());
				std::cout << std::to_string(node->get_rson()->get_value());
			}
			std::cout << "]" << std::endl;
		}
		next_level = temp;
		std::cout << "\n" << std::endl;
	}
}

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
void validate_depth(const NodePtr& node) {
	if(!node) {
		return;
	}
	validate_depth(node->get_lson());
	validate_depth(node->get_rson());
	if(node->is_leaf()) {
		ASSERT_EQ(node->get_depth(), 1);
	}
	uint depth = 1 + max( 
			node->get_lson_depth(),
			node->get_rson_depth());
	ASSERT_EQ(depth, node->get_depth());
}

template <typename T>
void validate_balance(const NodePtr& node) {
	if(!node) {
		return;
	}
	ASSERT_TRUE(node->is_balanced());
	validate_balance(node->get_lson());
	validate_balance(node->get_rson());
}

template <typename T>
void validate_bst(const NodePtr& node) {
	if(!node) {
		return;
	}
	if(node->has_lson()) {
		ASSERT_GT(node->get_value(), node->get_lson()->get_value());
	}
	if(node->has_rson()) {
		ASSERT_LT(node->get_value(), node->get_rson()->get_value());
	}
	validate_bst(node->get_lson());
	validate_bst(node->get_rson());
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