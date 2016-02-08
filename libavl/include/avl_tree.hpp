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
	const NodePtr& exchange(const NodePtr& old_node, const NodePtr& new_node);
	NodePtr create_node(const T& value) const;
	void add_to_key_vector(std::vector<T>& vector, const NodePtr& node) const;
public:
	AvlTree () {}
	AvlTree (const T& value) { m_root.reset(new Node<T>(value)); m_size++; }
	~AvlTree() { dfs_clean(m_root); }
	NodePtr add_key(const T& value);
	NodePtr remove_key(const T& value);
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
	return NodePtr(new Node<T>(value));
}

template <typename T>
const NodePtr& AvlTree<T>::exchange(const NodePtr& old_node, const NodePtr& new_node) {
	if(old_node->get_parent()) {
		if(old_node->get_parent()->get_lson() == old_node) {
			old_node->get_parent()->set_lson(new_node);
		}
		else if(old_node->get_parent()->get_rson() == old_node) {
			old_node->get_parent()->set_rson(new_node);
		}
		new_node->set_parent(old_node->get_parent());
	}
	if(old_node->get_lson()) {
		new_node->set_lson(old_node->get_lson());
	}
	if(old_node->get_rson()) {
		new_node->set_rson(old_node->get_rson());
	}
	old_node->release();
	return new_node;
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
	node->set_depth(1 + max(node->get_lson_depth(), node->get_rson_depth()));
	rebalance(node->get_parent());
	return;
}

/*
	Returns a shared pointer to the node with the given key value
	added to the tree or an empty share pointer if the key was already
	present int the tree.
*/ 
template <typename T>
NodePtr AvlTree<T>::add_key(const T& value) {
	auto node = create_node(value);
	if(!m_root) {
		set_root(node);
	}
	else { 
		auto current = m_root;
		while(true) {
			if(node->get_value() == current->get_value()) {
				return NodePtr(); 
			}
			if(node->get_value() < current->get_value()) {
				if(!current->get_lson()) {
					current->set_lson(node);
					break;
				}
				current = current->get_lson();
			}
			if(node->get_value() > current->get_value()) {
				if(!current->get_rson()) {
					current->set_rson(node);
					break;
				}
				current = current->get_rson();
			}
		}
		node->set_parent(current);
	}
	m_size++;
	rebalance(node);
	return node;
}


/*
	Removes a node with a given value from the tree.
	Returns a shared pointer to:
		-nullptr if the removed key was the only one in the tree
		 or if it was not present in the tree
		-the removed node's parent if the removed node is a leaf
		-the removed node's longer-subtree-having son otherwise
*/ 
template <typename T>
NodePtr AvlTree<T>::remove_key(const T& value) {
	auto node = find_key(value);
	if(!node) {
		return node;
	}
	if(node == m_root && m_size == 1) {
		m_root = nullptr;
		m_size--;
		return m_root;
	}
	if(node->is_leaf()) {
		m_size--;
		return exchange(node, nullptr);
	}

	//TODO: finish implementation
}

/*
	Returns a shared pointer to the node with the given key value
	or an empty share pointer if the key is not	present int the tree.
*/ 
template <typename T>
NodePtr AvlTree<T>::find_key(const T& value) const {
	if(!m_root) {
		return NodePtr();
	}
	auto current = m_root;
	while(true) {
		if(value == current->get_value()) { 
			return current;
		}
		if(value < current->get_value()) {
			if(!current->get_lson()) {
				return NodePtr();
			}
			current = current->get_lson();
		}
		if(value > current->get_value()) {
			if(!current->get_rson()) {
				return NodePtr();
			}
			current = current->get_rson();
		}
	}
}

template <typename T>
void AvlTree<T>::dfs_clean(const NodePtr& node) {
	if(node->get_lson())
		dfs_clean(node->get_lson());
	if(node->get_rson())
		dfs_clean(node->get_rson());
	node->release();
}

} /* avl */

#endif