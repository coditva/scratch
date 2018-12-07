#ifndef NODE_H_TCJS7ZWP
#define NODE_H_TCJS7ZWP

template <class T = unsigned int>
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
        return this->value;
    }

    void setValue(T value)
    {
        this->value = value;
    }

    Node<T> *left = nullptr;
    Node<T> *right = nullptr;

private:
    T value;
};

#endif /* end of include guard: NODE_H_TCJS7ZWP */
