#ifndef AVL_TEST_BASIC_SANITY_HPP
#define AVL_TEST_BASIC_SANITY_HPP

#include "test_utils.hpp"

#include <unordered_set>

namespace avl {
namespace test {

/*
	We are adding values to the tree while insterting the to a std::unordered_set 
	as well. Afterwards we compare the set's and the tree's size and check if 
	every key found in the set can be found in the tree as well. 
*/
TEST(LibAvlBasicSanity, validate_with_set)
{
	auto n = TEST_NUMBER;
	while(n--) {
		auto keys_vec = generate_random_keys(TREE_SIZE, MAX_TEST_UINT);
		std::unordered_set<int> keys{};
		auto avl = avl::AvlTree<int>();
		uint quantity = 0;
	    for(auto value : keys_vec) {
	    	if(avl.add_key(value)) {
	    		keys.insert(value);
	    		quantity++;
	    	}
	    	else {
	    		ASSERT_TRUE(avl.find_key(value));
	    	}
	    	validate_bst(avl.get_root());
			ASSERT_EQ(quantity, get_subtree_count(avl.get_root()));
			ASSERT_EQ(quantity, keys.size());
		}
		for(const auto& value : keys_vec) {
			ASSERT_TRUE(avl.find_key(value));
		}
	}
}

} /* test */
} /* avl */

#endif /* AVL_TEST_BASIC_SANITY_HPP */