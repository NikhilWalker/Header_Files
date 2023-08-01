#pragma once

// class iterator is used for traversing the list

#include <stdexcept>

template <typename T>
class doubly_linked_list;

/// @brief base class for constant_iterators
/// @tparam iterator_tag iterator can be of six or five types i.e. input,output,forward,bidirectional,random_access,contiguous
/// @tparam node node container
/// @tparam T value type
/// increment is defined
template <typename node, typename T>
class const_base_iterator
{
protected:
    node* m_node{};
    friend doubly_linked_list<T>;
public:
    using iterator_category = std::bidirectional_iterator_tag;
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
    const_base_iterator& operator--()
    {
        m_node = m_node->m_prev;
        return *this;
    }
    const_base_iterator operator--(int)
    {
        const_base_iterator temp(*this);
        m_node = m_node->m_prev;
        return temp;
    }

    // comparison
    constexpr bool operator==(const_base_iterator other) const noexcept { return m_node == other.m_node; }
    constexpr bool operator!=(const_base_iterator other) const noexcept { return m_node != other.m_node; }

    // dereferencing
    const T& operator*() const { return m_node->m_data; }
    const T* operator->() const { return &(m_node->m_data); }
};

/// @brief base class for iterators
/// @tparam iterator_tag iterator can be of six or five types i.e. input,output,forward,bidirectional,random_access,contiguous
/// @tparam node node container
/// @tparam T value type
/// increment is defined
template <typename node, typename T>
class base_iterator : public const_base_iterator< node, T>
{
protected:
    // tags
    using const_base_iterator<node, T>::m_node;
    friend doubly_linked_list<T>;
public:
    using iterator_category = std::bidirectional_iterator_tag;

    // constructors
    base_iterator() = default;
    base_iterator(const base_iterator& itr) { m_node = itr.m_node; }
    explicit base_iterator(node* n) { m_node = n; }

    T& operator*() { return m_node->m_data; }
    T* operator->() { return &(m_node->m_data); }
};


template <typename node, typename T>
class const_reverse_base_iterator : public const_base_iterator<node, T>
{
protected:
    using const_base_iterator<node, T>::m_node;
    friend doubly_linked_list<T>;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    const_reverse_base_iterator() = default;
    explicit const_reverse_base_iterator(node* n) { m_node = n; }
    const_reverse_base_iterator(const const_reverse_base_iterator& itr) { m_node = itr.m_node; }
    const_reverse_base_iterator& operator--()
    {
        m_node = m_node->m_next; // Move to the next node (which is actually the previous node in reverse)
        return *this;
    }
    const_reverse_base_iterator operator--(int)
    {
        const_reverse_base_iterator temp(*this);
        m_node = m_node->m_next; // Move to the next node (which is actually the previous node in reverse)
        return temp;
    }
    const_reverse_base_iterator& operator++()
    {
        m_node = m_node->m_prev; // Move to the previous node (which is actually the next node in reverse)
        return *this;
    }
    const_reverse_base_iterator operator++(int)
    {
        const_reverse_base_iterator temp(*this);
        m_node = m_node->m_prev; // Move to the previous node (which is actually the next node in reverse)
        return temp;
    }
};

template <typename node, typename T>
class reverse_base_iterator : public const_reverse_base_iterator<node, T>
{
protected:
    using const_reverse_base_iterator<node, T>::m_node;
    friend doubly_linked_list<T>;
public:
    using iterator_category = std::bidirectional_iterator_tag;

    reverse_base_iterator() = default;
    explicit reverse_base_iterator(node* n) { m_node = n; }
    reverse_base_iterator(const reverse_base_iterator& itr) { m_node = itr.m_node; }
    T& operator*()
    {
        return m_node->m_data;
    }
    T* operator->()
    {
        return &(m_node->m_data);
    }
};
