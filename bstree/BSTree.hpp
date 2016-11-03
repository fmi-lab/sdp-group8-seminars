#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <vector>
#include <assert.h>
template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
    Node(T data, Node* left=NULL, Node* right = NULL): data(data), left(left), right(right) {}
};

template <typename T>
class BSTree
{
    Node<T>* root;

    public:
        BSTree();
        BSTree(const BSTree<T>&);
        BSTree<T>& operator=(const BSTree<T>&);
        virtual ~BSTree();
        bool contains(const T&) const;
        void add(const T&);
        void remove(const T&);
        void print() const;
        std::vector<T> preorderTraversal() const;
        std::vector<T> inorderTraversal() const;
        std::vector<T> postorderTraversal() const;
    protected:
    private:
        void deleteAll(Node<T>*);
        Node<T>*& find(const T&, Node<T>*&);
        void print(Node<T>*, int) const;
        void preorderTraverse(Node<T>*, std::vector<T>&) const;
        void inorderTraverse(Node<T>*, std::vector<T>&) const;
        void postorderTraverse(Node<T>*, std::vector<T>&) const;
};

template <typename T>
BSTree<T>::BSTree():root(NULL) {}

template <typename T>
BSTree<T>::BSTree(const BSTree<T>& other) {
    // TODO: implement!
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& other) {
    // TODO: implement!
    return *this;
}

template <typename T>
BSTree<T>::~BSTree() {
    deleteAll(root);
}

template <typename T>
void BSTree<T>::deleteAll(Node<T>* node) {
    if (node == NULL) {
        return;
    }
    deleteAll(node->left);
    deleteAll(node->right);
    delete node;
}

template <typename T>
Node<T>*& BSTree<T>::find(const T& el, Node<T>*& node) {
    if (node == NULL || node->data == el) {
        return node;
    }
    if (node->data < el) {
        return find(el, node->right);
    }
    return find(el, node->left);
}

template <typename T>
bool BSTree<T>::contains(const T& el) const {
    return find(el, root) != NULL;
}

template <typename T>
void BSTree<T>::add(const T& el) {
    Node<T>*& existing = find(el, root);
    if (existing == NULL) {
        existing = new Node<T>(el);
    }
}

template <typename T>
void BSTree<T>::remove(const T& el) {
    Node<T>*& existing = find(el, root);
    if (existing == NULL) {
        // nothing to do
        return;
    }
    // find rightmost node of left child
    // and attach the right child to it
    Node<T>* toDelete = existing;
    Node<T>* replacement = existing->left;
    if (replacement == NULL) {
        replacement = existing->right;
    } else {
        Node<T>* rightmost = existing->left;
        while(rightmost->right != NULL) {
            rightmost = rightmost->right;
        }
        rightmost->right = existing->right;
    }
    // This will update the pointer in the parent because existing is a reference
    existing = replacement;
    // this deletes the old pointer
    delete toDelete;
}

template <typename T>
void BSTree<T>::print() const {
    print(root, 0);
}
template <typename T>
void BSTree<T>::print(Node<T>* node, int indent) const {
    if (node == NULL) {
        return;
    }
    print(node->right, indent + 1);
    for (int i = 0; i < indent; i++) {
        std::cout << '\t';
    }
    std::cout << node->data << std::endl;
    print(node->left, indent + 1);
}

template <typename T>
std::vector<T> BSTree<T>::preorderTraversal() const {
    std::vector<T> result;
    preorderTraverse(root, result);
    return result;
}

template <typename T>
void BSTree<T>::preorderTraverse(Node<T>* node, std::vector<T>& result) const {
    if (node == NULL) {
        return;
    }
    result.push_back(node->data);
    preorderTraverse(node->left, result);
    preorderTraverse(node->right, result);
}

template <typename T>
std::vector<T> BSTree<T>::inorderTraversal() const {
    std::vector<T> result;
    inorderTraverse(root, result);
    return result;
}
template <typename T>
void BSTree<T>::inorderTraverse(Node<T>* node, std::vector<T>& result) const {
    if (node == NULL) {
        return;
    }
    inorderTraverse(node->left, result);
    result.push_back(node->data);
    inorderTraverse(node->right, result);
    }

template <typename T>
std::vector<T> BSTree<T>::postorderTraversal() const {
    std::vector<T> result;
    postorderTraverse(root, result);
    return result;
}
template <typename T>
void BSTree<T>::postorderTraverse(Node<T>* node, std::vector<T>& result) const {
    if (node == NULL) {
        return;
    }
    postorderTraverse(node->left, result);
    postorderTraverse(node->right, result);
    result.push_back(node->data);
}

#endif // BSTREE_H
