#include <iostream>
#include "BTree.h"

void print(int val)
{
    std::cout << val << ", ";
}

int main(int argc, char *argv[])
{
    int i = 0, n = 0;
    void print(int val);
    BTree<int> tree;

    std::cin >> n;
    for (i = 0; i < n; ++i) {
        int node;
        std::cin >> node;
        tree.addNode(new Node<int>(node));
    }

    tree.doInOrder(print);

    std::cout << std::endl;
    return 0;
}
