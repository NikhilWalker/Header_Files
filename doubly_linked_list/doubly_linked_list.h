#pragma once

// doubly linked list (dll) is a linear data structure used to store data in memory efficient way
//  for example the int data is stores in this library as
/*
data is 1 2 3 4 5
dll is
    nullptr <- 1 <-> 2 <-> 3 <-> 4 <-> 5 -> nullptr
*/

#include <string>
#include <stdexcept> //for exception
#include <initializer_list>
#include "iterator_doubly_linked_list.h"


// these are Doxygen comments used for documentation of class, function or anything in language
/// @brief stores homogeneous data in a doubly_linked_list
/// @tparam T data type need to be stored
template <typename T>
class doubly_linked_list
{
private:
    class node
    {
    public:
        T m_data;     /**< The data stored in the node. */
        node* m_next; /**< Pointer to the next node in the list. */
        node* m_prev; /**< Pointer to the previous node in the list. */

        node() : m_data{}, m_next(nullptr), m_prev(nullptr) {}
        node(T&& d) : m_data(std::move(d)), m_prev(nullptr), m_next(nullptr) {}
        node(const T& d, node* n = nullptr, node* p = nullptr) : m_data(d), m_next(n), m_prev(p) {}
    };

    node* m_head{}; // stores head of dll
    node* m_tail{}; // stores tail of dll
    size_t sz{};

public:
    //iterators
    using iterator = base_iterator<node, T>;
    using const_iterator = const_base_iterator<node, T>;
    using reverse_iterator = reverse_base_iterator<node, T>;
    using const_reverse_iterator = const_reverse_base_iterator<node, T>;

    iterator begin() noexcept { return iterator(m_head); }
    iterator end() noexcept { return iterator(nullptr); }
    const_iterator cbegin() const noexcept { return const_iterator(m_head); }
    const_iterator cend() const noexcept { return const_iterator(nullptr); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(m_tail); }
    reverse_iterator rend() noexcept { return reverse_iterator(nullptr); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_tail); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(nullptr); }

    // constructors
    doubly_linked_list() = default;
    doubly_linked_list(int size, const T& init); // create nodes and initialise them with init O(n)
    doubly_linked_list(const T& d)
    {
        m_tail = m_head = new node(d);
        sz = 1;
    }
    doubly_linked_list(T&& d)
    {
        m_tail = m_head = new node(std::move(d));
        sz = 1;
    }

    doubly_linked_list(const doubly_linked_list& l) : doubly_linked_list(l.cbegin(), l.cend()) {} // copy constructor for static objects O(n)
    doubly_linked_list(doubly_linked_list&& l) noexcept;

    template <typename itr>
    doubly_linked_list(itr first, itr last);
    doubly_linked_list(const std::initializer_list<T>& il) : doubly_linked_list(il.begin(), il.end()) {} // intialise the linked list from intitalizer list

    // = operator
    void operator=(const doubly_linked_list& l);
    void operator=(doubly_linked_list&& l);

    // push and pop
    void push_front(const T& d)
    {
        m_head = new node(d, m_head, nullptr);
        if (m_head->m_next)
            m_head->m_next->m_prev = m_head;
        if (m_tail == nullptr)
            m_tail = m_head;
        sz++;
    }
    void push_front(T&& d)
    {
        m_head = new node(std::move(d), m_head, nullptr);
        if (m_head->m_next)
            m_head->m_next->m_prev = m_head;
        if (m_tail == nullptr)
            m_tail = m_head;
        sz++;
    }
    void pop_front()
    {
        if (this->empty())
            throw std::logic_error("tried to delete a node from empty list");
        node* temp = m_head;
        m_head = m_head->m_next;
        if (m_head != nullptr)
            m_head->m_prev = nullptr;
        delete temp;
        if (--sz == 0)
            m_tail = nullptr;
    }
    void push_back(const T& d)
    {
        m_tail = new node(d, nullptr, m_tail);
        if (m_tail->m_prev)
            m_tail->m_prev->m_next = m_tail;
        if (m_head == nullptr)
            m_head = m_tail;
        sz++;
    }
    void push_back(T&& d)
    {
        m_tail = new node(std::move(d), nullptr, m_tail);
        if (m_tail->m_prev)
            m_tail->m_prev->m_next = m_tail;
        if (m_head == nullptr)
            m_head = m_tail;
        sz++;
    }
    void pop_back()
    {
        if (this->empty())
            throw std::logic_error("tried to delete a node from empty list");
        node* temp = m_tail;
        m_tail = m_tail->m_prev;
        if (m_tail != nullptr)
            m_tail->m_next = nullptr;
        delete temp;
        if (--sz == 0)
            m_head = nullptr;
    }

    // swap
    void swap(doubly_linked_list& l1) noexcept;

    // insert
    /**
     * @brief Inserts elements into the doubly linked list from the given range of iterators.
     *
     * This function inserts elements into the linked list from the range [first, last). It properly
     * updates the links between nodes to include the new elements.
     *
     * @tparam itr The type of iterator used to traverse the range [first, last).
     * @param position An iterator pointing to the position where the new elements will be inserted.
     * @param first The beginning of the range of elements to be inserted.
     * @param last The position just past the last element in the range to be inserted.
     */
    template <typename itr>
    void insert(iterator position, itr first, itr last);
    void insert(iterator position, doubly_linked_list& source)
    {
        insert(position, source.cbegin(), source.cend());
    }
    void insert(iterator position, std::initializer_list<T> il)
    {
        insert(position, il.begin(), il.end());
    }

    void erase(iterator position, iterator last = iterator(nullptr));
    void erase(reverse_iterator position, reverse_iterator last = reverse_iterator(nullptr));

    // compare
    bool operator==(const doubly_linked_list& l) const;
    bool operator!=(const doubly_linked_list& l) const
    {
        return !this->operator==(l);
    }

    // find
    iterator find(const T& value, const_iterator start, const_iterator end = const_iterator(nullptr)) const;

    // size
    constexpr size_t size() const noexcept { return sz; }     // return size of dll
    constexpr bool empty() const noexcept { return sz == 0; } // return if the object is empty or not

    void clear() noexcept;
    ~doubly_linked_list() { clear(); }
};


