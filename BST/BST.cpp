// BST.cpp

#include <queue>
#include "BST.h"

//constructors

template<typename T>
template<typename itr>
inline BST<T>::BST(itr start, itr end)
{
	while (start != end)
	{
		this->insert(*start);
	}
}

template<typename T>
BST<T>::BST(std::initializer_list<T> il)
{
	for (auto itr : il)
		insert(std::move(itr));
}

//insert
template <typename T>
void BST<T>::insert(const T& d)
{
	//if the tree is empty than push at root
	if (m_root == nullptr)
	{
		m_root = new node(d);
		return;
	}
	//find the position where the node should be inserted
	node* temp = find(d, const_iterator(m_root)).m_node;

	//if the node and the data equal insert at right
	if (temp->m_data == d)
	{
		temp->m_right = new node(d, temp->m_left, temp->m_right);
		temp->m_left = nullptr;
	}

	//check if the node is smaller than data than insert the data on right else left
	if (d > temp->m_data && temp->m_right == nullptr)
		temp->m_right = new node(d);
	else if (temp->m_left == nullptr)
		temp->m_left = new node(d);

	//if both the node is not empty than there is error in logic must be solved
	else
		throw std::logic_error("Inserting at non-empty place");
}

template<typename T>
typename BST<T>::iterator BST<T>::find(const T& d, iterator root)
{
	return iterator(find(d, const_iterator(root.m_node)).m_node);
}

//find
template <typename T>
typename BST<T>::iterator BST<T>::find_min(iterator root) noexcept
{
	return iterator(find_min(const_iterator(root.m_node)).m_node);
}

template <typename T>
typename BST<T>::const_iterator BST<T>::find_min(const_iterator root) const noexcept
{
	if (root.m_node == nullptr)
		return root;
	while (root.m_node->m_left != nullptr)
	{
		root.m_node = root.m_node->m_left;
	}
	return root;
}
template<typename T>
typename BST<T>::iterator BST<T>::find_parent(iterator root)
{
	return iterator(find_parent(const_iterator(root.m_node)).m_node);
}
template<typename T>
typename BST<T>::const_iterator BST<T>::find_parent(const_iterator root) const
{
	// return null const_iterator when the node equals root node of tree or the root is nullptr
	if (root.m_node == nullptr || root == this->root() || m_root == nullptr)
		return const_iterator(nullptr);
	const_iterator parent;
	const_iterator temp = this->root();
	while (1)
	{
		parent = temp;
		//if left tree exist and the node is greater than data
		if (temp.m_node->m_left && temp.m_node->m_data > root.m_node->m_data)
			temp.m_node = temp.m_node->m_left;
		// if right tree exist and the node is smaller than data
		else if (temp.m_node->m_right && temp.m_node->m_data <= root.m_node->m_data)
			temp.m_node = temp.m_node->m_right;
		// if leaf node
		else
			throw std::logic_error("node is in another tree");
		//compare
		if (temp == root)
			return parent;
	}
}
//return iterator to the node if found or return the last node
// throws exception if the given node is nullptr
template <typename T>
typename BST<T>::const_iterator BST<T>::find(const T& d, const_iterator root) const
{
	//check if it is null
	if (root.m_node == nullptr)
		return const_iterator(nullptr);
	while (1)
	{
		//if left tree exist and the node is greater than data
		if (root.m_node->m_left && root.m_node->m_data > d)
			root.m_node = root.m_node->m_left;
		// if right tree exist and the node is smaller than data
		else if (root.m_node->m_right && root.m_node->m_data < d)
			root.m_node = root.m_node->m_right;
		// if leaf node or equal node
		else
			return root;
	}
}

template <typename T>
void BST<T>::insert(T&& d) noexcept
{
	//same logic but use std::move() function
	if (m_root == nullptr)
	{
		m_root = new node(std::move(d));
		return;
	}
	node* temp = find(d, const_iterator(m_root)).m_node;
	if (temp->m_data == d)
	{
		temp->m_right = new node(std::move(d), temp->m_left, temp->m_right);
		temp->m_left = nullptr;
	}
	if (d > temp->m_data && temp->m_right == nullptr)
		temp->m_right = new node(std::move(d));
	else if (temp->m_left == nullptr)
		temp->m_left = new node(std::move(d));
	else
		throw std::logic_error("Inserting at non-empty place");
}

// Function to delete a node with the given data from the BST
template<typename T>
typename BST<T>::iterator BST<T>::delete_node(const T& key)
{
	iterator itr = find(key, this->root());
	if (itr.m_node == nullptr || itr.m_node->m_data != key)
		return itr;
	else
		return delete_node(itr);
}

template<typename T>
typename BST<T>::iterator BST<T>::delete_node(iterator root)
{
	// check if the root and given node is not null
	if (root.m_node == nullptr || m_root == nullptr)
		return root;

	// Case 1: Node with only one child or no child
	if (root.m_node->m_left == nullptr)
	{
		iterator parent = find_parent(root);
		node** ptr;
		if (parent.m_node == nullptr)
			ptr = &m_root;
		else
			ptr = (parent.m_node->m_left == root.m_node) ? &(parent.m_node->m_left) : &(parent.m_node->m_right);
		*ptr = root.m_node->m_right;
		root.m_node->m_right = nullptr;
		delete root.m_node;
		return iterator(*ptr);
	}
	else	if (root.m_node->m_right == nullptr)
	{
		iterator parent = find_parent(root);
		node** ptr;
		if (parent.m_node == nullptr)
			ptr = &m_root;
		else
			ptr = (parent.m_node->m_left == root.m_node) ? &(parent.m_node->m_left) : &(parent.m_node->m_right);
		*ptr = root.m_node->m_left;
		root.m_node->m_left = nullptr;
		delete root.m_node;
		return iterator(*ptr);
	}

	// Case 2: Node with two children
	// Find smallest in the right subtree
	iterator temp = find_min(root.m_node->m_right);

	// Copy the inorder successor's data to this node
	root.m_node->m_data = std::move(temp.m_node->m_data);

	// Delete the inorder successor
	delete_node(temp);
	return root;
}

//access element
template<typename T>
void BST<T>::levelorder_(std::vector<T*>& res) noexcept
{
	std::queue<iterator> q;
	if (m_root == nullptr)
		return;

	q.push(root());
	while (!q.empty())
	{
		iterator current = q.front();
		q.pop();
		res.push_back(&(current.m_node->m_data));

		if (current.m_node->m_left != nullptr)
		{
			q.push(current.left());
		}
		if (current.m_node->m_right != nullptr)
		{
			q.push(current.right());
		}
	}
}
template <typename T>
void BST<T>::levelorder_(std::vector<const T*>& res) const noexcept
{
	std::queue<const_iterator> q;
	if (root.m_node == nullptr)
		return;

	q.push(root());
	while (!q.empty())
	{
		const_iterator current = q.front();
		q.pop();
		res.push_back(&(current.m_node->m_data));

		if (current.m_node->m_left != nullptr)
		{
			q.push(current.left());
		}
		if (current.m_node->m_right != nullptr)
		{
			q.push(current.right());
		}
	}
}


template <typename T>
void BST<T>::clear(iterator root)
{
	if (root.m_node)
	{
		delete root.m_node->m_left;
		delete root.m_node->m_right;
		root.m_node->m_left = nullptr;
		root.m_node->m_right = nullptr;
	}
}

