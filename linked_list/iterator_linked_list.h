#pragma once

#include <iterator> // for iterator tag
template <typename T>
class linked_list;

template <typename node, typename T>
class const_base_iterator
{
protected:
	node* m_node{};
	friend linked_list<T>;
public:
	using iterator_category = std::forward_iterator_tag;

	// constructors
	const_base_iterator() = default;
	const_base_iterator(const const_base_iterator& b) = default;
	explicit const_base_iterator(node* n) : m_node(n) {}

	// increment operator
	const_base_iterator& operator++()
	{
		m_node = m_node->m_next;
		return *this;
	}
	const_base_iterator operator++(int)
	{
		const_base_iterator temp(m_node);
		m_node = m_node->m_next;
		return temp;
	}

	// comparison
	constexpr bool operator==(const_base_iterator other) const noexcept { return m_node == other.m_node; }
	constexpr bool operator!=(const_base_iterator other) const noexcept { return m_node != other.m_node; }

	// dereferencing
	const T& operator*() const { return m_node->m_data; }
	const T* operator->() const { return &(m_node->m_data); }
};

template <typename node, typename T>
class base_iterator : public const_base_iterator<node,T>
{
protected:
	// tags
	using const_base_iterator<node, T>::m_node;
	friend linked_list<T>;
public:
	using iterator_category = std::forward_iterator_tag;

	// constructors
	base_iterator() = default;
	base_iterator(const base_iterator& other) { m_node = other.m_node; }
	explicit base_iterator(node* n) { m_node = n; }

	T& operator*() { return m_node->m_data; }
	T* operator->() { return &(m_node->m_data); }
};
