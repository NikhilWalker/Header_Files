#ifndef ITERATOR_BST_H__
#define ITERATOR_BST_H__ 1
// base Iterators for binary search tree

template <typename T>
class BST;

template <typename node, typename T>
class const_base_iterator
{
protected:
    node* m_node{};
    friend BST<T>;
public:

    const_base_iterator() = default;
    const_base_iterator(const const_base_iterator& other) = default;
    const_base_iterator(node* n) : m_node(n) {}

    const_base_iterator left() const { return const_base_iterator(m_node->m_left); }
    const_base_iterator right() const { return const_base_iterator(m_node->m_right); }

    // comparison
    constexpr bool operator==(const_base_iterator other) const noexcept { return m_node == other.m_node; }
    constexpr bool operator!=(const_base_iterator other) const noexcept { return m_node != other.m_node; }

    // dereferencing
    const T& operator*() const { return m_node->m_data; }
    const T* operator->() const { return &m_node->m_data; }
};

template <typename node, typename T>
class base_iterator : public const_base_iterator<node, T>
{
protected:
    using const_base_iterator<node, T>::m_node;
    friend BST<T>;
public:

    base_iterator() = default;
    base_iterator(const base_iterator& other) : const_base_iterator<node, T>(other) {}
    base_iterator(node* n) { m_node = n; }

    base_iterator left() const { return base_iterator(m_node->m_left); }
    base_iterator right() const { return base_iterator(m_node->m_right); }

    // dereferencing
    T& operator*() { return m_node->m_data; }
    T* operator->() { return &m_node->m_data; }
};
#endif //ITERATOR_BST_H__
