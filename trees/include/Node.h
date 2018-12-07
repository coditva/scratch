#ifndef NODE_H_TCJS7ZWP
#define NODE_H_TCJS7ZWP

template <class T = unsigned int>
class Node
{
public:
    Node ()
    {
        this->height = 0;
    }

    Node (T value)
    {
        this->value = value;
        this->height = 1;
    }

    T getValue()
    {
        return this->value;
    }

    void setValue(T value)
    {
        this->value = value;
    }

    unsigned int getHeight()
    {
        return this->height;
    }

    void setHeight(unsigned int height)
    {
        this->height = height;
    }

    void incHeight(int increment)
    {
        this->height += increment;
    }

    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    int balanceFactor = 0;

private:
    T value;
    unsigned int height = 0;
};

#endif /* end of include guard: NODE_H_TCJS7ZWP */
