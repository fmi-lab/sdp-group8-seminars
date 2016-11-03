#include <iostream>
#include <vector>
#include "BSTree.hpp"

using namespace std;

void printVector(const std::vector<int>& vec) {
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
}
int main()
{
    BSTree<int> bst;
    bst.add(10);
    bst.add(-20);
    bst.add(15);
    bst.add(5);
    bst.add(10); // should not add anything
    bst.add(-5);
    bst.add(17);
    cout << "Constructed tree: " << endl;
    bst.print();
    cout << endl;
    std::cout << "Inorder traversal: ";
    printVector(bst.inorderTraversal());
    std::cout << std::endl;
    std::cout << "Postorder traversal: ";
    printVector(bst.postorderTraversal());
    std::cout << std::endl;
    std::cout << "Preorder traversal: ";
    printVector(bst.preorderTraversal());
    std::cout << std::endl;

    bst.remove(10);
    cout << endl << "After removing the root: " << endl;
    bst.print();
    return 0;
}
