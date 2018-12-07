#ifndef AVLTREE_H_CRRXDKXV
#define AVLTREE_H_CRRXDKXV

#include "BTree.h"

template <class T = unsigned int>
class AVLTree: public BTree<T>
{
public:
    void addNode(Node<T> *node)
    {
        this->BTree<T>::addNode(node);
    }
    void addNode(Node<T> *node, Node<T> *root)
    {
        this->BTree<T>::addNode(node, root);
        this->balance();
    }
private:
    void balance()
    {
    }
};

#endif /* end of include guard: AVLTREE_H_CRRXDKXV */
