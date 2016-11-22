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
        static Node<T>* createNode(const std::vector<T>& inorder, const std::vector<T>& preorder);
        static BSTree<T>* reconstruct(const std::vector<T>& inorder, const std::vector<T>& preorder);
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

template <typename T>
int findIndex(const T& value, const std::vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (value == vec[i]) {
            return i;
        }
    }
    // return -1 if the value is not found
    return -1;
}
template <typename T>
Node<T>* BSTree<T>::createNode(const std::vector<T>& inorder, const std::vector<T>& preorder) {
    if (preorder.empty()) {
        // No more nodes
        return NULL;
    }
    const T& rootValue = preorder[0];
    Node<T>* result = new Node<T>(rootValue);
    int inorderPosition = findIndex(rootValue, inorder);
    // rootValue със сигурност трябва да го има в inorder списъка, ако не - грешка
    assert(inorderPosition != -1);
    // навсякъде по-надолу използваме конструктор на std::vector, който копира част от съществуващ вектор vec
    // в друг вектор. Този конструктор приема два параметъра:
    // std::vector(std::vector<T>::iterator vec_iter_start, std::vector<T>::iterator vec_iter_end)
    // vec_iter_start е итератор, сочещ към началната позиция, от която искаме да започнем да копираме.
    // Тази позиция може да е vec.begin(), което е началото на съществуващия вектор, или vec.begin() + i,
    // ако искаме да започнем от i-та позиция.
    // vec_iter_end е итератор, сочещ позицията СЛЕД последната, която искаме да копираме.
    // Това може да е vec.end(), което е позицията след края на вектора, или отново vec.begin() + j, ако искаме да
    // копираме всички елементи с индекси [i, j)
    // Например std::vector(vec.begin(), vec.end()) прави пълно копие на вектора vec

    // Inorder обхождането на лявото поддърво започва от началото на inorder за цялото дърво
    // и приключва до позицията, в която е коренът
    std::vector<T> leftSubtreeInorder = std::vector<T>(inorder.begin(),
                                                       inorder.begin() + inorderPosition);
    // preorder обхождането на лявото поддърво започва от втория елемент на preorder за цялото дърво
    // (първият елемент е самият корен) и е с дължина, колкото е и дължината на inorder обхождането
    std::vector<T> leftSubtreePreorder = std::vector<T>(preorder.begin() + 1,
                                                        preorder.begin() + 1 + inorderPosition);
    // рекурсивно построяваме лявото поддърво
    result->left = createNode(leftSubtreeInorder, leftSubtreePreorder);

    // Inorder обхождането на дясното поддърво започва от позицията, в която е коренът, и завършва в края
    // на inorder списъка за цялото дърво
    std::vector<T> rightSubtreeInorder = std::vector<T>(inorder.begin() + inorderPosition + 1,
                                                        inorder.end());
    // preorder обхождането на дясното поддърво започва от края на preorder обхождането на лявото поддърво
    // и завършва в края на preorder списъка за цялото дърво
    std::vector<T> rightSubtreePreorder = std::vector<T>(preorder.begin() + 1 + inorderPosition,
                                                         preorder.end());
    // рекурсивно построяваме дясното поддърво
    result->right = createNode(rightSubtreeInorder, rightSubtreePreorder);

    return result;
}
template <typename T>
BSTree<T>* BSTree<T>::reconstruct(const std::vector<T>& inorder, const std::vector<T>& preorder) {
    Node<T>* node = createNode(inorder, preorder);
    BSTree<T>* result = new BSTree<T>();
    result->root = node;
    return result;
}
#endif // BSTREE_H
