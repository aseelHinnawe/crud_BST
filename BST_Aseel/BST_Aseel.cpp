
#include <iostream>
using namespace std;
class Node {
    int val;
    Node* right;
    Node* left;

public:
    Node() {
        val = 0;
        right = nullptr;
        left = nullptr;
    }
    Node(int val,Node* right, Node* left) {
        this->val = val;
        this->right = right;
        this->left = left;
    }

    int getVal() {
        return val;
    }
    void setVal(int val) {
        this->val = val;
    }

    Node* getRight() {
        return right;
    }
    void setRight(Node* right) {
        this->right = right;
    }

    Node* getLeft() {
        return left;
    }
    void setLeft(Node* left) {
        this->left = left;
    }
};

class BST {
    Node* root;

public:
    BST() {
        root = nullptr;
    }

    bool search(int value) {
        Node* p = root;
        while (p != nullptr) {
            if (value == p->getVal()) {
                return true;
            }
            else if (value > p->getVal()) {
                p = p->getRight();
            }
            else {
                p = p->getLeft();
            }
        }
        return false;
    }

    void add(int value) {
        if (search(value)) return;

        Node* n = new Node(value, nullptr, nullptr);
        if (root == nullptr) {
            root = n;
            return;
        }

        Node* p = root;
        while (true) {
            if (value > p->getVal()) {
                if (p->getRight() == nullptr) break;
                p = p->getRight();
            }
            else {
                if (p->getLeft() == nullptr) break;
                p = p->getLeft();
            }
        }
        if (value > p->getVal()) {
            p->setRight(n);
        }
        else {
            p->setLeft(n);
        }
    }

    void inOrder(Node *r) {
        if (r == nullptr) return;
        inOrder(r->getLeft());
        cout << r->getVal()<<" ";
        inOrder(r->getRight());
    }
    void preOrder(Node* r) {
        if (r == nullptr) return;
        cout << r->getVal() << " ";
        preOrder(r->getLeft());
        preOrder(r->getRight());
    }
    void postOrder(Node* r) {
        if (r == nullptr) return;
        postOrder(r->getLeft());
        postOrder(r->getRight());
        cout << r->getVal() << " ";
    }

    void print() {
        cout << "in-order: ";  inOrder(root); cout << endl;
        cout << "pre-order: ";  preOrder(root); cout << endl;
        cout << "post-order: ";  postOrder(root); cout << endl;
    }  

    void remove(int value) {
        if (!search(value)) return;

        Node* curr = root;
        Node* prev = root;
        while (value != curr->getVal()) {
            prev = curr;
            if (value > curr->getVal()) {
                curr = curr->getRight();
            }
            else {
                curr = curr->getLeft();
            }
        }

        // root with no children
        if (curr == root && curr->getLeft() == nullptr && curr->getRight() == nullptr) {
            delete curr;
            root = nullptr;
            return;
        }

        // root with only right child
        if (curr == root && curr->getLeft() == nullptr) {
            root = curr->getRight();
            delete curr;
            return;
        }

        // root with only left child
        if (curr == root && curr->getRight() == nullptr) {
            root = curr->getLeft();
            delete curr;
            return;
        }

        // leaf node
        if (curr->getRight() == nullptr && curr->getLeft() == nullptr) {
            if (value > prev->getVal()) {
                prev->setRight(nullptr);
            }
            else {
                prev->setLeft(nullptr);
            }
            delete curr;
        }
        else if(curr->getRight() == nullptr){ // has left child
            if (curr->getVal() > prev->getVal()) {
                prev->setRight(curr->getLeft());
            }
            else {
                prev->setLeft(curr->getLeft());
            }
            delete curr;
        }
        else if (curr->getLeft() == nullptr) { // has right child
            if (curr->getVal() > prev->getVal()) {
                prev->setRight(curr->getRight());
            }
            else {
                prev->setLeft(curr->getRight());
            }
            delete curr;
        }
        else if (curr->getLeft() != nullptr && curr->getRight() != nullptr) { // has left and right child
            Node* p = curr->getRight();
            Node* prev2 = curr;

            if (p->getLeft() == nullptr) {
                curr->setVal(p->getVal());
                curr->setRight(p->getRight());
                delete p;
            }
            else {
                while (p->getLeft() != nullptr) {
                    prev2 = p;
                    p = p->getLeft();
                }

                curr->setVal(p->getVal());
                prev2->setLeft(p->getRight());
                delete p;
            }
        }
    }

    void update(int oldValue, int newValue) {
        if (!search(oldValue)) return;
        if (search(newValue)) return;

        remove(oldValue);
        add(newValue);
    }

    bool isEmpty() {
        return root == nullptr;
    }  
};

int main()
{
    BST bst;
    bst.add(50);
    bst.add(40);
    bst.add(60);
    bst.add(35);
    bst.add(45);
    bst.add(55);
    bst.add(70);
    bst.add(30);
    bst.add(65);
    bst.add(80);
    
    cout<<bst.search(30)<<endl;
    cout << bst.isEmpty() << endl;
    bst.print(); cout << endl;

    bst.remove(30);
    cout << "after remove: "<<endl;
    bst.print(); cout << endl;

    bst.update(60, 58);
    cout << "after update: " << endl;
    bst.print(); cout << endl;

}