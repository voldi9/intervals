#ifndef AVL_TEST_REMOVING_KEYS_HPP
#define AVL_TEST_REMOVING_KEYS_HPP

#include "test_utils.hpp"

#include <algorithm>
#include <unordered_set>

namespace avl {
namespace test {
/*
	We keep removing the root until the tree is empty.
*/
TEST(LibAvlRemovingKeys, keep_removing_root_check_size)
{
	auto n = TEST_NUMBER;
	while(n--) {
		auto avl = generate_random_int_tree(TREE_SIZE, MAX_TEST_UINT);
		int size = avl.get_size();
		ASSERT_FALSE(avl.remove_key(0));
		while(size--) {
			avl.remove_key(avl.get_root()->get_value());
			ASSERT_EQ(size, avl.get_size());
		}
		ASSERT_FALSE(avl.remove_key(0));
	}
}

/*
	We keep removing the root until the tree is empty. After every removal we check the depth, 
	balance and subtree count of each node.
*/
TEST(LibAvlRemovingKeys, remove_random_check_all)
{
	auto n = TEST_NUMBER;
	while(n--) {
		auto avl = generate_random_int_tree(TREE_SIZE, MAX_TEST_UINT);
		auto vector = avl.get_key_vector();
		std::random_shuffle(vector.begin(), vector.end());
		while(vector.size()) {
			avl.remove_key(vector[vector.size()-1]);
			vector.pop_back();
			ASSERT_EQ(vector.size(), get_subtree_count(avl.get_root()));
			ASSERT_TRUE(validate_depth(avl.get_root()));
			ASSERT_TRUE(validate_balance(avl.get_root()));
		}
		ASSERT_EQ(0, avl.get_size());
	}
}

/*
	We generate random keys and random add/remove sequence. We add/remove the keys according 
	to the sequence. After every addition/removal we check the depth, balance and subtree count 
	of each node.
*/
TEST(LibAvlRemovingKeys, random_adds_and_removals_check_all)
{
	std::random_device r;
    std::mt19937 generator(r());
    std::uniform_int_distribution<int> random_value(0, TREE_SIZE);

	auto n = TEST_NUMBER;
	while(n--) {
		auto avl = avl::AvlTree<int>();
		auto sequence = generate_random_add_remove_sequence(TREE_SIZE);
		auto keys_vec = generate_random_keys(TREE_SIZE, MAX_TEST_UINT);
		std::unordered_set<int> set{};
		int ptr = 0;
		for(auto action : sequence) {
			if(action) {
				set.insert(keys_vec[ptr]);
				avl.add_key(keys_vec[ptr++]);
			}
			else {
				auto remove_it(set.begin());
				std::advance(remove_it, random_value(generator) % set.size());
				avl.remove_key(*remove_it);
				set.erase(remove_it);
			}
			ASSERT_EQ(set.size(), get_subtree_count(avl.get_root()));
			ASSERT_TRUE(validate_depth(avl.get_root()));
			ASSERT_TRUE(validate_balance(avl.get_root()));
		}
		ASSERT_EQ(0, avl.get_size());
	}
}

/*
	We keep generate a random tree. We try to delete a random value (randomly chosen between existent 
	in the tree and totally random) until the tree is empty.
*/
TEST(LibAvlRemovingKeys, random_removals_check_all)
{
	std::random_device r;
    std::mt19937 generator(r());
    std::bernoulli_distribution random_bool(0.8); // the chance to try to remove an existent key
    std::uniform_int_distribution<int> random_value(-MAX_TEST_UINT, MAX_TEST_UINT);
	auto n = TEST_NUMBER;
	while(n--) {
		auto avl = generate_random_int_tree(TREE_SIZE, MAX_TEST_UINT);
		auto vector = avl.get_key_vector();
		std::random_shuffle(vector.begin(), vector.end());
		while(avl.get_size()) {
			if(!random_bool(generator)) {
				int value;
				do {
					value = random_value(generator);
				} while(std::find(vector.begin(), vector.end(), value) == vector.end());
				int old_size = avl.get_size();
				ASSERT_FALSE(avl.remove_key(value));
				ASSERT_EQ(old_size, avl.get_size());
				continue;
			}
			avl.remove_key(vector[vector.size()-1]);
			vector.pop_back();
			ASSERT_EQ(vector.size(), get_subtree_count(avl.get_root()));
			ASSERT_TRUE(validate_depth(avl.get_root()));
			ASSERT_TRUE(validate_balance(avl.get_root()));
		}
		ASSERT_EQ(0, avl.get_size());
	}
}

} /* test */
} /* avl */

#endif /* AVL_TEST_REMOVING_KEYS_HPP */