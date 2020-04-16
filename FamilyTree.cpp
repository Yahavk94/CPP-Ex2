#include <string>
#include <bits/stdc++.h>
#include <queue>
#include "FamilyTree.hpp"

#define FEMALE 0
#define MALE 1
#define EMPTY 2
char gender = 0; // 0 refers to a mother and 1 refers to a father
char flag = 0; // For indication purposes

class MyException : public exception {
private:
    string msg;
public:
    MyException(string msg) {this->msg = msg;}
    ~MyException() {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

namespace family {
    Node::Node(string name) {
        this->gender = EMPTY;
        this->height = 0;
        this->name = name;
        this->left = nullptr;
        this->right = nullptr;
    }

    Tree::Tree() {root = nullptr;}
    Tree::Tree(string name) {
        if (name == "") throw MyException("ERROR! the input must be a non-empty string");
        root = new Node(name);
    }

    Tree::~Tree() {destroy(&root);}

    Tree& Tree::addMother(const string descendant, const string parent) {
        if (root == nullptr) throw MyException("ERROR! addMother method failed since the given tree is empty");
        if (descendant == "" | parent == "") throw MyException("ERROR! the input must be a non-empty string");

        flag = 0;
        gender = FEMALE;
        insert(&root, descendant, parent); // A protected method
        if (flag == 1) return *this;
        throw MyException("ERROR! addMother method failed due to descendant's non-existence");
    }

    Tree& Tree::addFather(const string descendant, const string parent) {
        if (root == nullptr) throw MyException("ERROR! addFather method failed since the given tree is empty");
        if (descendant == "" | parent == "") throw MyException("ERROR! the input must be a non-empty string");

        flag = 0;
        gender = MALE;
        insert(&root, descendant, parent); // A protected method
        if (flag == 1) return *this;
        throw MyException("ERROR! addFather failed due to descendant's non-existence");
    }

    void Tree::display() const {
        if (root == nullptr) cout << "The tree is empty" << endl;
        else traversal(root); // A protected method
    }

    string Tree::relation(const string name) const {
        if (root == nullptr) throw MyException("ERROR! relation method failed since the given tree is empty");
        if (name == "") throw MyException("ERROR! the input must be a non-empty string");

        int len = length(root, name); // A protected method
        if (len == -1) return "unrelated"; // No relation found
        if (len == 0) return "me";
        if (len == 1) return gender == FEMALE ? "mother" : "father";
        /* if (len > 1) */ string related = "";
        for (int i = 2; i < len; i++) related += "great-"; // Holds if len is greater than 2
        return gender == FEMALE ? related += "grandmother" : related += "grandfather";
    }

    string Tree::find(const string relation) const {
        if (root == nullptr) throw MyException("ERROR! find method failed since the given tree is empty");
        if (relation == "") throw MyException("ERROR! the input must be a non-empty string");

        vector<string> tokens;
        stringstream check1(relation);
        string intermediate;
        while (getline(check1, intermediate, '-')) // Tokenizing a string
            tokens.push_back(intermediate);
            
        int height = 0;
        int i = 0;
        while (i < tokens.size() - 1) { // For counting purpose
            if (tokens[i] != "great") throw MyException("ERROR! invalid input");
            height++;
            i++;
        }

        i = tokens.size() - 1; // To identify the relation type
        if (tokens[i] == "me") return root->name; // The tree is non-empty

        else if (tokens[i] == "mother") {
            if (root->left == nullptr) throw MyException("No relation found");
            return root->left->name;
        }

        else if (tokens[i] == "father") {
            if (root->right == nullptr) throw MyException("No relation found");
            return root->right->name;
        }

        else if (tokens[i] == "grandmother") {
            gender = FEMALE;
            return limitedBFS(root, height + 2);
        }

        else if (tokens[i] == "grandfather") {
            gender = MALE;
            return limitedBFS(root, height + 2);
        }

        else throw MyException("Cannot handle the specified relation");
    }

    Tree& Tree::remove(const string name) {
        if (root == nullptr) throw MyException("ERROR! remove method failed since the given tree is empty");
        if (name == "") throw MyException("ERROR! the input must be a non-empty string");

        if (root->name == name) // The tree is non-empty
            throw MyException("ERROR! remove method failed due to an attempt to destory the tree");

        flag = 0;
        remove(&root, name); // A protected method
        if (flag == 1) return *this;
        throw MyException("ERROR! remove method failed due to name's non-existence");
    }
};

using namespace family;

void Tree::destroy(Node** current) {
    if (*current != nullptr) {
        destroy(&((*current)->left));
        destroy(&((*current)->right));
        delete(*current);
    }
}

void Tree::insert(Node** current, const string descendant, const string parent) {
    if (*current != nullptr) {
        if ((*current)->name == descendant) { // Match found
            if (gender == FEMALE) {
                if ((*current)->left == nullptr) { // Check mother's non-existence
                    (*current)->left = new Node(parent);
                    (*current)->left->gender = FEMALE;
                    (*current)->left->height = 1 + (*current)->height;
                    flag = 1; // Added
                    return;
                }

                else throw MyException("ERROR! addMother method failed since duplications are not allowed");
            }

            else {
                if ((*current)->right == nullptr) { // Check father's non-existence
                    (*current)->right = new Node(parent);
                    (*current)->right->gender = MALE;
                    (*current)->right->height = 1 + (*current)->height;
                    flag = 1; // Added
                    return;
                }

                else throw MyException("ERROR! addFather method failed since duplications are not allowed");
            }
        }

        insert(&((*current)->left), descendant, parent);
        insert(&((*current)->right), descendant, parent);
    }
}

void Tree::traversal(const Node* current) const {
    if (current != nullptr) {
        // Print the specified node and it's parents names
        cout << current->name << endl;
        if (current->left != nullptr) cout << "Mother's name is " + current->left->name << endl;
        else cout << "Mother's name is unknown" << endl; // Print unknown in case of non-existence
        if (current->right != nullptr) cout << "Father's name is " + current->right->name << endl;
        else cout << "Father's name is unknown" << endl; // Print unknown in case of non-existence
        cout << endl;

        traversal(current->left);
        traversal(current->right);
    }
}

int Tree::length(const Node* current, const string name) const {
	if (current == nullptr) return -1;

	int len = -1;
	if (current->name == name) { // Match found
        if (current->gender == EMPTY) return 0; // Refers to the root
        if (current->gender == FEMALE) gender = FEMALE;
        else gender = MALE;
        return len + 1;
    }

    else if ((len = length(current->left, name)) >= 0 || (len = length(current->right, name)) >= 0)
        return len + 1;

	return len;
}

void Tree::remove(Node** current, const string name) {
    if (*current != nullptr) {
        if ((*current)->left != nullptr) {
            if ((*current)->left->name == name) {
                Node* rem = (*current)->left;
                (*current)->left = nullptr; // Update
                destroy(&rem); // Free memory
                flag = 1; // Removed
                return;
            }
        }

        if ((*current)->right != nullptr) {
            if ((*current)->right->name == name) {
                Node* rem = (*current)->right;
                (*current)->right = nullptr; // Update
                destroy(&rem); // Free memory
                flag = 1; // Removed
                return;
            }
        }

        remove(&((*current)->left), name);
        remove(&((*current)->right), name);
    }
}

string Tree::limitedBFS(Node* current, const int height) const {
    queue<Node*> nodes;
    nodes.push(current); // The tree is non-empty
    while (!nodes.empty()) {
        if (nodes.front()->height > height) throw MyException("No relation found");
        if (nodes.front()->height == height) {
            if (nodes.front()->gender == gender) return nodes.front()->name;
        }

        if (nodes.front()->left != nullptr) nodes.push(nodes.front()->left);
        if (nodes.front()->right != nullptr) nodes.push(nodes.front()->right);
        nodes.pop();
    }

    throw MyException("No relation found");
}