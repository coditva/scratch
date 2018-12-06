#include <iostream>

template <class T>
class Node
{
public:
    Node () { }

    Node (T value)
    {
        this->value = value;
    }

    T getValue()
    {
        return this->val;
    }

    void setValue(T value)
    {
        this->val = value;
    }

    void print()
    {
        std::cout << this->val;
    }

    T value;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;

private:
    T val;
};

template <class T>
class Tree
{
public:
    virtual void addNode(Node<T> *node);
    void print(Node<T> *node = nullptr)
    {
        if (node == nullptr) {
            return;
        }

        if (node->left) {
            this->print(node->left);
        }
        node->print();
        std::cout << ", ";
        if (node->right) {
            this->print(node->right);
        }
    }

protected:
    int num_of_nodes = 0;
    Node<T> *root = nullptr;
};

template <class T>
class AVLTree: public Tree<T>
{
public:
    AVLTree () {}

    void addNode(Node<T> *node, Node<T> *root)
    {
        if (node->getValue() > root->getValue()) {
            if (root->right == nullptr) {
                root->right = node;
            } else {
                this->addNode(node, root->right);
            }
        } else {
            if (root->left == nullptr) {
                root->left = node;
            } else {
                this->addNode(node, root->left);
            }
        }
    }

    void addNode(Node<T> *node)
    {
        if (this->root == nullptr) {
            this->root = node;
        } else {
            this->addNode(node, this->root);
        }
    }
};

int main(int argc, char *argv[])
{
    int i = 0, n = 0;
    AVLTree<int> tree;

    std::cin >> n;
    for (i = 0; i < n; ++i) {
        int node;
        std::cin >> node;
        tree.addNode(new Node<int>(node));
    }

    tree.print();
    return 0;
}
