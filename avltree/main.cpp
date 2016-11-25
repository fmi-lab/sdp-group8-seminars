#include <iostream>
#include "AVLTree.h"
using namespace std;

int main()
{
    AVLTree<int> avlTree;
    avlTree.add(20);
    avlTree.add(4).add(26);
    avlTree.add(3).add(9).add(21).add(30);
    avlTree.add(2).add(7).add(11);
    cout << "Test Case 3a - add 15: " << endl;
    avlTree.add(15);
    avlTree.print();

    AVLTree<double> removeTest;
    removeTest.add(5)
        .add(2).add(8)
        .add(1).add(3).add(7).add(10)
        .add(4).add(6).add(7.5).add(9)
        .add(7.4);
    cout << endl << endl;
    cout << "Modified delete test Case 3" << endl;
    removeTest.print();
    cout << "Removing value 1" << endl;
    removeTest.remove(1);
    removeTest.print();
    return 0;
}
