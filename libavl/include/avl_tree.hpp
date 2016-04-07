#ifndef LIBAVL_AVL_TREE_HPP
#define LIBAVL_AVL_TREE_HPP

#include "node.hpp"

#include <memory>
#include <vector>

#define NodePtr std::shared_ptr<avl::Node<T>>

namespace avl {
template <typename T>
class AvlTree {
private:
	unsigned int m_size {};
	NodePtr m_root {};
	inline uint max(uint a, uint b) { return a > b ? a : b; }
	void rotate_rr();
	void rotate_lr();
	void rotate_rl();
	void rotate_ll();
	void rebalance(const NodePtr& node);
	void set_root(const NodePtr& node);
	void dfs_clean(const NodePtr& node);
	NodePtr create_node(const T& value) const;
	void add_to_key_vector(std::vector<T>& vector, const NodePtr& node) const;
public:
	AvlTree () {}
	AvlTree (const T& value) { m_root.reset(new Node<T>(value)); m_size++; }
	~AvlTree() { dfs_clean(m_root); }
	NodePtr add_key(const T& value);
	NodePtr add_key(const NodePtr& node);
	bool remove_key(const T& value);
	bool remove_key(NodePtr node);
	NodePtr find_key(const T& value) const;
	const NodePtr& get_root() const { return m_root; }
	uint get_size() { return m_size; }
	std::vector<T> get_key_vector() const;
};

template <typename T>
void AvlTree<T>::rotate_rr() {}
template <typename T>
void AvlTree<T>::rotate_lr() {}
template <typename T>
void AvlTree<T>::rotate_rl() {}
template <typename T>
void AvlTree<T>::rotate_ll() {}

template <typename T>
void AvlTree<T>::set_root(const NodePtr& node) {
	m_root = NodePtr(node);
}

template <typename T>
NodePtr AvlTree<T>::create_node(const T& value) const {
	return std::make_shared<Node<T>>(Node<T>(value));
}

template <typename T>
void AvlTree<T>::add_to_key_vector(std::vector<T>& vector, const NodePtr& node) const {
	if(!node) {
		return;
	}
	add_to_key_vector(vector, node->get_lson());
	add_to_key_vector(vector, node->get_rson());
	vector.push_back(node->get_value());
}

/*
	Returns a vector containing all the keys present in the tree
*/ 
template <typename T>
std::vector<T> AvlTree<T>::get_key_vector() const {
	std::vector<T> vector{};
	add_to_key_vector(vector, m_root);
	return vector;
}

/*
	Updates the depths value of the nodes on the path from node to the
	root. Triggered on the return values of add/remove_key methods if
	they are not nulls.
*/ 
template <typename T>
void AvlTree<T>::rebalance(const NodePtr& node) {
	if(!node) {
		return;
	}
	// TODO: rotations
	node->set_depth(1 + max(node->get_lson_depth(), node->get_rson_depth()));
	rebalance(node->get_parent());
	return;
}

/*
	Returns a shared pointer to the node with the given key value
	added to the tree or a nullptr if the key was already present 
	in the tree.
*/
template <typename T>
NodePtr AvlTree<T>::add_key(const NodePtr& new_node) {
	if(!m_root) {
		set_root(new_node);
	}
	else { 
		auto node = m_root;
		while(node) {
			if(new_node->get_value() == node->get_value()) {
				return nullptr; 
			}
			if(new_node->get_value() < node->get_value()) {
				if(!node->get_lson()) {
					node->set_lson(new_node);
					break;
				}
				node = node->get_lson();
			}
			if(new_node->get_value() > node->get_value()) {
				if(!node->get_rson()) {
					node->set_rson(new_node);
					break;
				}
				node = node->get_rson();
			}
		}
		new_node->set_parent(node);
	}
	m_size++;
	rebalance(new_node);
	return new_node;
}


template <typename T>
NodePtr AvlTree<T>::add_key(const T& value) {
	return add_key(create_node(value));
}


/*
	Removes a node with a given value from the tree.
	Returns a true if the removal succeeded, false otherwise.
*/

template <typename T>
bool AvlTree<T>::remove_key(NodePtr node) {
	if(!node) {
		return false;
	}
	if(!node->has_both_sons()) {
		NodePtr son;
		son = node->has_lson() ? node->get_lson() : 
						         node->get_rson();
		if(node == m_root) {
			m_root = son;
		}
		node->substitute(son);
		rebalance(son);
		m_size--;
	}
	else {
		auto next = node->find_next();
		node->set_value(next->get_value());
		remove_key(next);
	}
	return true;
}

template <typename T>
bool AvlTree<T>::remove_key(const T& value) {
	return remove_key(find_key(value));
}


/*
	Returns a shared pointer to the node with the given key value
	or an empty share pointer if the key is not	present int the tree.
*/ 
template <typename T>
NodePtr AvlTree<T>::find_key(const T& value) const {
	auto node = m_root;
	while(node) {
		if(value == node->get_value()) { 
			break;
		}
		if(value < node->get_value()) {
			node = node->get_lson();
		}
		if(value > node->get_value()) {
			node = node->get_rson();
		}
	}
	return node;
}

template <typename T>
void AvlTree<T>::dfs_clean(const NodePtr& node) {
	if(!node) {
		return;
	}
	dfs_clean(node->get_lson());
	dfs_clean(node->get_rson());
	node->release();
}

} /* avl */

#endif