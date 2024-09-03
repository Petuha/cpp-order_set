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
	if (!ptr) {
		throw std::runtime_error("Increment null iterator");
		return;
	}
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
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_lower_bound(const T& key)
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
	ptr = y;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_upper_bound(const T& key)
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
	if (ptr == TNULL) {
		throw std::runtime_error("Increment null iterator");
		return *this;
	}
	find_next();
	return *this;
}

template<class T, class CMP>
inline const class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::ConstRedBlackIterator::operator++(int) {
	if (ptr == TNULL) {
		throw std::runtime_error("Increment null iterator");
		return *this;
	}
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
	if (!ptr) {
		ptr = prev_ptr;
		throw std::runtime_error("Decrement begin iterator");
	}
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
	if (!ptr) {
		ptr = res.ptr;
		throw std::runtime_error("Decrement begin iterator");
	}
	return res;
}

