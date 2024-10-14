#pragma once

#include "RedBlackTree.h"

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_min()
{
	while (ptr->left != TNULL) ptr = ptr->left;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_max()
{
	while (ptr->right != TNULL) ptr = ptr->right;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_next()
{
	if (ptr == nullptr || ptr == TNULL) return;
	if (ptr->right != TNULL) {
		ptr = ptr->right;
		find_min();
		return;
	}
	Node* y = ptr->parent;
	while (y != nullptr && ptr == y->right) {
		ptr = y;
		y = y->parent;
	}
	ptr = y;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_prev()
{
	if (ptr->left != TNULL) {
		ptr = ptr->left;
		find_max();
		return;
	}
	Node* y = ptr->parent;
	while (y != nullptr && ptr == y->left) {
		ptr = y;
		y = y->parent;
	}
	ptr = y;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::ConstRedBlackIterator::ConstRedBlackIterator(Node* ptr, Node* TNULL, Node* root) {
	this->ptr = ptr;
	this->TNULL = TNULL;
	this->root = root;
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::ConstRedBlackIterator::operator==(const ConstRedBlackIterator& rhs) const
{
	return ptr == rhs.ptr;
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::ConstRedBlackIterator::operator!=(const ConstRedBlackIterator& rhs) const
{
	return ptr != rhs.ptr;
}

template<class T, class CMP>
inline const T& RedBlackTree<T, CMP>::ConstRedBlackIterator::operator*() const
{
	return ptr->data;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator& RedBlackTree<T, CMP>::ConstRedBlackIterator::operator++() {
	if (ptr == nullptr || ptr == TNULL) return *this;
	find_next();
	return *this;
}

template<class T, class CMP>
inline const class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::ConstRedBlackIterator::operator++(int) {
	ConstRedBlackIterator res(*this);
	find_next();
	return res;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator& RedBlackTree<T, CMP>::ConstRedBlackIterator::operator--() {
	Node* prev_ptr = ptr;
	if (ptr == nullptr) {
		ptr = root;
		find_max();
		return *this;
	}
	find_prev();
	if (!ptr) ptr = prev_ptr;
	return *this;
}

template<class T, class CMP>
inline const class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::ConstRedBlackIterator::operator--(int)
{
	ConstRedBlackIterator res(*this);
	if (ptr == nullptr) {
		ptr = root;
		find_max();
		return res;
	}
	find_prev();
	if (!ptr) ptr = res.ptr;
	return res;
}

template<class T, class CMP>
inline size_t RedBlackTree<T, CMP>::ConstRedBlackIterator::order()
{
	Node* p = ptr;
	size_t i = 0;
	if (!p) {
		p = root;
		while (p != TNULL) {
			i += p->cnt + 1;
			p = p->right;
		}
	}
	else {
		i = p->cnt;
		while (p != root) {
			if (p->parent->right == p) i += p->parent->cnt + 1;
			p = p->parent;
		}
	}
	return i;
}
