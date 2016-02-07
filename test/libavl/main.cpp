#include <iostream>

#include "gtest/gtest.h"
#include "avl_tree.hpp"

namespace {
	template <typename T>
	unsigned int get_subtree_count(const std::shared_ptr<avl::Node<T>>& node) {
		if(!node)
			return 0;
		return 1 + get_subtree_count(node->get_lson()) + get_subtree_count(node->get_rson());
	}

	template <typename T>
	unsigned int get_tree_count(const avl::AvlTree<T>& tree) {
		return get_subtree_count(tree.get_root());
	}
}

TEST(LIBAVL, descending_values_adding)
{
	auto avl = avl::AvlTree<int>(8);
	avl.add_key(7);
	avl.add_key(6);
	avl.add_key(5);
    EXPECT_EQ(avl.get_root()->get_value(), avl.get_root()->get_lson()->get_lson()->get_value() + 2);
    EXPECT_EQ(avl.get_size(), 4);
    EXPECT_EQ(avl.get_size(), get_subtree_count(avl.get_root()));
    EXPECT_EQ(avl.find_key(9), nullptr);
}

