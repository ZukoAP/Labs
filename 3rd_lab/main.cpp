#include <iostream>
#include "dynamicArray.hpp"
#include "NTree.hpp"
#include "Node.hpp"

int main() {
    NTree<int> tree;
    tree.addVertex(0, 1337);
    tree.addVertex(0, 1488);
    tree.addVertex(0, 15);
    tree.addVertex(1, 123);
    tree.addVertex(1,24);
    tree.addVertex(1,234);
    cout << "puk "<<tree.walk("K 3 2 1") << endl;
    NTree<int> tree2(tree);
    cout << "tuk "<<tree2.walk("K 1 2 3") << endl;
    tree2.fill("1 2 3 4 5 6 7","K 3 2 1");
    cout << "stuk "<<tree2.walk("K 1 2 3") << endl;
    tree2.delVertex(1);
    cout <<tree2.walk("K 1 2 3") << endl;
    cout << tree.getNodeById(2)->getValue() << endl;
    cout << tree.getNodeByVal(1488)->getId() << endl;
    NTree<int> *subTree = tree.subTree(tree.getNodeById(6));
    cout<< "suk " <<subTree->walk("K 1 2 3")<<endl;
    cout<< tree.hasSubTree(subTree) <<endl;

    return 0;
}
