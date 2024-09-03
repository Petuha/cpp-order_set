#pragma once
#include <functional>
#include <initializer_list>
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <format>

template<class T, class CMP = std::less<T>>
class RedBlackTree {
private:
	//Node
	struct Node {
		T data; // holds the key
		Node* parent; // pointer to the parent
		Node* left; // pointer to left child
		Node* right; // pointer to right child
		bool color; // 1 -> Red, 0 -> Black
		size_t cnt; // elements in the left sub-tree
	};
	//Iterator
	class ConstRedBlackIterator { //унаследоваться, добавить удовлетворение требованиям random access iterator
	private:
		Node* ptr;
		Node* TNULL;
		Node* root;
		friend class RedBlackTree;

		void find_min();
		void find_max();
		void find_next();
		void find_prev();
		void find_lower_bound(const T& key);
		void find_upper_bound(const T& key);
	public:
		ConstRedBlackIterator(Node* ptr = 0, Node* TNULL = 0, Node* root = 0);
		bool operator== (const ConstRedBlackIterator& rhs) const;
		bool operator!= (const ConstRedBlackIterator& rhs) const;
		const T& operator*() const;
		ConstRedBlackIterator& operator++ ();
		const ConstRedBlackIterator operator++ (int);
		ConstRedBlackIterator& operator-- ();
		const ConstRedBlackIterator operator-- (int);
	};
	//Tree
	Node* root;
	Node* TNULL;
	size_t elements;
	void leftRotate(Node* x);
	void rightRotate(Node* x);
	void fixDelete(Node* x);
	void rbTransplant(Node* u, Node* v);
	void fixInsert(Node* k);
	void free_node(Node* ptr);
	void copy_tree(Node* dst, Node* src, Node* otherTNULL, Node* parent);
	void erase_helper(Node* z);
public:

	void phelp(Node* p, int i, std::ofstream& fout) {
		if (p->color == 1) fout << format("{} [label={},style=filled,color=red];\n", i, p->data);
		else fout << format("{} [label={}];\n", i, p->data);
		if (p->left != TNULL) {
			fout << format("{}->{}", i, 2 * i + 1);
			phelp(p->left, 2 * i + 1, fout);
		}
		if (p->right != TNULL) {
			fout << format("{}->{}", i, 2 * i + 2);
			phelp(p->right, 2 * i + 2, fout);
		}
	}
	void print_to_ostream() {
		std::ofstream fout("1.txt");
		fout << "digraph G {\n";
		phelp(root, 0, fout);
		fout << "}";
		fout.close();
	}

	using const_iterator = ConstRedBlackIterator;
	RedBlackTree();
	RedBlackTree(const std::initializer_list<T>& l);
	RedBlackTree(const RedBlackTree<T, CMP>& rhs);
	RedBlackTree(RedBlackTree<T, CMP>&& rhs);
	RedBlackTree<T, CMP>& operator=(const RedBlackTree<T, CMP>& rhs);
	RedBlackTree<T, CMP>& operator=(RedBlackTree<T, CMP>&& rhs) noexcept;
	void insert(const T& key);
	void erase(const T& key);
	void erase(const_iterator it);
	const_iterator begin() const;
	const_iterator end() const;
	size_t size() const;
	const_iterator find(const T& key) const;
	const_iterator lower_bound(const T& key) const;
	const_iterator upper_bound(const T& key) const;
	const_iterator find_by_order(size_t i) const;
	size_t order_of_key(const T& x) const;
	~RedBlackTree();
};

#include "RedBlackTreeImplementation.h"
#include "ConstRedBlackIterator.h"