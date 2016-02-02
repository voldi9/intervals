#include <avl_tree.hpp>
#include <iostream>

int main() {
	auto t = avl::AvlTree<int>(6);
	auto z = t.add_key(5);
	auto z2 = t.add_key(4);
	auto z3 = t.add_key(7);
	auto r = t.get_root();
	auto r2 = std::shared_ptr<avl::Node<int>>(r);
	std::cout << "efqfeqw\n" << r2->get_value() << "\n" << std::endl;
	auto t1 = avl::AvlTree<int>(546);
	std::cout << "efqfeqw\n" << t1.get_root()->get_value() << "\n" << std::endl;
	auto t2 = avl::AvlTree<int>(56);
	std::cout << "efqfeqw\n" << t2.get_root()->get_value() << "\n" << std::endl;
	auto t3 = avl::AvlTree<int>(55);
	std::cout << "efqfeqw\n" << t3.get_root()->get_value() << "\n" << std::endl;
	return 0;
}