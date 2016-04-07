#ifndef LIBAVL_NODE_HPP
#define LIBAVL_NODE_HPP

#include <memory>

#ifdef DEBUG
	#include <iostream>
#endif

namespace avl {

template <class T>
class Node : public std::enable_shared_from_this<Node<T>> {
	typedef unsigned int uint;
private:
	std::shared_ptr<Node<T>> m_parent {}, m_lson {}, m_rson {};	
	T m_value {};
	uint m_depth {};
public:
	const T& get_value() const {
		return m_value;
	}
	virtual void set_value(const T& value) {
		m_value = value;
	}

	const uint get_lson_depth() const {
		if(!m_lson) {
			return 0;
		}
		return m_lson->get_depth();
	}
	const uint get_rson_depth() const {
		if(!m_rson) {
			return 0;
		}
		return m_rson->get_depth();
	}
	const uint get_depth() const {
		return m_depth;
	}
	virtual void set_depth(const uint depth) {
		m_depth = depth;
	}
	const bool is_balanced() const {
		return (get_rson_depth() - get_lson_depth() <= 1) &&
			   (get_rson_depth() - get_lson_depth() >= -1);
	}

	bool has_parent() const {
		return !(m_parent == nullptr);
	}
	const std::shared_ptr<Node<T>>& get_parent() const {
		return m_parent;
	}
	virtual void set_parent(const std::shared_ptr<Node<T>>& parent) {
		m_parent = parent;
	}
	virtual void release_parent() {
		if(m_parent) {
			if(is_lson()) {
				m_parent->release_lson();
				return;
			}
			if(is_rson()) {
				m_parent->release_rson();
				return;
			}
		}
	}

	const std::shared_ptr<Node<T>> get_ptr() const {
		return this->shared_from_this();
	}

	virtual const std::shared_ptr<Node<T>> find_next() const {
		if(m_rson) {
			auto node = m_rson;
			while(node->has_lson()) {
				node = node->get_lson();
			}
			return node;
		}
		auto node = this->shared_from_this();
	}

	bool is_lson() const {
		return m_parent && m_parent->has_lson() && 
			   m_parent->get_lson()->get_value() == m_value; 
	}
	bool has_lson() const {
		return !(m_lson == nullptr);
	}
	const std::shared_ptr<Node<T>>& get_lson() const {
		return m_lson;
	}
	virtual void set_lson(const std::shared_ptr<Node<T>>& lson) {
		m_lson = lson;
	}
	virtual void release_lson() {
		m_lson = nullptr;
	}

	bool is_rson() const {
		return m_parent && m_parent->has_rson() && 
			   m_parent->get_rson()->get_value() == m_value; 
	}
	bool has_rson() const {
		return !(m_rson == nullptr);
	}
	const std::shared_ptr<Node<T>>& get_rson() const {
		return m_rson;
	}
	virtual void set_rson(const std::shared_ptr<Node<T>>& rson) {
		m_rson = rson;
	}
	virtual void release_rson() {
		m_rson = nullptr;
	}

	bool has_both_sons() const {
		return has_lson() && has_rson();
	}

	bool is_leaf() const {
		return !(m_lson || m_rson);
	}

	virtual void substitute(std::shared_ptr<Node<T>> other) {
		if(has_parent() && other) {
			is_lson() ? m_parent->set_lson(other) :
						m_parent->set_rson(other);
			other->set_parent(m_parent);
		}
		release();
	}

	virtual void release() {
		release_lson();
		release_rson();
		release_parent();
	}
	
	Node(T value) : m_value(value), m_depth(1) {}

	virtual ~Node() { };
};


} /* avl */

#endif
