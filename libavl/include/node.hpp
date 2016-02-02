#ifndef LIBAVL_NODE_HPP
#define LIBAVL_NODE_HPP

#include <memory>

namespace avl {

template <class T>
class Node {
	typedef unsigned int uint;
private:
	std::shared_ptr<Node<T>> m_parent {}, m_lson {}, m_rson {};	
	T m_value {};
	uint m_depth {};
public:
	virtual const T& get_value() const {
		return m_value;
	}
	virtual void set_value(const T& value) {
		m_value = value;
	}

	virtual const uint get_depth() const {
		return m_depth;
	}
	virtual void set_depth(const uint depth) {
		m_depth = depth;
	}

	virtual const std::shared_ptr<Node<T>>& get_parent() const {
		return m_parent;
	}
	virtual void set_parent(const std::shared_ptr<Node<T>>& parent) {
		m_parent = parent;
	}

	virtual const std::shared_ptr<Node<T>>& get_lson() const {
		return m_lson;
	}
	virtual void set_lson(const std::shared_ptr<Node<T>>& lson) {
		m_lson = lson;
	}

	virtual const std::shared_ptr<Node<T>>& get_rson() const {
		return m_rson;
	}
	virtual void set_rson(const std::shared_ptr<Node<T>>& rson) {
		m_rson = rson;
	}
	
	Node(T value) : m_value(value) {}

	virtual ~Node() { };
};


}	/* avl */

#endif
