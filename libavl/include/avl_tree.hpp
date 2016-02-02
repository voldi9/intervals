#ifndef LIBAVL_AVL_TREE_HPP
#define LIBAVL_AVL_TREE_HPP

#include "node.hpp"
#include <memory>

namespace avl {

#define NodePtr std::shared_ptr<Node<T>>

template <typename T>
class AvlTree {
private:
	NodePtr m_root {};
	void rebalance();
	void rotate_rr();
	void rotate_lr();
	void rotate_rl();
	void rotate_ll();
	void set_root(NodePtr node);
	const NodePtr create_node(const T& value) const;
	void dfs_clean(const NodePtr& node);
public:
	AvlTree () {}
	AvlTree (const T& value) { m_root.reset(new Node<T>(value)); }
	NodePtr add_key(const T& value);
	const NodePtr& get_root() const {
		return m_root;
	}
	~AvlTree() { dfs_clean(m_root); }
};

template <typename T>
void AvlTree<T>::rebalance() {}
template <typename T>
void AvlTree<T>::rotate_rr() {}
template <typename T>
void AvlTree<T>::rotate_lr() {}
template <typename T>
void AvlTree<T>::rotate_rl() {}
template <typename T>
void AvlTree<T>::rotate_ll() {}

template <typename T>
void AvlTree<T>::set_root(NodePtr node) {
	m_root = node;
}

template <typename T>
const NodePtr AvlTree<T>::create_node(const T& value) const {
	return NodePtr(new Node<T>(value));
}

template <typename T>
NodePtr AvlTree<T>::add_key(const T& value) {
	auto node = create_node(value);
	if(!m_root) {
		set_root(node);
	}
	else { 
		auto current = m_root;
		while(true) {
			if(node->get_value() == current->get_value()) { }
				//TODO: exception, added already present value
			if(node->get_value() < current->get_value()) {
				if(!current->get_lson()) {
					current->set_lson(node);
					node->set_parent(current);
					break;
				}
				current = current->get_lson();
			}
			if(node->get_value() > current->get_value()) {
				if(!current->get_rson()) {
					current->set_rson(node);
					node->set_parent(current);
					break;
				}
				current = current->get_rson();
			}
		}
	}
	return node;
}

//template <typename T>
//NodePtr AvlTree<T>::find_key(const T& value) const {}
//template <typename T>
//NodePtr AvlTree<T>::remove_key(const T& value) {}

//template <typename T>

template <typename T>
void AvlTree<T>::dfs_clean(const NodePtr& node) {
	if(node->get_lson())
		dfs_clean(node->get_lson());
	if(node->get_rson())
		dfs_clean(node->get_rson());
	node->set_parent(nullptr);
	node->set_lson(nullptr);
	node->set_rson(nullptr);
}

}

#endif