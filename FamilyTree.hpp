#include <iostream>
#include <string>
using namespace std;

int gender = 0; // 0 refers to mother and 1 refers to father

namespace family {
    class Node {
        friend class Tree;
    private:
        Node* left; // Mother
        Node* right; // Father
        Node* parent;
        string name;
    public:
        Node(string name) {
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->name = name;
        }
    };

    class Tree {
    public:
        Tree() {root = nullptr;} // Constructor
        Tree(string name) {root = new Node(name);} // Constructor
        ~Tree() {destroy(root);} /* Destructor
        Can there be more than one destructor in a class?
        No! There can only one destructor in a class, no parameters and no return type. */

        Tree& addMother(const string descendant, const string parent) {
            gender = 0;
            insert(&root, descendant, parent);
            return *this;
        }

        Tree& addFather(const string descendant, const string parent) {
            gender = 1;
            insert(&root, descendant, parent);
            return *this;
        }

        void display() const {traversal(root);}

        string relation(const string name) const {
            int len = length(root, name);

            if (len == -1) return "unrelated";
            if (len == 0) return "me";
            if (len == 1) {
                if (gender == 0) return "mother";
                else return "father";
            }

            string related = "";
            for (int i = 2; i < len; i++) related += "great-";

            if (gender == 0) related += "grandmother";
            else related += "grandfather";
            return related;
        }

    protected:
        Node* root;
        void destroy(Node* current);
        void insert(Node** current, const string descendant, const string parent);
        void traversal(const Node* current) const;
        int length(const Node* current, const string name) const;
    };
};

using namespace family;

void Tree::insert(Node** current, const string descendant, const string parent) {
    if (*current != nullptr) {
        if ((*current)->name == descendant) {
            if (gender == 0) {
                if ((*current)->left == nullptr) {
                    (*current)->left = new Node(parent);
                    (*current)->left->parent = *current;
                    return;
                }
            }

            else if (gender == 1) {
                if ((*current)->right == nullptr) {
                    (*current)->right = new Node(parent);
                    (*current)->right->parent = *current;
                    return;
                }
            }
        }

        insert(&((*current)->left), descendant, parent);
        insert(&((*current)->right), descendant, parent);
    }
}

void Tree::traversal(const Node* current) const {
    if (current != nullptr) {
        cout << "Name: " + current->name << endl;
        if (current->left != nullptr) cout << "Mother's name: " + current->left->name << endl;
        else cout << "Mother's name: unknown" << endl;
        if (current->right != nullptr) cout << "Father's name: " + current->right->name << endl;
        else cout << "Father's name: unknown" << endl;
        cout << endl;

        traversal(current->left);
        traversal(current->right);
    }
}

int Tree::length(const Node* current, const string name) const {
	if (current == nullptr) return -1;

	int len = -1;
	if (current->name == name) {
        if (current->parent == nullptr) return 0; // The length of the path to the root is 0.
            
        if (current->parent->left != nullptr) { // Check mother's existence
            if (current->parent->left->name == name) gender = 0;
            else gender = 1;
        }

        else gender = 1;
        return len + 1;
    }

    else if ((len = length(current->left, name)) >= 0 || (len = length(current->right, name)) >= 0)
        return len + 1;

	return len;
}

void Tree::destroy(Node* current) {
    if (current != nullptr) {
        destroy(current->left);
        destroy(current->right);
        delete(current);
    }
}