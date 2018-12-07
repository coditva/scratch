#include <iostream>
#include "AVLTree.h"

void print(Node<int> *node)
{
    std::cout << node->getValue() << ", ";
}

int main(int argc, char *argv[])
{
    int i = 0, n = 0;
    AVLTree<int> tree;

    std::cin >> n;
    for (i = 0; i < n; ++i) {
        int node;
        std::cin >> node;
        tree.addNode(new Node<int>(node));
        tree.doLevelOrder(print);
        std::cout << "---------" << std::endl;
    }

    std::cout << std::endl << "inorder:" << std::endl;
    tree.doInOrder(print);

    std::cout << std::endl << "preorder:" << std::endl;
    tree.doPreOrder(print);

    std::cout << std::endl << "postorder:" << std::endl;
    tree.doPostOrder(print);

    std::cout << std::endl << "levelorder:" << std::endl;
    tree.doLevelOrder(print);

    std::cout << std::endl;
    return 0;
}
