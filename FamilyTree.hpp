#include <iostream>
#include <string>
using namespace std;

#define EMPTY 2
char gender = 0; // 0 refers to mother and 1 refers to father

namespace family {
    class Node {
        friend class Tree;
    private:
        char gender;
        string name;
        Node* left; // Mother
        Node* right; // Father
    public:
        Node(string name) {
            this->gender = EMPTY;
            this->name = name;
            this->left = nullptr;
            this->right = nullptr;
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
            else if (len == 0) return "me";
            else if (len == 1) return gender == 0 ? "mother" : "father";
            else {
                string related = "";
                for (int i = 2; i < len; i++)
                    related += "great-";
                if (gender == 0) related += "grandmother";
                else related += "grandfather";
                return related;
            }
        }

        Tree& remove(const string name) {
            remove(root, name);
            return *this;
        }

    protected:
        Node* root;
        void destroy(Node* current);
        void insert(Node** current, const string descendant, const string parent);
        void traversal(const Node* current) const;
        int length(const Node* current, const string name) const;
        void remove(Node* current, const string name);
    };
};

using namespace family;

void Tree::destroy(Node* current) {
    if (current != nullptr) {
        destroy(current->left);
        destroy(current->right);
        delete(current);
    }
}

void Tree::insert(Node** current, const string descendant, const string parent) {
    if (*current != nullptr) {
        if ((*current)->name == descendant) {
            if (gender == 0) {
                if ((*current)->left == nullptr) {
                    (*current)->left = new Node(parent);
                    (*current)->left->gender = 0;
                    return;
                }
            }

            else if (gender == 1) {
                if ((*current)->right == nullptr) {
                    (*current)->right = new Node(parent);
                    (*current)->right->gender = 1;
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
        cout << current->name << endl;
        if (current->left != nullptr) cout << "Mother's name is " + current->left->name << endl;
        else cout << "Mother's name is unknown" << endl;
        if (current->right != nullptr) cout << "Father's name is " + current->right->name << endl;
        else cout << "Father's name is unknown" << endl;
        cout << endl;

        traversal(current->left);
        traversal(current->right);
    }
}

int Tree::length(const Node* current, const string name) const {
	if (current == nullptr) return -1;

	int len = -1;
	if (current->name == name) {
        if (current->gender == EMPTY) return 0;
        if (current->gender == 0) gender = 0;
        else gender = 1;
        return len + 1;
    }

    else if ((len = length(current->left, name)) >= 0 || (len = length(current->right, name)) >= 0)
        return len + 1;

	return len;
}

void Tree::remove(Node* current, const string name) {
    if (current != nullptr) {
        if (current->left != nullptr) {
            if (current->left->name == name) {
                Node* rem = current->left;
                current->left = nullptr;
                destroy(rem);
                return;
            }
        }

        else if (current->right != nullptr) {
            if (current->right->name == name) {
                Node* rem = current->right;
                current->right = nullptr;
                destroy(rem);
                return;
            }
        }

        remove(current->left, name);
        remove(current->right, name);
    }
}