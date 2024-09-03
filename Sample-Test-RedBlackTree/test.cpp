#include "pch.h"
#include "../RedBlackTree/RedBlackTree.h"
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "leaks.h"
using namespace std;
template<class T>
string get_data(const T& s) {
	stringstream ss;
	ss << s.size() << '\n';
	for (auto& now : s) ss << now << ' ';
	return ss.str();
}

TEST(TestCTR, 1) {
	MemoryLeakDetector meamleak;
	set<int> s = { 1, -1, 25, 123, 3122, -21312, 10 };
	RedBlackTree<int> rb = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestCTR, 2) {
	MemoryLeakDetector meamleak;
	set<int> s = {  };
	RedBlackTree<int> rb = {  };
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestCTR, 3) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int> rb;
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestCTRCopy, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	RedBlackTree<int> rb2 = rb1;
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(TestCTRCopy, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1;
	for (int i = 0; i < 1000; i++) rb1.insert(rand());
	RedBlackTree<int> rb2 = rb1;
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(TestCTRMove, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	RedBlackTree<int> rb2 = rb1;
	RedBlackTree<int> rb3 = std::move(rb1);
	EXPECT_EQ(get_data(rb2), get_data(rb3));
}

TEST(TestCTRMove, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1;
	for (int i = 0; i < 1000; i++) rb1.insert(rand());
	RedBlackTree<int> rb2 = rb1;
	RedBlackTree<int> rb3 = std::move(rb1);
	EXPECT_EQ(get_data(rb2), get_data(rb3));
}

TEST(TestCTRMove, 3) {
	MemoryLeakDetector meamleak;
	auto random_tree = []()->RedBlackTree<int> {
		return { 1, -1, 25, 123, 3122, -21312, 10 };
		};
	RedBlackTree<int> rb1 = random_tree();
	RedBlackTree<int> rb2 = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(TestCTRMove, 4) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1;
	auto random_tree = [&]()->RedBlackTree<int> {
		RedBlackTree<int> ret;
		int x;
		for (int i = 0; i < 1000; i++) {
			x = rand();
			rb1.insert(x);
			ret.insert(x);
		}
		return ret;
		};
	RedBlackTree<int> rb2 = random_tree();
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(OperatorAssignCopy, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	RedBlackTree<int> rb2 = { 12, -1, 3, 15 };
	rb1 = rb2;
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(OperatorAssignCopy, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	RedBlackTree<int> rb2;
	rb1 = rb2;
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(OperatorAssignCopy, 3) {
	MemoryLeakDetector meamleak;
	auto random_tree = [&]()->RedBlackTree<int> {
		RedBlackTree<int> ret;
		for (int i = 0; i < 1000; i++) ret.insert(rand());
		return ret;
		};
	RedBlackTree<int> rb1 = random_tree();
	RedBlackTree<int> rb2 = random_tree();
	rb1 = rb2;
	EXPECT_EQ(get_data(rb1), get_data(rb2));
	rb2 = random_tree();
	rb1 = rb2;
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(OperatorAssignCopy, 4) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_NO_THROW(rb1 = rb1);
	EXPECT_EQ(get_data(rb1), get_data(rb1));
}

TEST(OperatorAssignMove, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	RedBlackTree<int> rb2 = rb1;
	RedBlackTree<int> rb3 = { 12, -1, 3, 15 };
	rb3 = move(rb1);
	EXPECT_EQ(get_data(rb2), get_data(rb3));
}

TEST(OperatorAssignMove, 2) {
	MemoryLeakDetector meamleak;
	auto random_tree = [&]()->RedBlackTree<int> {
		RedBlackTree<int> ret;
		for (int i = 0; i < 1000; i++) ret.insert(rand());
		return ret;
		};
	RedBlackTree<int> rb1 = random_tree();
	RedBlackTree<int> rb2 = rb1;
	RedBlackTree<int> rb3 = random_tree();
	rb3 = move(rb1);
	EXPECT_EQ(get_data(rb2), get_data(rb3));
}

TEST(OperatorAssignMove, 3) {
	MemoryLeakDetector meamleak;
	auto random_tree = []()->RedBlackTree<int> {
		return { 1, -1, 25, 123, 3122, -21312, 10 };
		};
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_NO_THROW(rb1 = random_tree());
	RedBlackTree<int> rb2 = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(OperatorAssignMove, 4) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1;
	auto random_tree = [&]()->RedBlackTree<int> {
		RedBlackTree<int> ret;
		int x;
		for (int i = 0; i < 1000; i++) {
			x = rand();
			ret.insert(x);
			rb1.insert(x);
		}
		return ret;
		};
	RedBlackTree<int> rb2 = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_NO_THROW(rb2 = random_tree());
	EXPECT_EQ(get_data(rb1), get_data(rb2));
}

TEST(OperatorAssignMove, 5) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb1 = { 1, -1, 25, 123, 3122, -21312, 10 };
	EXPECT_NO_THROW(rb1 = move(rb1));
	EXPECT_EQ(get_data(rb1), get_data(rb1));
}

TEST(OperatorEqualNotEqual, 1) {
	MemoryLeakDetector meamleak;
	auto random_tree = [&]()->RedBlackTree<int> {
		RedBlackTree<int> ret;
		for (int i = 0; i < 1000; i++) ret.insert(rand());
		return ret;
		};
	RedBlackTree<int> rbt1 = random_tree(), rbt2;
	rbt2 = rbt1;
	EXPECT_TRUE(rbt1 == rbt2);
	vector<int> erased;
	int n = rbt1.size();
	RedBlackTree<int>::const_iterator it = rbt1.begin();
	for (int i = 0; i < n; ++i, ++it) {
		if (i % 3 == 0) {
			erased.push_back(*it);
		}
	}
	n = erased.size();
	for (int i = 0; i < n; ++i) {
		rbt1.erase(erased[i]);
		EXPECT_TRUE(rbt1 != rbt2);
	}
	for (int i = 0; i + 1 < n; ++i) {
		rbt1.insert(erased[i]);
		EXPECT_TRUE(rbt1 != rbt2);
	}
	rbt1.insert(erased[n - 1]);
	EXPECT_TRUE(rbt1 == rbt2);
	for (int i = n - 1; i >= 0; --i) {
		rbt1.erase(erased[i]);
		EXPECT_TRUE(rbt1 != rbt2);
	}
	for (int i = n - 1; i > 0; --i) {
		rbt1.insert(erased[i]);
		EXPECT_TRUE(rbt1 != rbt2);
	}
	rbt1.insert(erased[0]);
	EXPECT_TRUE(rbt1 == rbt2);
}

TEST(OperatorEqualNotEqual, 2) {
	MemoryLeakDetector meamleak;
	int n = 1000;
	vector<int> arr;
	arr.reserve(n);
	for (int i = 0; i < n; i++) {
		arr.push_back(rand());
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	n = arr.size();
	RedBlackTree<int> rbt1, rbt2;
	for (int x : arr) {
		rbt1.insert(x);
		rbt2.insert(x);
	}
	EXPECT_TRUE(rbt1 == rbt2);
	int x;
	for (int i = 1; i + 1 < n; ++i) {
		rbt1.erase(arr[i]);
		if (arr[i + 1] - arr[i - 1] > 2) {
			do {
				x = arr[i - 1] + 1 + rand() % (arr[i + 1] - arr[i - 1] - 1);
			} while (x == arr[i]);
		}
		else {
			if (rand() % 2) x = *arr.rbegin() + 1 + rand();
			else x = *arr.begin() - 1 - rand();
		}
		rbt1.insert(x);
		EXPECT_TRUE(rbt1 != rbt2);
		rbt1.erase(x);
		rbt1.insert(arr[i]);
		EXPECT_TRUE(rbt1 == rbt2);
	}
}

TEST(TestInsert, 2) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int> rb;
	for (int i = 0; i < 100; i++) {
		s.insert(i);
		s.insert(i);
		rb.insert(i);
		rb.insert(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestErase, 1) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int, less_equal<int>> rb;
	for (int i = 0; i < 100; i++) {
		s.insert(i);
		rb.insert(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 0; i < 50; i++) {
		s.erase(i);
		rb.erase(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestErase, 2) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int, less_equal<int>> rb;
	for (int i = 0; i < 100; i++) {
		s.insert(i);
		rb.insert(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 0; i < 100; i += 2) {
		s.erase(i);
		rb.erase(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestErase, 3) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int, less_equal<int>> rb;
	for (int i = 0; i < 100; i++) {
		s.insert(i);
		rb.insert(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 0; i < 100; i++) {
		s.erase(i);
		rb.erase(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestErase, 4) {
	MemoryLeakDetector meamleak;
	set<int> s;
	RedBlackTree<int, less_equal<int>> rb;
	for (int i = 0; i < 100; i++) {
		s.insert(i);
		rb.insert(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 0; i < 100; i += 2) {
		s.erase(i);
		rb.erase(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 100; i < 200; i++) {
		s.insert(i);
		rb.insert(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 100; i < 200; i++) {
		s.erase(i);
		rb.erase(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
	for (int i = 1; i < 100; i += 2) {
		s.erase(i);
		rb.erase(i);
	}
	EXPECT_EQ(get_data(s), get_data(rb));
}

TEST(TestLowerBound, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb = { -1, 1, 2, 10, 11, 15, 45 };
	EXPECT_EQ(*rb.lower_bound(-1000), -1);
	EXPECT_EQ(*rb.lower_bound(-2), -1);
	EXPECT_EQ(*rb.lower_bound(-1), -1);
	EXPECT_EQ(*rb.lower_bound(0), 1);
	EXPECT_EQ(*rb.lower_bound(1), 1);
	EXPECT_EQ(*rb.lower_bound(2), 2);
	EXPECT_EQ(*rb.lower_bound(3), 10);
	EXPECT_EQ(*rb.lower_bound(4), 10);
	EXPECT_EQ(*rb.lower_bound(5), 10);
	EXPECT_EQ(*rb.lower_bound(10), 10);
	EXPECT_EQ(*rb.lower_bound(11), 11);
	EXPECT_EQ(*rb.lower_bound(12), 15);
	EXPECT_EQ(*rb.lower_bound(13), 15);
	EXPECT_EQ(*rb.lower_bound(14), 15);
	EXPECT_EQ(*rb.lower_bound(15), 15);
	EXPECT_EQ(*rb.lower_bound(16), 45);
	EXPECT_EQ(*rb.lower_bound(20), 45);
	EXPECT_EQ(*rb.lower_bound(30), 45);
	EXPECT_EQ(*rb.lower_bound(45), 45);
	EXPECT_EQ(rb.lower_bound(46), rb.end());
	EXPECT_EQ(rb.lower_bound(1000), rb.end());
}

TEST(TestLowerBound, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	set<int> s;
	int x;
	for (int i = 0; i < 1000; i++) {
		x = rand() % 10000;
		s.insert(x);
		rb.insert(x);
	}
	for (int i = 0; i < 1000; i++) {
		x = rand() % 10000;
		if (s.lower_bound(x) == s.end()) {
			EXPECT_EQ(rb.lower_bound(x), rb.end());
		}
		else {
			EXPECT_EQ(*s.lower_bound(x), *rb.lower_bound(x));
		}
	}
}

TEST(TestLowerBound, 3) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	set<int> s;
	int x;
	for (int i = 0; i < 1000; i++) {
		x = rand() % 1000;
		s.insert(x);
		rb.insert(x);
	}
	for (int i = 0; i < 1000; i++) {
		x = i;
		if (s.lower_bound(x) == s.end()) {
			EXPECT_EQ(rb.lower_bound(x), rb.end());
		}
		else {
			EXPECT_EQ(*s.lower_bound(x), *rb.lower_bound(x));
		}
	}
}

TEST(TestUpperBound, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb = { -1, 1, 2, 10, 11, 15, 45 };
	EXPECT_EQ(*rb.upper_bound(-1000), -1);
	EXPECT_EQ(*rb.upper_bound(-2), -1);
	EXPECT_EQ(*rb.upper_bound(-1), 1);
	EXPECT_EQ(*rb.upper_bound(0), 1);
	EXPECT_EQ(*rb.upper_bound(1), 2);
	EXPECT_EQ(*rb.upper_bound(2), 10);
	EXPECT_EQ(*rb.upper_bound(3), 10);
	EXPECT_EQ(*rb.upper_bound(4), 10);
	EXPECT_EQ(*rb.upper_bound(5), 10);
	EXPECT_EQ(*rb.upper_bound(9), 10);
	EXPECT_EQ(*rb.upper_bound(10), 11);
	EXPECT_EQ(*rb.upper_bound(11), 15);
	EXPECT_EQ(*rb.upper_bound(12), 15);
	EXPECT_EQ(*rb.upper_bound(13), 15);
	EXPECT_EQ(*rb.upper_bound(14), 15);
	EXPECT_EQ(*rb.upper_bound(15), 45);
	EXPECT_EQ(*rb.upper_bound(16), 45);
	EXPECT_EQ(*rb.upper_bound(20), 45);
	EXPECT_EQ(*rb.upper_bound(30), 45);
	EXPECT_EQ(rb.upper_bound(45), rb.end());
	EXPECT_EQ(rb.upper_bound(46), rb.end());
	EXPECT_EQ(rb.upper_bound(1000), rb.end());
}

TEST(TestUpperBound, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	set<int> s;
	int x;
	for (int i = 0; i < 1000; i++) {
		x = rand() % 10000;
		s.insert(x);
		rb.insert(x);
	}
	for (int i = 0; i < 1000; i++) {
		x = rand() % 10000;
		if (s.upper_bound(x) == s.end()) {
			EXPECT_EQ(rb.upper_bound(x), rb.end());
		}
		else {
			EXPECT_EQ(*s.upper_bound(x), *rb.upper_bound(x));
		}
	}
}

TEST(TestUpperBound, 3) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	set<int> s;
	int x;
	for (int i = 0; i < 1000; i++) {
		x = rand() % 1000;
		s.insert(x);
		rb.insert(x);
	}
	for (int i = 0; i < 1000; i++) {
		x = i;
		if (s.upper_bound(x) == s.end()) {
			EXPECT_EQ(rb.upper_bound(x), rb.end());
		}
		else {
			EXPECT_EQ(*s.upper_bound(x), *rb.upper_bound(x));
		}
	}
}

TEST(TestOrder, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i++) EXPECT_EQ(i, *rb.find_by_order(i));
	for (int i = 0; i < 1000; i++) EXPECT_EQ(i, rb.order_of_key(i));
}

TEST(TestOrder, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i += 2) rb.erase(i);
	for (int i = 0; i < 100; i++) {
		EXPECT_ANY_THROW(rb.erase((rand() % 500) * 2));
	}
	EXPECT_ANY_THROW(rb.erase(-1));
	int j = 0;
	for (int i = 1; i < 1000; i += 2, j++) EXPECT_EQ(i, *rb.find_by_order(j));
	j = 0;
	for (int i = 1; i < 1000; i += 2, j++) EXPECT_EQ(j, rb.order_of_key(i));
	for (int i = 1; i < 1000; i += 2) rb.erase(i);
	EXPECT_EQ(rb.size(), 0);
	EXPECT_ANY_THROW(rb.erase(0));
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i++) EXPECT_EQ(i, *rb.find_by_order(i));
	for (int i = 0; i < 1000; i++) EXPECT_EQ(i, rb.order_of_key(i));
}

TEST(TestOrder, 3) {
	MemoryLeakDetector meamleak;
	for (int test = 0; test < 100; test++) {
		RedBlackTree<int> rb;
		int n = 100;
		vector<int> arr;
		arr.reserve(n);
		for (int i = 0; i < n; i++) {
			arr.push_back(rand());
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
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(i, rb.order_of_key(arr[i]));
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(arr[i], *rb.find_by_order(i));
		}
	}
}

TEST(TestOrder, 5) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	int n = 1000;
	vector<int> arr;
	arr.reserve(n);
	for (int i = 0; i < n; i++) {
		arr.push_back(rand());
		rb.insert(*arr.rbegin());
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	int c, r;
	for (int step = 0; step < 1000; step++) {
		c = rand() % 2;
		if (c == 1 && arr.size()) {
			r = rand() % arr.size();
			rb.erase(rb.find(arr[r]));
			arr.erase(arr.begin() + r);
		}
		else {
			r = rand() % 500;
			arr.push_back(r);
			rb.insert(r);
			sort(arr.begin(), arr.end());
			arr.erase(unique(arr.begin(), arr.end()), arr.end());
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(i, rb.order_of_key(arr[i]));
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(arr[i], *rb.find_by_order(i));
		}
	}
	while (arr.size()) {
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
	for (int i = 0; i < n; i++) {
		arr.push_back(rand());
		rb.insert(*arr.rbegin());
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(i, rb.order_of_key(arr[i]));
	}
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(arr[i], *rb.find_by_order(i));
	}
}

TEST(TestIterator, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	int n = 1000;
	vector<int> arr;
	arr.reserve(n);
	for (int i = 0; i < n; i++) {
		arr.push_back(rand());
		rb.insert(*arr.rbegin());
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(i, rb.order_of_key(arr[i]));
	}
	for (int i = 0; i < arr.size(); i++) {
		EXPECT_EQ(arr[i], *rb.find_by_order(i));
	}
	n = arr.size() / 2;
	for (int i = 0; i < n; i++) {
		rb.erase(rb.begin());
		arr.erase(arr.begin());
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(i, rb.order_of_key(arr[i]));
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(arr[i], *rb.find_by_order(i));
		}
	}
}

TEST(TestIterator, 2) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb;
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i += 2) rb.erase(rb.find(i));
	for (int i = 0; i < 100; i++) {
		EXPECT_ANY_THROW(rb.erase((rand() % 500) * 2));
	}
	int j = 0;
	for (int i = 1; i < 1000; i += 2, j++) EXPECT_EQ(i, *rb.find_by_order(j));
	j = 0;
	for (int i = 1; i < 1000; i += 2, j++) EXPECT_EQ(j, rb.order_of_key(i));
	for (int i = 1; i < 1000; i += 2) rb.erase(rb.find(i));
	EXPECT_EQ(rb.size(), 0);
	for (int i = 0; i < 1000; i++) rb.insert(i);
	for (int i = 0; i < 1000; i++) EXPECT_EQ(i, *rb.find_by_order(i));
	for (int i = 0; i < 1000; i++) EXPECT_EQ(i, rb.order_of_key(i));
}

TEST(TestIterator, 3) {
	MemoryLeakDetector meamleak;
	for (int test = 0; test < 100; test++) {
		RedBlackTree<int> rb;
		int n = 100;
		vector<int> arr;
		arr.reserve(n);
		for (int i = 0; i < n; i++) {
			arr.push_back(rand());
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
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(i, rb.order_of_key(arr[i]));
		}
		for (int i = 0; i < arr.size(); i++) {
			EXPECT_EQ(arr[i], *rb.find_by_order(i));
		}
	}
}

TEST(TestIterator, 4) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb = { 1, 2, 3, 4, 5, 6 };
	RedBlackTree<int>::const_iterator it = rb.begin(), it1;
	EXPECT_NO_THROW(it1 = ++++++it);
	EXPECT_EQ(it, ++++++rb.begin());
	EXPECT_EQ(it1, ++++++rb.begin());
	it = rb.begin();
	EXPECT_NO_THROW(it1 = it++);
	EXPECT_EQ(it, ++rb.begin());
	EXPECT_EQ(it1, rb.begin());
	it = rb.begin();
	int a;
	EXPECT_NO_THROW(a = *++++it);
	EXPECT_EQ(a, 3);
	it = rb.begin();
	EXPECT_NO_THROW(a = *it++);
	EXPECT_EQ(a, 1);
	EXPECT_EQ(it, ++rb.begin());
}

TEST(TestIteratorThrow, 1) {
	MemoryLeakDetector meamleak;
	RedBlackTree<int> rb = { 1, 2, 3, 4, 5, 6 };
	RedBlackTree<int>::const_iterator it = rb.begin();
	for (int i = 0; i < 6; i++) ++it;
	EXPECT_EQ(it, rb.end());
	it = rb.begin();
	for (int i = 0; i < 6; i++) it++;
	EXPECT_EQ(it, rb.end());
	EXPECT_ANY_THROW(it++);
	EXPECT_ANY_THROW(++it);
	it = rb.begin();
	EXPECT_ANY_THROW(it--);
	EXPECT_ANY_THROW(--it);
}