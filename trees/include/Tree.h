#ifndef TREE_H_I37DWHC8
#define TREE_H_I37DWHC8

#include <iostream>
#include <queue>
#include "Node.h"

template <class T = unsigned int>
class Tree
{
public:
    typedef void (Callback)(Node<T> *);

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
        callback(node);
        doInOrder(node->right, callback);
    }

    void doPreOrder(Callback *callback)
    {
        this->doPreOrder(this->root, callback);
    }

    void doPreOrder(Node<T> *node, Callback *callback)
    {
        if (node == nullptr) {
            return;
        }

        callback(node);
        doPreOrder(node->left, callback);
        doPreOrder(node->right, callback);
    }

    void doPostOrder(Callback *callback)
    {
        this->doPostOrder(this->root, callback);
    }

    void doPostOrder(Node<T> *node, Callback *callback)
    {
        if (node == nullptr) {
            return;
        }

        doPostOrder(node->left, callback);
        doPostOrder(node->right, callback);
        callback(node);
    }

    void doLevelOrder(Callback *callback)
    {
        this->doLevelOrder(this->root, callback);
    }

    void doLevelOrder(Node<T> *node, Callback *callback)
    {
        if (node == nullptr) {
            return;
        }

        std::queue<Node<T> *> q;
        q.push(node);
        while (!q.empty()) {
            Node<T> *current_node = q.front();
            if (current_node->left) {
                q.push(current_node->left);
            }
            if (current_node->right) {
                q.push(current_node->right);
            }
            callback(current_node);
            std::cout << current_node->balanceFactor << std::endl;
            q.pop();
        }
    }

protected:
    int num_of_nodes = 0;
    Node<T> *root = nullptr;
};

#endif /* end of include guard: TREE_H_I37DWHC8 */
