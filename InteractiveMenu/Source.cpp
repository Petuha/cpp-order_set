#include "../RedBlackTree/RedBlackTree.h"
#include <iostream>
#include <functional>
#include <iomanip>
#include <vector>
using namespace std;
int main() {
	RedBlackTree<int> rbt = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int c, x, i;
	while (1) {
		cout << "1 - insert\n2 - erase\n3 - find by order\n4 - order of key\n5 - exit\n";
		for (auto& now : rbt) cout << setw(2) << now << ' ';
		cout << '\n';
		for (auto& now : rbt) cout << setw(2) << rbt.order_of_key(now) << ' ';
		cout << '\n';
		for (int i = 0; i < rbt.size(); i++) cout << setw(2) << i << ' ';
		cout << '\n';
		cin >> c;
		if (c == 1) {
			cin >> x;
			rbt.insert(x);
		}
		else if (c == 2) {
			cin >> x;
			rbt.erase(x);
		}
		else if (c == 3) {
			cin >> i;
			cout << *rbt.find_by_order(i) << '\n';
		}
		else if (c == 4) {
			cin >> x;
			cout << rbt.order_of_key(x) << '\n';
		}
		else if (c == 5) break;
	}
	return 0;
}
