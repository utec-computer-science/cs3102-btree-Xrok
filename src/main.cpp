#include <iostream>
#include <math.h>
#include "./include/btree.cpp"


int main()
{
    BTree<int, 4> bt;
    bt.insert(10);
    bt.insert(5);
    bt.insert(8);
    bt.insert(9);
    bt.insert(17);
    bt.insert(21);
    bt.print();
}
