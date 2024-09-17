#pragma once
#include "RedBlackTree.h"

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::leftRotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != TNULL) y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr) this->root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
	y->cnt += x->cnt + 1;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::rightRotate(Node* x)
{
	Node* y = x->left;
	x->left = y->right;
	if (y->right != TNULL) y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr) this->root = y;
	else if (x == x->parent->right) x->parent->right = y;
	else x->parent->left = y;
	y->right = x;
	x->parent = y;
	x->cnt -= y->cnt + 1;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::fixDelete(Node* x)
{
	Node* s;
	while (x != root && x->color == 0) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == 1) {
				s->color = 0;
				x->parent->color = 1;
				leftRotate(x->parent);
				s = x->parent->right;
			}
			if (s->left->color == 0 && s->right->color == 0) {
				s->color = 1;
				x = x->parent;
			}
			else {
				if (s->right->color == 0) {
					s->left->color = 0;
					s->color = 1;
					rightRotate(s);
					s = x->parent->right;
				}
				s->color = x->parent->color;
				x->parent->color = 0;
				s->right->color = 0;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			s = x->parent->left;
			if (s->color == 1) {
				s->color = 0;
				x->parent->color = 1;
				rightRotate(x->parent);
				s = x->parent->left;
			}
			if (s->left->color == 0 && s->right->color == 0) {
				s->color = 1;
				x = x->parent;
			}
			else {
				if (s->left->color == 0) {
					s->right->color = 0;
					s->color = 1;
					leftRotate(s);
					s = x->parent->left;
				}
				s->color = x->parent->color;
				x->parent->color = 0;
				s->left->color = 0;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 0;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::rbTransplant(Node* u, Node* v)
{
	if (u->parent == nullptr) this->root = v;
	else if (u == u->parent->left) u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::fixInsert(Node* k)
{
	Node* u;
	while (k->parent->color == 1) {
		if (k->parent == k->parent->parent->right) {
			u = k->parent->parent->left;
			if (u->color == 1) {
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->left) {
					k = k->parent;
					rightRotate(k);
				}
				k->parent->color = 0;
				k->parent->parent->color = 1;
				leftRotate(k->parent->parent);
			}
		}
		else {
			u = k->parent->parent->right;
			if (u->color == 1) {
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->right) {
					k = k->parent;
					leftRotate(k);
				}
				k->parent->color = 0;
				k->parent->parent->color = 1;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root) break;
	}
	root->color = 0;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::free_node(Node* ptr)
{
	if (ptr->left != TNULL) free_node(ptr->left);
	if (ptr->right != TNULL) free_node(ptr->right);
	delete ptr;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::copy_tree(Node* dst, Node* src, Node* otherTNULL, Node* parent)
{
	dst->data = src->data;
	dst->color = src->color;
	dst->cnt = src->cnt;
	dst->parent = parent;
	if (src->right == otherTNULL) dst->right = TNULL;
	else {
		dst->right = new Node;
		copy_tree(dst->right, src->right, otherTNULL, dst);
	}
	if (src->left == otherTNULL) dst->left = TNULL;
	else {
		dst->left = new Node;
		copy_tree(dst->left, src->left, otherTNULL, dst);
	}
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase_helper(Node* z)
{
	Node* x;
	Node* y;
	y = z;
	bool y_original_color = y->color;
	if (z->left == TNULL) {
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == TNULL) {
		x = z->left;
		rbTransplant(z, z->left);
	}
	else {
		y = z->right;
		while (y->left != TNULL) {
			y->cnt--;
			y = y->left;
		}
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) x->parent = y;
		else {
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
		y->cnt = z->cnt + 1;
	}
	delete z;
	if (y_original_color == 0) fixDelete(x);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree()
{
	TNULL = new Node;
	TNULL->color = 0;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->cnt = -1;
	root = TNULL;
	elements = 0;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(const std::initializer_list<T>& l) : RedBlackTree()
{
	for (auto& now : l) insert(now);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(const RedBlackTree<T, CMP>& rhs) : RedBlackTree()
{
	elements = rhs.elements;
	if (rhs.root != rhs.TNULL) {
		root = new Node;
		copy_tree(root, rhs.root, rhs.TNULL, nullptr);
	}
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(RedBlackTree<T, CMP>&& rhs) noexcept
{
	TNULL = rhs.TNULL;
	root = rhs.root;
	elements = rhs.elements;
	rhs.root = rhs.TNULL = nullptr;
	rhs.elements = 0;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>& RedBlackTree<T, CMP>::operator=(const RedBlackTree<T, CMP>& rhs)
{
	if (this == &rhs) return *this;
	if (this->root != TNULL) free_node(this->root);
	elements = rhs.elements;
	if (rhs.root != rhs.TNULL) {
		root = new Node;
		copy_tree(root, rhs.root, rhs.TNULL, nullptr);
	}
	else root = TNULL;
	return *this;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>& RedBlackTree<T, CMP>::operator=(RedBlackTree<T, CMP>&& rhs) noexcept
{
	if (this == &rhs) return *this;
	if (this->root != TNULL) free_node(this->root);
	delete TNULL;
	TNULL = rhs.TNULL;
	root = rhs.root;
	elements = rhs.elements;
	rhs.root = rhs.TNULL = nullptr;
	rhs.elements = 0;
	return *this;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::insert(const T& key)
{
	elements++;
	Node* node = new Node;
	node->parent = nullptr;
	node->data = key;
	node->left = TNULL;
	node->right = TNULL;
	node->color = 1;
	Node* y = nullptr;
	Node* x = this->root;
	while (x != TNULL) {
		y = x;
		if (CMP{}(node->data, x->data)) {
			x->cnt++;
			x = x->left;
		}
		else if (node->data == x->data) {
			delete node;
			elements--;
			while (x->parent != nullptr) {
				if (x == x->parent->left) x->parent->cnt--;
				x = x->parent;
			}
			return;
		}
		else x = x->right;
	}
	node->parent = y;
	node->cnt = node->left->cnt + 1;
	if (y == nullptr) root = node;
	else if (CMP{}(node->data, y->data)) y->left = node;
	else y->right = node;
	if (node->parent == nullptr) {
		node->color = 0;
		return;
	}
	if (node->parent->parent == nullptr) {
		return;
	}
	fixInsert(node);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase(const T& key)
{
	if (elements == 0) return;
	elements--;
	Node* node = this->root;
	Node* z = TNULL;
	Node* x;
	Node* y = nullptr;
	while (node != TNULL) {
		y = node;
		if (node->data == key) z = node;
		if (CMP{}(node->data, key)) {
			node = node->right;
		}
		else {
			node->cnt--;
			node = node->left;
		}
	}
	if (z == TNULL) {
		elements++;
		if (CMP{}(key, y->data)) y->cnt++;
		while (y->parent != nullptr) {
			if (y == y->parent->left) y->parent->cnt++;
			y = y->parent;
		};
		return;
	}
	erase_helper(z);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase(const_iterator it)
{
	if (it.ptr == nullptr || it.ptr == TNULL) return;
	elements--;
	Node* p = it.ptr;
	p->cnt--;
	while (p->parent != nullptr) {
		if (p == p->parent->left) p->parent->cnt--;
		p = p->parent;
	}
	erase_helper(it.ptr);
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::const_iterator RedBlackTree<T, CMP>::begin() const
{
	if (root == TNULL) return end();
	const_iterator it(root, TNULL, root);
	it.find_min();
	return it;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::const_iterator RedBlackTree<T, CMP>::end() const
{
	return const_iterator(nullptr, TNULL, root);
}

template<class T, class CMP>
inline size_t RedBlackTree<T, CMP>::size() const
{
	return elements;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::const_iterator RedBlackTree<T, CMP>::find(const T& key) const
{
	Node* node = this->root;
	Node* z = TNULL;
	while (node != TNULL) {
		if (node->data == key) z = node;
		if (CMP{}(node->data, key)) node = node->right;
		else node = node->left;
	}
	if (z == TNULL) return end();
	return const_iterator(z, TNULL, root);
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::const_iterator RedBlackTree<T, CMP>::lower_bound(const T& key) const
{
	Node* p = root;
	Node* y = nullptr;
	while (p != TNULL) {
		if (CMP{}(p->data, key)) p = p->right;
		else {
			if (y == nullptr) y = p;
			else y = (CMP{}(p->data, y->data) ? p : y);
			p = p->left;
		}
	}
	return const_iterator(y, TNULL, root);
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::const_iterator RedBlackTree<T, CMP>::upper_bound(const T& key) const
{
	Node* p = root;
	Node* y = nullptr;
	while (p != TNULL) {
		if (!CMP{}(key, p->data)) p = p->right;
		else {
			if (y == nullptr) y = p;
			else y = (!CMP{}(y->data, p->data) ? p : y);
			p = p->left;
		}
	}
	return const_iterator (y, TNULL, root);
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::const_iterator RedBlackTree<T, CMP>::find_by_order(size_t i) const
{
	if (i >= elements) return end();
	Node* p = this->root;
	while (p != TNULL && p->cnt != i) {
		if (p->cnt < i) {
			i -= p->cnt + 1;
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return const_iterator(p, TNULL, root);
}

template<class T, class CMP>
inline size_t RedBlackTree<T, CMP>::order_of_key(const T& x) const
{
	Node* p = this->root;
	size_t i = 0;
	while (p != TNULL && p->data != x) {
		if (CMP{}(x, p->data)) p = p->left;
		else {
			i += p->cnt + 1;
			p = p->right;
		}
	}
	if (p == TNULL) return elements;
	i += p->cnt;
	return i;
}

template<class T, class CMP>
inline size_t RedBlackTree<T, CMP>::order_of_key(const const_iterator& it) const
{
	return it.order();
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::operator==(const RedBlackTree<T, CMP>& rhs) const
{
	if (elements != rhs.elements) return 0;
	auto it1 = begin(), it2 = rhs.begin();
	while (it1 != end()) {
		if (*it1 != *it2) return 0;
		it1++;
		it2++;
	}
	return 1;
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::operator!=(const RedBlackTree<T, CMP>& rhs) const
{
	if (elements != rhs.elements) return 1;
	auto it1 = begin(), it2 = rhs.begin();
	while (it1 != end()) {
		if (*it1 != *it2) return 1;
		it1++;
		it2++;
	}
	return 0;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::~RedBlackTree()
{
	if (this->root != TNULL) free_node(this->root);
	delete TNULL;
}

