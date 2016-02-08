#include <avl_tree.hpp>
#include <iostream>
#include <random>
#include "avl_tree.hpp"

int main() {
	const unsigned int RANDOM_TIMES = 100;
	const unsigned int MAX_VALUE = 1000;
	//std::random_device r;
    //std::mt19937 generator(r());
    //std::uniform_int_distribution<int> random_value(-MAX_VALUE, MAX_VALUE);
    auto avl = avl::AvlTree<int>();
    unsigned int quantity = 0;
    for(int i = 0; i < RANDOM_TIMES; i++) {
    	if(avl.add_key(i)) {
    		quantity++;
    	}
    }
	return 0;
}