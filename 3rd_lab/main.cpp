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
    tree.addVertex(1, 24);
    tree.addVertex(1, 234);
    cout << "puk " << tree.walk("K 3 2 1") << endl;
    cout << "puk am " << tree.amount() << endl;
    tree.rearrange();
    cout << "puk rearr " << tree.walk("K 1 2 3") << endl;
    NTree<int> tree2(tree);
    cout << "tuk " << tree2.walk("K 1 2 3") << endl;
    tree2.fill("1 2 3 4 5 6 7", "K 3 2 1");
    cout << "tree 2 after fill, before delete " << tree2.walk("K 1 2 3") << endl;
    tree2.delVertex(1);
//    tree2.gentlyDelete(1);
    cout << "delete " << tree2 << endl;
    tree2.rearrange();
    cout << tree2.walk("K 1 2 3 4 5 6 7 8") << endl;
    cout << tree.getNodeById(2)->getValue() << endl;
    cout << tree.getNodeByVal(1488)->getId() << endl;
    NTree<int> *subTree = tree.subTree(tree.getNodeById(6));
    cout << "suk " << subTree->walk("K 1 2 3 4 5 6 7 8") << endl;
//    cout<< tree.hasSubTree(subTree) <<endl;
    NTree<int> treeMap = tree2.map([](int &a) { a = a + 1; });
    cout << "map " << treeMap.walk("K 1 2 3 4 5 6 7 8") << endl;
    NTree<int> treeWhere = tree2.where([](int &a) {
        if (a % 2 == 0)
            return 1;
        else
            return 0;
    });
    cout << "where " << treeWhere.walk("K 1 2 3 4 5 6 7 8") << endl;
    int reduceResult = tree2.reduce([](int &a, int m) {
        return a * m;
    }, 2);
    cout << reduceResult << endl;

    return 0;
}
