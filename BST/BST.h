#ifndef BST_H__
#define BST_H__ 1

// BST (binary search tree)
/*
for example a BST tree with data 2,1,3
    2       -> root node
   / \
  /   \
 /     \
1       3   -> child nodes

*/

#include <vector>
#include <stdexcept>
#include <initializer_list>
#include "iterator_BST.h"

template <typename T>
class BST
{
protected:
    struct node
    {
        T m_data{};
        node* m_left{};
        node* m_right{};
        node() = default;
        node(const T& d, node* l = nullptr, node* r = nullptr) : m_data(d), m_left(l), m_right(r) {}
        node(T&& d, node* l = nullptr, node* r = nullptr) : m_data(std::move(d)), m_left(l), m_right(r) {}
        node(const node* other) : m_data(other->m_data)
        {
            if (other->m_left)
                m_left = new node(other->m_left);
            if (other->m_right)
                m_right = new node(other->m_right);
        }
        ~node()
        {
            if (m_left)
                delete m_left;
            if (m_right)
                delete m_right;
        }
    };
    node* m_root{};

    //helper
    void levelorder_(std::vector<T*>& res) noexcept;
    void levelorder_(std::vector<const T*>& res) const noexcept;

public:
    // iterators
    using iterator = base_iterator<node, T>;
    using const_iterator = const_base_iterator<node, T>;
    iterator root() noexcept { return iterator(m_root); }
    const_iterator root() const noexcept { return const_iterator(m_root); }

    // constructors
    BST() = default;
    BST(const T& d) : m_root(new node(d)) {}
    BST(T&& d) : m_root(new node(std::move(d))) {}
    BST(const BST& other) : BST(other.root()) {}
    BST(BST&& other) : m_root(other.m_root) { other.m_root = nullptr; }
    BST(const_iterator root) : m_root(new node(root.m_node)) {}
    template<typename itr>
    BST(itr start, itr end);
    BST(std::initializer_list<T> il);

    // size and height
    constexpr size_t size(iterator root) const noexcept
    {
        if (root.m_node == nullptr)
            return 0;
        return 1 + size(root.left()) + size(root.right());
    }
    constexpr size_t height(iterator root) const noexcept
    {
        if (root.m_node == nullptr)
            return 0;
        return std::max(height(root.left()), height(root.right())) + 1;
    }

    // insert and delete
    void insert(const T& d);
    void insert(T&& d) noexcept;
    iterator delete_node(const T& key);
    iterator delete_node(iterator root);

    //access elements
    std::vector<T*> levelorder() noexcept { std::vector<T*> res; levelorder_(res); return res; }
    std::vector<const T*> levelorder() const noexcept { std::vector<const T*> res; levelorder_(res); return res; }

    // find and search
    bool search(const T& d, const_iterator root) const noexcept
    {
        // check if the node is empty
        if (root.m_node == nullptr)
            return false;
        //compare
        if (d == root.m_node->m_data)
            return true;
        //if given data is larger and equal to current node data than search right side else search left side
        return (d >= root.m_node->m_data) ? search(d, root.right()) : search(d, root.left());
    }
    const_iterator find(const T& d, const_iterator root) const;
    iterator find(const T& d, iterator root);
    iterator find_min(iterator root) noexcept;
    const_iterator find_min(const_iterator root) const noexcept;
    iterator find_parent(iterator root);
    const_iterator find_parent(const_iterator root) const;

    // clear
    void clear(iterator root);
    ~BST()
    {
        delete m_root;
    }
};

#endif //BST_H__
