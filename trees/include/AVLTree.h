#ifndef AVLTREE_H_CRRXDKXV
#define AVLTREE_H_CRRXDKXV

#include "BTree.h"

template <class T = unsigned int>
class AVLTree: public BTree<T>
{
public:
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
    void addNode(Node<T> *node, Node<T> *root)
    {
        this->BTree<T>::addNode(node, root);
        this->balance();
    }

private:
    void balance()
    {
        auto *root = this->root;

        if (root->balanceFactor > 1) {
            if (root->right->balanceFactor > 0) {
                this->root = rotateLeft(root);
            } else {
                root->right = rotateRight(root->right);
                this->root = rotateLeft(root);
            }
        } else if (root->balanceFactor < -1) {
            if (root->left->balanceFactor < 0) {
                this->root = rotateRight(root);
            } else {
                root->left = rotateLeft(root->left);
                this->root = rotateRight(root);
            }
        }
    }

    Node<T> * rotateLeft(Node<T> *root)
    {
        std::cout << "left" << std::endl;
        auto top = root->right;
        //top->incHeight(-1);
        //root->incHeight(1);

        root->right = top->left;
        root->balanceFactor++;

        top->left = root;
        top->balanceFactor--;

        return top;
    }

    Node<T> * rotateRight(Node<T> *root)
    {
        std::cout << "right" << std::endl;
        auto top = root->left;

        root->left = top->right;
        root->balanceFactor--;

        top->right = root;
        top->balanceFactor++;

        return top;
    }
};

#endif /* end of include guard: AVLTREE_H_CRRXDKXV */
