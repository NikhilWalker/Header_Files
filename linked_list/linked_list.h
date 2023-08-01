#pragma once

// linked list is a linear data structure used to store data in memory efficient way
//  for example the int data is stores in this library as
/*
data is 1 2 3 4 5
dll is
	1 -> 2 -> 3 -> 4 -> 5 -> nullptr
*/

#include <string>
#include <stdexcept>        //for exception
#include <initializer_list> //for intializer list
#include "iterator_linked_list.h"

/// @brief stores homogeneous data in a linear linked_list.
/// @tparam T data type to be stored
template <typename T>
class linked_list
{
private:
	class node // base class for node container
	{
	public:
		T m_data{};
		node* m_next{};

		node() = default;
		node(T&& d, node* n = nullptr) : m_data(std::move(d)), m_next(n) {}
		node(const T& d, node* n = nullptr) : m_data(d), m_next(n) {}
	};

	// data
	node* m_head{}; // stores head of the list
	size_t sz{};  // size of the list

public:
	// iterator 
	using iterator = base_iterator<node, T>;
	iterator begin() noexcept { return iterator(m_head); }
	iterator end() noexcept { return iterator(nullptr); }

	// const iterator
	using const_iterator = const_base_iterator<node, T>;
	const_iterator cbegin() const noexcept { return const_iterator(m_head); }
	const_iterator cend() const noexcept { return const_iterator(nullptr); }

	// constructors
	linked_list() = default;
	linked_list(int size, const T& init);
	linked_list(const T& d);
	linked_list(T&& d);
	linked_list(const linked_list& l) : linked_list(l.cbegin(), l.cend()) {}
	linked_list(linked_list&& l);
	template <typename itr>
	linked_list(itr first, itr last);
	linked_list(const std::initializer_list<T>& list) : linked_list(list.begin(), list.end()) {}

	// assignment operator
	linked_list& operator=(const linked_list& l);
	linked_list& operator=(linked_list&& l) noexcept;

	// insert
	template <typename itr>
	void insert(iterator position, itr source_start, itr source_end);
	void insert(iterator position, linked_list& source);
	void insert(iterator position, std::initializer_list<T> il);

	// and pop
	void push_front(const T& d)
	{
		m_head = new node(d, m_head);
		sz++;
	}
	void push_front(T&& d)
	{
		m_head = new node(std::move(d), m_head);
		sz++;
	}
	void pop_front();

	// swap
	void swap(linked_list& l) noexcept;
	// erase
	void erase(iterator position, iterator last = iterator(nullptr));

	// search
	iterator find(const T& value, const_iterator start, const_iterator end = const_iterator(nullptr)) const;

	// compare
	bool operator==(const linked_list& l) const;
	bool operator!=(const linked_list& l) const { return !this->operator==(l); }

	// size
	constexpr size_t size() const noexcept { return sz; }
	constexpr bool empty() const noexcept { return sz == 0; }

	// destructor
	void clear() noexcept;
	~linked_list() { clear(); }
};
