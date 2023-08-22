// doubly_linked_list.cpp

#include "doubly_linked_list.h"

// constructors
template <typename T>
doubly_linked_list<T>::doubly_linked_list(std::initializer_list<T> il)
{
    for (auto it : il)
        push_back(std::move(it));
}

template <typename T>
doubly_linked_list<T>::doubly_linked_list(doubly_linked_list&& l) noexcept
{
    m_head = l.m_head;
    m_tail = l.m_tail;
    sz = l.sz;
    l.m_head = nullptr;
    l.m_tail = nullptr;
    l.sz = 0;
}
template <typename T>
template <typename itr>
doubly_linked_list<T>::doubly_linked_list(itr first, itr last)
{
    if (first == last)
        return;
    m_head = new node(*first++);
    m_tail = m_head;
    sz++;
    for (; first != last; first++)
    {
        m_tail->m_next = new node(*first, nullptr, m_tail);
        sz++;
        m_tail = m_tail->m_next;
    }
}
template <typename T>
doubly_linked_list<T>::doubly_linked_list(int size, const T& init)
{
    if (size < 1)
        throw std::invalid_argument("Initializing linked list with " + std::to_string(size) + " nodes.");
    while (size--)
        push_front(init);
}

// = operator
template <typename T>
void doubly_linked_list<T>::operator=(const doubly_linked_list& l)
{
    for (auto ritr = l.crbegin(); ritr != l.crend(); ritr++)
        push_front(*ritr);
}
template <typename T>
void doubly_linked_list<T>::operator=(doubly_linked_list&& l)
{
    clear();
    m_head = l.m_head;
    m_tail = l.m_tail;
    sz = l.sz;
    l.m_head = nullptr;
    l.m_tail = nullptr;
    l.sz = 0;
}

// swap
template <typename T>
void doubly_linked_list<T>::swap(doubly_linked_list& l1) noexcept
{
    node* temp;
    // swap head
    temp = l1.m_head;
    l1.m_head = m_head;
    m_head = temp;
    // swap tail
    temp = l1.m_tail;
    l1.m_tail = m_tail;
    m_tail = temp;
    // swap size
    size_t t = l1.sz;
    l1.sz = sz;
    sz = t;
}

template <typename T>
template <typename itr>
void doubly_linked_list<T>::insert(iterator position, itr first, itr last)
{
    if (first == last || position == iterator(nullptr))
        return;
    while (first != last)
    {
        position.m_node->m_next = new node(*first++, position.m_node->m_next, position.m_node);
        position++;
        position.m_node->m_next->m_prev = position.m_node;
        sz++;
    }
}

template <typename T>
void doubly_linked_list<T>::erase(iterator position, iterator last)
{
    if (position == last || position == iterator(nullptr))
        return;

    if (position == iterator(this->begin()))
        m_head = last.m_node;

    // Adjust the prev pointer for the node before the erased range.
    if (position.m_node->m_prev != nullptr)
        position.m_node->m_prev->m_next = last.m_node;

    // Adjust the next pointer for the node after the erased range.
    if (last.m_node != nullptr)
        last.m_node->m_prev = position.m_node->m_prev;

    // Traverse the erased range and delete nodes.
    while (position != last)
    {
        iterator m_next = position;
        ++m_next;
        delete position.m_node;
        position = m_next;
        sz--;
    }
}

template <typename T>
void doubly_linked_list<T>::erase(reverse_iterator position, reverse_iterator last)
{
    if (last == reverse_iterator(nullptr))
        last = reverse_iterator(m_head);
    erase(iterator(last.m_node), iterator(position.m_node));
}

// compare
template <typename T>
bool doubly_linked_list<T>::operator==(const doubly_linked_list& l) const
{
    if (sz != l.sz)
        return false;
    for (auto itr1 = cbegin(), itr2 = l.cbegin(); itr1 != cend(); itr1++, itr2++)
    {
        if (!(*itr1 == *itr2))
            return false;
    }
    return true;
}


// search
template <typename T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::find(const T& value, const_iterator start, const_iterator end) const
{
    while (start != end)
    {
        if (*start == value)
            return iterator(start.m_node);
        start++;
    }
    return iterator(end.m_node);
}

//clear
template <typename T>
void doubly_linked_list<T>::clear() noexcept
{
    if (m_head == nullptr)
        return;
    iterator temp = this->begin(), m_prev = temp;
    m_head = nullptr;
    sz = 0;
    while (m_prev != this->end())
    {
        temp++;
        delete m_prev.m_node;
        m_prev = temp;
    }
}
