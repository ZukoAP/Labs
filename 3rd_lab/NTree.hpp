#ifndef INC_3RD_LAB_NTREE_HPP
#define INC_3RD_LAB_NTREE_HPP

#include "Node.hpp"
#include "dynamicArray.hpp"
#include <cstdlib>
#include <algorithm>

template<typename T>
class NTree {
private:
    Node<T> *root;
    int lastId = 0;
public:
    NTree() { this->root = new Node<T>(0, 0); }

    NTree(int id) { this->root = new Node<T>(0, id); }

    NTree(const NTree<T> &tree);

    Node<T> *copyNode(Node<T> *target);

    string walk(string format);

    string walk(Node<T> *start, dynamicArray<int> *order);

    Node<T> *getNodeById(int id) { return getNodeById(this->root, id); };

    Node<T> *getNodeById(Node<T> *start, int id = 0);

    Node<T> *getNodeByVal(T val) { return getNodeByVal(this->root, val); };

    Node<T> *getNodeByVal(Node<T> *start, T val);

    void addVertex(int parentId, T val);

    void addVertex(int parentId, Node<T> *newNode);

    void addVertex(Node<T> *parent, Node<T> *newNode);

    void fill(string vals, string format);

    void fill(dynamicArray<int> *values, Node<T> *start, dynamicArray<int> *order);

    void delVertex(int id);

    NTree<T> *subTree(Node<T> *node);

    bool hasSubTree(NTree<T> *tree);

    int weight() { return this->lastId; };

    int maxWeight();

};

template<typename T>
NTree<T>::NTree(const NTree<T> &tree) {
    this->root = new Node<T>(*(tree.root), tree.root->getId());
    this->root->flushNext();
    this->lastId += (tree.root->weight() >= 0);
    for (int i = 0; i < tree.root->weight(); i++) {
        auto newNode = this->copyNode(tree.root->getNext(i));
        this->addVertex(this->root, newNode);
        this->lastId--;
    }
    this->lastId--;
}

template<typename T>
Node<T> *NTree<T>::copyNode(Node<T> *target) {
    auto copy = new Node<T>(*target, this->lastId);
    this->lastId++;
    copy->flushNext();
    for (int i = 0; i < target->weight(); i++) {
        auto newNode = this->copyNode(target->getNext(i));
        this->addVertex(copy, newNode);
        this->lastId--;
    }
    return copy;
}

//wrapper
template<typename T>
string NTree<T>::walk(string format) {
    replace(format.begin(), format.end(), 'K', '0');
    dynamicArray<int> decoded(format);
    return this->walk(this->root, &decoded);
}

template<typename T>
string NTree<T>::walk(Node<T> *start, dynamicArray<int> *order) {
    if (start->isLeaf())
        return to_string(start->getValue()) +
               " ";                  //to_string(start->getValue()) +"("+to_string(start->getId())+")"+" ";
    string out = "";
    for (int i = 0; i < order->length(); i++) {
        if (order->operator[](i) == 0) {
            out += to_string(start->getValue()) + " ";
            continue;
        }
        if (order->operator[](i) - 1 < start->weight()) {
            out += walk(start->getNext(order->operator[](i) - 1), order);
        }
    }
    return out;
}

template<typename T>
Node<T> *NTree<T>::getNodeById(Node<T> *start, int id) {
    assert(id <= this->lastId);
    if (start->getId() == id) return start;
    if (start->isLeaf()) {
        return nullptr;
    }
    for (int i = 0; i < start->weight(); i++) {
        Node<T> *success = getNodeById(start->getNext(i), id);
        if (success) return success;
    }
    return nullptr;
}

template<typename T>
void NTree<T>::addVertex(int parentId, Node<T> *newNode) {
    Node<T> *parent = this->getNodeById(parentId);
    parent->addNext(newNode, this->lastId + 1);
    this->lastId++;
}

template<typename T>
void NTree<T>::addVertex(int parentId, T val) {
    Node<T> *parent = this->getNodeById(parentId);
    parent->addNext(val, this->lastId + 1);
    this->lastId++;
}

template<typename T>
void NTree<T>::addVertex(Node<T> *parent, Node<T> *newNode) {
    parent->addNext(newNode, newNode->getId());
    newNode->setPrev(parent);
    this->lastId++;
}

template<typename T>
NTree<T> *NTree<T>::subTree(Node<T> *node) {
    auto out = new NTree<T>(node->getId());
    out->root = out->copyNode(node);
    return out;
}

template<typename T>
Node<T> *NTree<T>::getNodeByVal(Node<T> *start, T val) {
    if (start->getValue() == val) return start;
    if (start->isLeaf()) {
        return nullptr;
    }
    for (int i = 0; i < start->weight(); i++) {
        Node<T> *success = getNodeByVal(start->getNext(i), val);
        if (success) return success;
    }
    return nullptr;
}

template<typename T>
void NTree<T>::delVertex(int id) {
    auto got = getNodeById(id);
    auto parent = got->getPrev();
    parent->delNext(got);
}

template<typename T>
bool NTree<T>::hasSubTree(NTree<T> *tree) {
    auto walkCriteria = new dynamicArray<int>();
    for (int i = 0; i < tree->maxWeight(); i++) {
        walkCriteria->append(i);
    }
    string baseWalk = tree->walk(tree->root, walkCriteria);
    for (int i = 0; i <= this->lastId; i++) {
        Node<T> *vertex = getNodeById(this->root, i);
        if (!vertex) continue;
        if (vertex->getValue() == tree->root->getValue()) {
            if (this->walk(vertex, walkCriteria) == baseWalk) return true;
        }
    }
    return false;
}

template<typename T>
int NTree<T>::maxWeight() {
    int max = -1;
    for (int i = 0; i <= lastId; i++) {
        auto vertex = getNodeById(this->root, i);
        if (vertex) {
            if (vertex->weight() > max) max = vertex->weight();
        }
    }
    assert(max >= 0);
    return max;
}

template<typename T>
void NTree<T>::fill(string vals, string format) {
    replace(format.begin(), format.end(), 'K', '0');
    auto values = new dynamicArray<int>(vals);
    auto order = new dynamicArray<int>(format);
    return fill(values, this->root, order);
}

template<typename T>
void NTree<T>::fill(dynamicArray<int> *values, Node<T> *start, dynamicArray<int> *order) {
    if (start->isLeaf()) {
        start->setValue(values->operator[](0));
        values->delById(0);
        return;
    }
    for (int i = 0; i < order->length(); i++) {
        if (order->operator[](i) == 0) {
            start->setValue(values->operator[](0));
            values->delById(0);
            continue;
        }
        if (order->operator[](i) - 1 < start->weight()) {
            fill(values, start->getNext(order->operator[](i) - 1), order);
        }
    }
}


#endif //INC_3RD_LAB_NTREE_HPP
