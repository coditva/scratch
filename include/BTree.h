#ifndef BTREE_H_XANPQUIH
#define BTREE_H_XANPQUIH

#include "Tree.h"

template <class T>
class BTree: public Tree<T>
{
public:
    BTree () {}

    void addNode(Node<T> *node, Node<T> *root)
    {
        if (node->getValue() > root->getValue()) {
            if (root->right == nullptr) {
                root->right = node;
                this->num_of_nodes++;
            } else {
                this->addNode(node, root->right);
            }
        } else {
            if (root->left == nullptr) {
                root->left = node;
                this->num_of_nodes++;
            } else {
                this->addNode(node, root->left);
            }
        }
    }

    void addNode(Node<T> *node)
    {
        if (this->root == nullptr) {
            this->root = node;
            this->num_of_nodes++;
        } else {
            this->addNode(node, this->root);
        }
    }
};

#endif /* end of include guard: BTREE_H_XANPQUIH */
