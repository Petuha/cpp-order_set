Implementation of order_set on c++. order_set is a usual set, which provides quick index search by element value and quick search for an item by index in O(log n) time complexity. The RB-tree insertion and deletion was taken from:
https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp
The templates, iterators and index modules were written by me.
Some tests were written, probably there are enough of them.
The ability for fast index search is provided by extra information in each node, which contains the amount of elements in the left sub-tree. In case of incorrect insertion or deletion the tree should be able to keep that information correctly.
If you find incorrect behavior of this data structure, please let me know.
