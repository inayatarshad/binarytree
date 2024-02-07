#include <iostream>
#include <cstdlib> // For rand() function

using namespace std;

template <typename T>
class BST
{
public:
    BST();
    BST(const BST &t);
    ~BST();
    bool empty() const;
    bool search(const T x) const; // contains
    void insert(const T x);       // compose x into a tree
    void remove(const T x);
     void displayInOrder() {
        cout << "In-order traversal: ";
        inOrderTraversal(root);
        cout << endl;
    }     // decompose x from a tree

private:
    struct Node
    {
        T element;
        Node *left;
        Node *right;

        Node(const T &value, Node *leftNode = nullptr, Node *rightNode = nullptr)
            : element(value), left(leftNode), right(rightNode)
        {
            cout << "Constructor of node has been called" << endl;
        } // constructor for Node
    };
    Node *root;
    void insert(const T x, Node *&t);    // recursive function
    void remove(const T x, Node *&t);    // recursive function
    Node *findMin(Node *t) const;        // recursive function
    void makeEmpty(Node *&t);            // recursive ‘destructor’
    bool contains(const T x, Node *t) const; // recursive function
    void inOrderTraversal(Node* t) {
        if (t != nullptr) {
            inOrderTraversal(t->left);
            cout << t->element << " ";
            inOrderTraversal(t->right);
        }
    }
};

template <typename T>
BST<T>::BST() : root(nullptr)
{
    cout << "Constructor of BST has been called" << endl;
}

template <typename T>
BST<T>::BST(const BST &t)
{
    // Copy constructor of BST if needed
}

template <typename T>
BST<T>::~BST()
{
    makeEmpty(root);
    cout << "Destructor of BST has been called" << endl;
}

template <typename T>
bool BST<T>::empty() const
{
    return root == nullptr;
}

template <typename T>
bool BST<T>::search(const T x) const
{
    return contains(x, root);
}

template <typename T>
void BST<T>::insert(const T x)
{
    insert(x, root);
}

template <typename T>
void BST<T>::remove(const T x)
{
    remove(x, root);
}

template <typename T>
void BST<T>::insert(const T x, Node *&t)
{
    if (t == nullptr)
    {
        t = new Node(x);
    }
    else if (x < t->element)
    {
        insert(x, t->left);
    }
    else if (x > t->element)
    {
        insert(x, t->right);
    }
}

template <typename T>
void BST<T>::remove(const T x, Node *&t)
{
    if (t == nullptr)
    {
        return;
    }

    if (x < t->element)
    {
        remove(x, t->left);
    }
    else if (x > t->element)
    {
        remove(x, t->right);
    }
    else
    {
        if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }
}

template <typename T>
typename BST<T>::Node *BST<T>::findMin(Node *t) const
{
    while (t->left != nullptr)
    {
        t = t->left;
    }
    return t;
}

template <typename T>
void BST<T>::makeEmpty(Node *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }
}

template <typename T>
bool BST<T>::contains(const T x, Node *t) const
{
    if (t == nullptr)
    {
        return false;
    }
    else if (x == t->element)
    {
        return true;
    }
    else if (x < t->element)
    {
        return contains(x, t->left);
    }
    else
    {
        return contains(x, t->right);
    }
}

int main()
{
    BST<int> bst;

    // Insert random numbers
    for (int i = 0; i < 200; ++i)
    {
        bst.insert(rand() % 1000); // Inserting random numbers between 0 and 999
    }

    // Insert known numbers
    bst.insert(50);
    bst.insert(25);
    bst.insert(475);
    bst.insert(80);
    bst.insert(135);
    bst.insert(90);
    bst.insert(355);
bst.displayInOrder();
    // Search for known and random numbers
    cout << "Contains 50: " << bst.search(50) << endl;
    cout << "Contains 85: " << bst.search(355) << endl;
    cout << "Contains 75: " << bst.search(123) << endl;
    cout << "Contains Random Number: " << bst.search(rand() % 100) << endl;
    cout << "Contains Random Number: " << bst.search(rand() % 100) << endl;
    cout << "Contains Random Number: " << bst.search(rand() % 100) << endl;

    return 0;
}
