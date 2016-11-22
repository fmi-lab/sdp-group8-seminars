#include <iostream>
#include <vector>
#include "BSTree.hpp"

using namespace std;

template <typename T>
void printVector(const std::vector<T>& vec) {
    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
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

    cout << endl << "-------------------------" << endl;
    cout << "Test tree reconstruction" << endl;
    char preorder[] = "PSBKRJCMDE";
    char inorder[] = "SKBPCJRDME";
    std::vector<char> preorderVec = std::vector<char>(preorder, preorder + 10);
    std::vector<char> inorderVec = std::vector<char>(inorder, inorder + 10);
    BSTree<char>* reconstructed = BSTree<char>::reconstruct(inorderVec, preorderVec);
    reconstructed->print();
    std::vector<char> postorderVec = reconstructed->postorderTraversal();
    cout << "Postorder traversal: ";
    printVector(postorderVec);
    delete reconstructed;
    return 0;
}
