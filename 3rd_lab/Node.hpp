#ifndef INC_3RD_LAB_NODE_HPP
#define INC_3RD_LAB_NODE_HPP

#include <cstdlib>
#include "dynamicArray.hpp"

template<typename T>
class Node {
private:
    T value;
    int id;
    Node<T> *prev;
    dynamicArray<Node<T> *> next;
public:
    Node(int n, int id);

    Node(Node<T> &node, int id);

    bool isLeaf() { return this->next.length() == 0; }

    int getId() { return this->id; }

    int weight() { return this->next.length(); }

    void addNext(T value, int id);

    void addNext(Node<T> *newNode, int id);

    void delNext(Node<T> *nextNode) { this->next.delByValue(nextNode); }

    T &getValue() { return this->value; }

    void setValue(T value) { this->value = value; };

    void setNext(int n, Node<T> *next) { this->next[n] = next; };

    void setPrev(Node<T> *prev) { this->prev = prev; };

    Node<T> *getNext(int n) { return this->next[n]; }

    Node<T> *getPrev() { return this->prev; }

    void flushNext() { this->next = *(new dynamicArray<Node<T> *>()); }

    Node<T> &operator=(T val) { this->setValue(val); }

    ~Node() = default;
};

template<typename T>
Node<T>::Node(int n, int id) {
    this->value = 0;
    this->next = dynamicArray<Node<T> *>(n);
    this->id = id;
    this->prev = nullptr;
}

template<typename T>
Node<T>::Node(Node<T> &node, int id) {
    this->value = node.getValue();
    this->id = id;
    this->next = node.next;
    this->prev = node.getPrev();
}

template<typename T>
void Node<T>::addNext(T value, int id) {
    auto fresh = new Node<T>(0, id);
    fresh->setPrev(this);
    fresh->setValue(value);
    this->next.append(fresh);
}

template<typename T>
void Node<T>::addNext(Node<T> *newNode, int nid) {
    this->next.append(newNode);
    newNode->id = nid;
}


#endif //INC_3RD_LAB_NODE_HPP