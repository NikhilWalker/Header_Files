// linked_list.cpp

#include "linked_list.h"

// constructors
template <typename T>
linked_list<T>::linked_list(std::initializer_list<T>& il)
{
    for (auto it : il)
        push_front(std::move(it));
}

template <typename T>
linked_list<T>::linked_list(const T& d)
{
    m_head = new node(d);
    sz = 1;
}
template <typename T>
linked_list<T>::linked_list(T&& d)
{
    m_head = new node(std::move(d));
    sz = 1;
}
template <typename T>
linked_list<T>::linked_list(linked_list&& l)
{
    m_head = l.m_head;
    sz = l.sz;
    l.m_head = nullptr;
    sz = 0;
}
template <typename T>
linked_list<T>::linked_list(int size, const T& init)
{
    if (size < 1)
        throw std::invalid_argument("Initializing linked list with " + std::to_string(size) + " nodes.");
    sz = size;
    while (size--)
        insert_at_head(init);
}
template <typename T>
template <typename itr>
linked_list<T>::linked_list(itr first, itr last)
{
    if (first == last)
        return;
    m_head = new node(*first++);
    sz++;
    node* temp = m_head;
    for (; first != last; first++)
    {
        temp->m_next = new node(*first);
        sz++;
        temp = temp->m_next;
    }
}

// = operator
template <typename T>
linked_list<T>& linked_list<T>::operator=(const linked_list& l)
{
    clear();
    auto itr = l.cbegin();
    if (l.sz == 0)
        return *this;
    push_front(*itr);
    itr++;
    insert(this->begin(), itr, l.cend());
    return *this;
}
template <typename T>
linked_list<T>& linked_list<T>::operator=(linked_list&& l) noexcept
{
    clear();
    m_head = l.m_head;
    sz = l.sz;
    l.m_head = nullptr;
    sz = 0;
    return *this;
}

// insert
template <typename T>
template <typename itr>
void linked_list<T>::insert(iterator position, itr source_start, itr source_end)
{
    if (source_start == source_end || position == iterator(nullptr))
        return;
    while (source_start != source_end)
    {
        position.m_node->m_next = new node(*source_start++, position.m_node->m_next);
        position++;
        sz++;
    }
}
template <typename T>
void linked_list<T>::insert(iterator position, linked_list& source)
{
    insert(position, source.cbegin(), source.cend());
}
template <typename T>
void linked_list<T>::insert(iterator position, std::initializer_list<T> il)
{
    insert(position, il.begin(), il.end());
}

//pop
template <typename T>
void linked_list<T>::pop_front()
{
    if (this->empty())
        throw std::logic_error("tried to delete a node from empty list");
    node* temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    sz--;
}

// swap
template <typename T>
void linked_list<T>::swap(linked_list& l) noexcept
{
    node* temp = l.m_head;
    l.m_head = m_head;
    m_head = temp;
    // swap size
    size_t t = l.sz;
    l.sz = sz;
    sz = t;
}

// erase
template <typename T>
void linked_list<T>::erase(iterator position, iterator last)
{
    node* temp = position.m_node, * m_prev = nullptr;
    if (temp == m_prev)
        return;
    while (temp != position.m_node && temp != nullptr)
    {
        m_prev = temp;
        temp = temp->m_next;
    }
    if (temp == nullptr)
        return;

    while (temp != last.m_node)
    {
        if (m_prev == nullptr)
            m_head = m_head->m_next;
        else
            m_prev->m_next = temp->m_next;
        position++;
        delete temp;
        temp = position.m_node;
        sz--;
    }
}

// search
template <typename T>
typename linked_list<T>::iterator linked_list<T>::find(const T& value, const_iterator start, const_iterator end) const
{
    while (start != end)
    {
        if (*start == value)
            return iterator(start.m_node);
        start++;
    }
    return iterator(end.m_node);
}

// compare
template <typename T>
bool linked_list<T>::operator==(const linked_list& l) const
{
    if (sz != l.sz)
        return false;
    for (auto itr1 = cbegin(), itr2 = l.cbegin(); itr1 != cend(); itr1++, itr2++)
    {
        if (*itr1 != *itr2)
            return false;
    }
    return true;
}

// destructors
template <typename T>
void linked_list<T>::clear() noexcept
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

