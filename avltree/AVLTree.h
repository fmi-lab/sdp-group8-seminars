#ifndef AVLTREE_H
#define AVLTREE_H
template <typename T>
struct AVLNode {
    T data;
    int height;
    AVLNode<T>* left;
    AVLNode<T>* right;
    AVLNode(T data, int h = 1, AVLNode<T>* l=NULL, AVLNode<T>* r = NULL)
        :data(data), height(h), left(l), right(r) {}
};
template <typename T>
int getHeight(AVLNode<T>* node) {
    return node? node->height: 0;
}
template <typename T>
int recalculateHeight(AVLNode<T>* node) {
    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename T>
class AVLTree
{
    public:
        AVLTree();
        AVLTree(const AVLTree&);
        AVLTree<T>& operator=(const AVLTree&);
        ~AVLTree();
        bool contains(const T&) const;
        AVLTree<T>&  add(const T&);
        AVLTree<T>&  remove(const T&);
        bool checkBalance() const;
        void print() const;
    protected:
    private:
        AVLNode<T>* root;
        void add (const T&, AVLNode<T>*&);
        void remove(const T&, AVLNode<T>*&);
        void balanceAfterRemove(AVLNode<T>*&);
        bool contains(const T&, AVLNode<T>*) const;
        void leftRotate(AVLNode<T>*&);
        void rightRotate(AVLNode<T>*&);
        int getNodeBalance(AVLNode<T>*) const;
        bool checkBalance(AVLNode<T>*) const;
        void print(AVLNode<T>*, int) const;
};

template <typename T>
AVLTree<T>::AVLTree():root(NULL) {}
template <typename T>
AVLTree<T>::AVLTree(const AVLTree& other) {
    // TODO: implement
}
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& other) {
    // TODO: implement
    return *this;
}
template <typename T>
AVLTree<T>::~AVLTree() {
    // TODO: implement
}

template <typename T>
bool AVLTree<T>::contains(const T& el) const {
    return contains(el, root);
}
template <typename T>
bool AVLTree<T>::contains(const T& el, AVLNode<T>* node) const {
    if (node == NULL) { return false; }
    if (node->data == el) { return true; }
    if (el < node->data) { return contains(el, node->left);}
    else { return contains(el, node->right); }
}

template <typename T>
AVLTree<T>&  AVLTree<T>::remove(const T& el) {
    remove(el, root);
    return *this;
}

template <typename T>
void AVLTree<T>::balanceAfterRemove(AVLNode<T>*& node) {
    int balance = getHeight(node->left) - getHeight(node->right);
    std::cout << "Balance of node " << node->data << ": " << balance << std::endl;
    std::cout << "Left child height: " << getHeight(node->left) << std::endl;
    std::cout << "Right child height: " << getHeight(node->right) << std::endl;
    if (balance < -1) {
        // дясното дърво е по-високо, трябва да направим лява ротация
        // но първо трябва да видим кое поддърво на десния наследник е по-високо
        int leftHeight = getHeight(node->right->left);
        int rightHeight = getHeight(node->right->right);
        if (leftHeight <= rightHeight) {
            // вдясно е по-високо, така че само една лява ротация е достатъчна
            std::cout << "right right case, rotating left" << node->data << std::endl;
            leftRotate(node);
        } else {
            // вляво е по-високо, тогава дясната ротация може да доведе отново до небалансирано дърво
            // тъй като лявото поддърво всъщност "слиза" по-надолу при ротацията
            // затова първо завъртаме надясно, за да стигнем до горния случай
            // тогава сме сигурни, че лява ротация ще свърши работа
            std::cout << "right right case, rotating right " << node->right->data
                << " and then left " << node->data << std::endl;
            rightRotate(node->right);
            leftRotate(node);
        }
    } else if (balance > 1) {
        // симетрично на горния случай
        // разглеждаме левия наследник на node, понеже той има по-голяма височина
        int leftHeight = getHeight(node->left->left);
        int rightHight = getHeight(node->left->right);
        if (leftHeight >= rightHight) {
            // ако за него лявото поддърво също е по-високо, достатъчна ни е само една дясна ротация
            std::cout << "left left case, rotating right" << node->data << std::endl;
            rightRotate(node);
        } else {
            // ако обаче дясното му поддърво е по-високо, дясна ротация ще доведе до небалансирано дърво
            // и първо правим лява ротация
            std::cout << "left right case, rotating left " << node->left->data
                << " and then right " << node->data << std::endl;
            leftRotate(node->left);
            rightRotate(node);
        }
    }
    // ако балансът е между -1 и 1, този node е балансиран - няма нужда нищо да правим
}

template <typename T>
void AVLTree<T>::remove(const T& el, AVLNode<T>*& node) {
    if (node == NULL) {
        // we could not find the el in the tree, nothing to do
        return;
    } else if (node->data == el) {
        // this is the node we have to delete
        AVLNode<T>* toDelete = node;
        AVLNode<T>* replacement = node->left;
        if (replacement == NULL) {
            replacement = node->right;
        } else {
            AVLNode<T>* rightmost = node->left;
            while(rightmost->right != NULL) {
                rightmost = rightmost->right;
            }
            rightmost->right = node->right;
        }
        // This will update the pointer in the parent because node is a reference
        node = replacement;
        // this deletes the old pointer
        delete toDelete;
        return;
    } else if (el < node->data) {
        remove(el, node->left);
    } else {
        remove(el, node->right);
    }

    // Вече сме минали през рекурсивните извиквания за remove и елементът е изтрит
    // това значи, че височината на node може да е намаляла и трябва да я преизчислим
    node->height = recalculateHeight(node);

    // сега трябва да ребалансираме поддървото с корен в node, ако има нужда
    // това ще се случва на всяка стъпка от рекурсията, докато не стигнем корена на дървото
    balanceAfterRemove(node);
}

template <typename T>
AVLTree<T>& AVLTree<T>::add(const T& el) {
    add(el, root);
    return *this;
}

template <typename T>
void AVLTree<T>::add(const T& el, AVLNode<T>*& node) {
    // Add the node as in a normal BSTree
    if (node == NULL) {
        node = new AVLNode<T>(el);
        return;
    }
    if (node->data == el) {
        // element already exist in the tree, do nothing
        return;
    }
    if (el < node->data) {
        add(el, node->left);
    } else {
        add(el, node->right);
    }

    // we get to this point after we exit the recursive calls to add
    // so at this point the new node has been added as a (grand...)child of this node
    // and its height needs to be updated
    node->height = recalculateHeight(node);

    // now check whether this node has become unbalanced
    int balance = getHeight(node->left) - getHeight(node->right);

    if (balance > 1) {
        // too many nodes on the left => we need a right rotate
        // check for right or right-left rotate
        if (el < node->left->data) {
            // the new node was added to the left of node->left, so we need to do a single rotate
            rightRotate(node);
        } else {
            // it was added to the right of node->left, so we need a left rotation from the child and then a right
            leftRotate(node->left);
            rightRotate(node);
        }
    } else if (balance < -1) {
        // too many nodes on the right
        if (el > node->right->data) {
            leftRotate(node);
        } else {
            rightRotate(node->right);
            leftRotate(node);
        }
    } else {
         // this node is balanced - nothing to do
    }
}

template <typename T>
void AVLTree<T>::rightRotate(AVLNode<T>*& node) {
    AVLNode<T>* currentParent = node;
    node = node->left;
    currentParent->left = node->right;
    node->right = currentParent;
    // recalculate heights of the nodes that were moved around
    node->right->height = recalculateHeight(node->right);
    node->height = recalculateHeight(node);
}

template <typename T>
void AVLTree<T>::leftRotate(AVLNode<T>*& node) {
    AVLNode<T>* currentParent = node;
    node = node->right;
    currentParent->right = node->left;
    node->left = currentParent;
    // recalculate heights of the nodes that were moved around
    node->left->height = recalculateHeight(node->left);
    node->height = recalculateHeight(node);
}

template <typename T>
bool AVLTree<T>::checkBalance() const {
    return checkBalance(root);
}
template <typename T>
bool AVLTree<T>::checkBalance(AVLNode<T>* node) const {
    if (node == NULL) { return true; }
    int balance = getNodeBalance(node);
    return balance >= -1 && balance <= 1 && checkBalance(node->left) && checkBalance(node->right);
}
template <typename T>
int AVLTree<T>::getNodeBalance(AVLNode<T>* node) const {
    if (node == NULL) {return 0;}
    return getHeight(node->left) - getHeight(node->right);
}
template <typename T>
void AVLTree<T>::print() const {
    print(root, 0);
}

/**
 * Отпечатва дървото хоризонтално, коренът е най-вляво на екрана, а листата - най-вдясно
 * Лявото поддърво се отпечатва под дясното, т.е. дървото се отпечатва завъртяно на 90 градуса,
 * обратно на часовниковата стрелка.
 * В скоби е отпечатана височината на съответния елемент в дървото.
 */
template <typename T>
void AVLTree<T>::print(AVLNode<T>* node, int indent) const {
    if (node == NULL) {
        return;
    }
    print(node->right, indent + 1);
    for (int i = 0; i < indent; i++) {
        std::cout << "\t\t";
    }
    std::cout << node->data << "(h" << node->height << ")" << std::endl;
    print(node->left, indent + 1);
}


#endif // AVLTREE_H
