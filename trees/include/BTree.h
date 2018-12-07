#ifndef BTREE_H_XANPQUIH
#define BTREE_H_XANPQUIH

#include "Tree.h"

template <class T = unsigned int>
class BTree: public Tree<T>
{
public:
    BTree () {}

    void addNode(Node<T> *node, Node<T> *root)
    {
        if (node->getValue() > root->getValue()) {
            root->balanceFactor++;
            if (root->right == nullptr) {
                root->right = node;
                node->setHeight(root->getHeight() + 1);
                this->num_of_nodes++;
            } else {
                this->addNode(node, root->right);
            }
        } else {
            root->balanceFactor--;
            if (root->left == nullptr) {
                root->left = node;
                node->setHeight(root->getHeight() + 1);
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
            node->setHeight(0);
            this->num_of_nodes++;
        } else {
            this->addNode(node, this->root);
        }
    }
};

#endif /* end of include guard: BTREE_H_XANPQUIH */
