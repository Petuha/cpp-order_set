#pragma once
#include <functional>
#include <initializer_list>
#include <stdexcept>
namespace RedBlack {
	template<class T>
	struct Node {
		T data; // holds the key
		Node* parent; // pointer to the parent
		Node* left; // pointer to left child
		Node* right; // pointer to right child
		bool color; // 1 -> Red, 0 -> Black
		size_t cnt; // elements in the left sub-tree
	};
	template<class T>
	Node<T>* find_min(Node<T>* node, Node<T>* TNULL) {
		while (node->left != TNULL) node = node->left;
		return node;
	}
	template<class T>
	Node<T>* find_max(Node<T>* node, Node<T>* TNULL) {
		while (node->right != TNULL) node = node->right;
		return node;
	}
	template<class T>
	Node<T>* find_next(Node<T>* x, Node<T>* TNULL) {
		if (x->right != TNULL) return find_min(x->right, TNULL);
		Node<T>* y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
	template<class T>
	Node<T>* find_prev(Node<T>* x, Node<T>* TNULL) {
		if (x->left != TNULL) return find_max(x->left);
		Node<T>* y = x->parent;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}
	template<class T, class CMP = std::less<T>>
	Node<T>* find_lower_bound(Node<T>* root, Node<T>* TNULL, const T& key) {
		Node<T>* p = root;
		Node<T>* y = nullptr;
		while (p != TNULL) {
			if (CMP{}(p->data, key)) p = p->right;
			else {
				if (y == nullptr) y = p;
				else y = (CMP{}(p->data, y->data) ? p : y);
				p = p->left;
			}
		}
		return y;
	}
	template<class T, class CMP = std::less<T>>
	Node<T>* find_upper_bound(Node<T>* root, Node<T>* TNULL, const T& key) {
		Node<T>* p = root;
		Node<T>* y = nullptr;
		while (p != TNULL) {
			if (!CMP{}(key, p->data)) p = p->right;
			else {
				if (y == nullptr) y = p;
				else y = (!CMP{}(y->data, p->data) ? p : y);
				p = p->left;
			}
		}
		return y;
	}
}

template<class T>
class RedBlackIterator {
private:
	RedBlack::Node<T>* ptr;
	RedBlack::Node<T>* TNULL;
	RedBlack::Node<T>* root;
public:
	RedBlackIterator(RedBlack::Node<T>* ptr = 0, RedBlack::Node<T>* TNULL = 0, RedBlack::Node<T>* root = 0) {
		this->ptr = ptr;
		this->TNULL = TNULL;
		this->root = root;
	}
	bool operator==(const RedBlackIterator<T> rhs) const {
		return ptr == rhs.ptr;
	}
	bool operator!=(const RedBlackIterator<T> rhs) const {
		return ptr != rhs.ptr;
	}
	const T& operator*() {
		return ptr->data;
	}
	RedBlackIterator<T>& operator++ () {
		if (ptr == TNULL) {
			throw std::runtime_error("Can't increment null iterator");
			return *this;
		}
		ptr = RedBlack::find_next(ptr, TNULL);
		return *this;
	}
	RedBlackIterator<T> operator++ (int) {
		if (ptr == TNULL) {
			throw std::runtime_error("Can't increment null iterator");
			return *this;
		}
		RedBlackIterator<T> res(*this);
		ptr = RedBlack::find_next(ptr, TNULL);
		return res;
	}
	RedBlackIterator<T>& operator-- () {
		if (ptr == nullptr) {
			ptr = RedBlack::find_max(root, TNULL);
			return *this;
		}
		ptr = RedBlack::find_prev(ptr, TNULL);
		return *this;
	}
	RedBlackIterator<T> operator-- (int) {
		RedBlackIterator<T> res(*this);
		if (ptr == nullptr) {
			ptr = RedBlack::find_max(root, TNULL);
			return res;
		}
		ptr = RedBlack::find_prev(ptr, TNULL);
		return res;
	}
	RedBlack::Node<T>* _getPtr() const {
		return ptr;
	}
};

template<class T, class CMP = std::less<T>>
class RedBlackTree {
private:
	RedBlack::Node<T>* root;
	RedBlack::Node<T>* TNULL;
	size_t elements;
	void leftRotate(RedBlack::Node<T>* x) {
		RedBlack::Node<T>* y = x->right;
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
	void rightRotate(RedBlack::Node<T>* x) {
		RedBlack::Node<T>* y = x->left;
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
	void fixDelete(RedBlack::Node<T>* x) {
		RedBlack::Node<T>* s;
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
	void rbTransplant(RedBlack::Node<T>* u, RedBlack::Node<T>* v) {
		if (u->parent == nullptr) this->root = v;
		else if (u == u->parent->left) u->parent->left = v;
		else u->parent->right = v;
		v->parent = u->parent;
	}
	void fixInsert(RedBlack::Node<T>* k) {
		RedBlack::Node<T>* u;
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
	void free_node(RedBlack::Node<T>* ptr) {
		if (ptr->left != TNULL) free_node(ptr->left);
		if (ptr->right != TNULL) free_node(ptr->right);
		delete ptr;
	}
	void copy_tree(RedBlack::Node<T>* dst, RedBlack::Node<T>* src,
		RedBlack::Node<T>* otherTNULL, RedBlack::Node<T>* parent) {
		dst->data = src->data;
		dst->color = src->color;
		dst->cnt = src->cnt;
		dst->parent = parent;
		if (src->right == otherTNULL) dst->right = TNULL;
		else {
			dst->right = new RedBlack::Node<T>;
			copy_tree(dst->right, src->right, otherTNULL, dst);
		}
		if (src->left == otherTNULL) dst->left = TNULL;
		else {
			dst->left = new RedBlack::Node<T>;
			copy_tree(dst->left, src->left, otherTNULL, dst);
		}
	}
	void erase_helper(RedBlack::Node<T>* z) {
		RedBlack::Node<T>* x;
		RedBlack::Node<T>* y;
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
public:
	RedBlackTree() {
		TNULL = new RedBlack::Node<T>;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		TNULL->cnt = -1;
		root = TNULL;
		elements = 0;
	}
	RedBlackTree(const std::initializer_list<T>& l) : RedBlackTree() {
		for (auto& now : l) insert(now);
	}
	RedBlackTree(const RedBlackTree<T, CMP>& rhs) : RedBlackTree() {
		elements = rhs.elements;
		if (rhs.root != rhs.TNULL) {
			root = new RedBlack::Node<T>;
			copy_tree(root, rhs.root, rhs.TNULL, nullptr);
		}
	}
	RedBlackTree(RedBlackTree<T, CMP>&& rhs) {
		TNULL = rhs.TNULL;
		root = rhs.root;
		elements = rhs.elements;
		rhs.root = rhs.TNULL = nullptr;
		rhs.elements = 0;
	}
	RedBlackTree<T, CMP>& operator=(const RedBlackTree<T, CMP>& rhs) {
		if (this == &rhs) return *this;
		if (this->root != TNULL) free_node(this->root);
		elements = rhs.elements;
		if (rhs.root != rhs.TNULL) {
			root = new RedBlack::Node<T>;
			copy_tree(root, rhs.root, rhs.TNULL, nullptr);
		}
		else root = TNULL;
		return *this;
	}
	RedBlackTree<T, CMP>& operator=(RedBlackTree<T, CMP>&& rhs) noexcept {
		if (this->root != TNULL) free_node(this->root);
		delete TNULL;
		TNULL = rhs.TNULL;
		root = rhs.root;
		elements = rhs.elements;
		rhs.root = rhs.TNULL = nullptr;
		rhs.elements = 0;
		return *this;
	}
	void insert(const T& key) {
		elements++;
		RedBlack::Node<T>* node = new RedBlack::Node<T>;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;
		RedBlack::Node<T>* y = nullptr;
		RedBlack::Node<T>* x = this->root;
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
	void erase(const T& key) {
		if (elements == 0) {
			throw std::runtime_error("No elements to erase");
			return;
		}
		elements--;
		RedBlack::Node<T>* node = this->root;
		RedBlack::Node<T>* z = TNULL;
		RedBlack::Node<T>* x;
		RedBlack::Node<T>* y = nullptr;
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
			throw std::runtime_error("Couldn't find key in the tree");
			return;
		}
		erase_helper(z);
	}
	void erase(RedBlackIterator<T> it) {
		if (it._getPtr() == nullptr) {
			throw std::runtime_error("Invalid iterator");
			return;
		}
		elements--;
		RedBlack::Node<T>* p = it._getPtr();
		p->cnt--;
		while (p->parent != nullptr) {
			if (p == p->parent->left) p->parent->cnt--;
			p = p->parent;
		}
		erase_helper(it._getPtr());
	}
	RedBlackIterator<T> begin() const {
		if (root == TNULL) return end();
		return RedBlackIterator<T>(RedBlack::find_min<T>(root, TNULL), TNULL, root);
	}
	RedBlackIterator<T> end() const {
		return RedBlackIterator<T>(nullptr, TNULL, root);
	}
	size_t size() const {
		return elements;
	}
	RedBlackIterator<T> find(const T& key) const {
		RedBlack::Node<T>* node = this->root;
		RedBlack::Node<T>* z = TNULL;
		while (node != TNULL) {
			if (node->data == key) z = node;
			if (CMP{}(node->data, key)) node = node->right;
			else node = node->left;
		}
		if (z == TNULL) return end();
		return RedBlackIterator<T>(z, TNULL, root);
	}
	RedBlackIterator<T> lower_bound(const T& key) const {
		return RedBlackIterator<T>(RedBlack::find_lower_bound<T, CMP>(root, TNULL, key), TNULL, root);
	}
	RedBlackIterator<T> upper_bound(const T& key) const {
		return RedBlackIterator<T>(RedBlack::find_upper_bound<T, CMP>(root, TNULL, key), TNULL, root);
	}
	RedBlackIterator<T> find_by_order(size_t i) const {
		if (i >= elements) return end();
		RedBlack::Node<T>* p = this->root;
		while (p->cnt != i) {
			if (p->cnt < i) {
				i -= p->cnt + 1;
				p = p->right;
			}
			else {
				p = p->left;
			}
		}
		return RedBlackIterator<T>(p, TNULL, root);
	}
	size_t order_of_key(const T& x) const {
		RedBlack::Node<T>* p = this->root;
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
	~RedBlackTree() {
		if (this->root != TNULL) free_node(this->root);
		delete TNULL;
	}
};
