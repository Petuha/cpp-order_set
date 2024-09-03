#include "pch.h"
#include "../RedBlackTree/RedBlackTree.h"
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "../Sample-Test-RedBlackTree/leaks.h"
using namespace std;
template<class T>
string get_data(const T& s) {
	stringstream ss;
	ss << s.size() << '\n';
	for (auto& now : s) ss << now << ' ';
	return ss.str();
}

TEST(TestInsert, 1) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int> rb;
	int x;
	for (int i = 0; i < 100; i++) {
		s = {};
		rb = {};
		for (int j = 0; j < 1000; j++) {
			do {
				x = rand();
			} while (s.find(x) != s.end());
			s.insert(x);
			rb.insert(x);
		}
		EXPECT_EQ(get_data(s), get_data(rb));
	}
}

TEST(TestInsertEraseOrder, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	int x, c, i;
	for (int step = 0; step < 10000; step++) {
		x = rand() % 100;
		c = rand() % 2;
		if (c == 0) {
			rb.insert(x);
		}
		else {
			try {
				rb.erase(x);
			}
			catch (...) {}
		}
		i = 0;
		for (auto& now : rb) {
			x = now;
			EXPECT_EQ(i, rb.order_of_key(x));
			EXPECT_EQ(x, *rb.find_by_order(i));
			i++;
		}
	}
}

TEST(TestOrder, 4) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	int n = 10000;
	vector<int> arr;
	arr.reserve(n);
	for (int i = 0; i < n; i++) {
		arr.push_back(rand());
		rb.insert(*arr.rbegin());
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	for (int x : arr) {
		rb.insert(x);
		rb.insert(x);
	}
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(i, rb.order_of_key(arr[i]));
	}
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(arr[i], *rb.find_by_order(i));
	}
	n = arr.size() / 2;
	int r;
	for (int i = 0; i < n; i++) {
		r = rand() % arr.size();
		rb.erase(arr[r]);
		arr.erase(arr.begin() + r);
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(i, rb.order_of_key(arr[i]));
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(arr[i], *rb.find_by_order(i));
		}
	}
}

TEST(TestOrderIterator, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	int n = 10000;
	vector<int> arr;
	arr.reserve(n);
	for (int i = 0; i < n; i++) {
		arr.push_back(rand());
		rb.insert(*arr.rbegin());
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	for (int x : arr) {
		rb.insert(x);
		rb.insert(x);
	}
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(i, rb.order_of_key(arr[i]));
	}
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(arr[i], *rb.find_by_order(i));
	}
	n = arr.size() / 2;
	int r;
	for (int i = 0; i < n; i++) {
		r = rand() % arr.size();
		rb.erase(rb.find(arr[r]));
		arr.erase(arr.begin() + r);
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(i, rb.order_of_key(arr[i]));
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(arr[i], *rb.find_by_order(i));
		}
	}
}
