#ifndef TREE_H_I37DWHC8
#define TREE_H_I37DWHC8

#include "Node.h"

template <class T = unsigned int>
class Tree
{
public:
    typedef void (Callback)(T);

    void doInOrder(Callback *callback)
    {
        this->doInOrder(this->root, callback);
    }

    void doInOrder(Node<T> *node, Callback *callback)
    {
        if (node == nullptr) {
            return;
        }

        doInOrder(node->left, callback);
        callback(node->getValue());
        doInOrder(node->right, callback);
    }

protected:
    int num_of_nodes = 0;
    Node<T> *root = nullptr;
};

#endif /* end of include guard: TREE_H_I37DWHC8 */
