#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <queue>
using namespace std;

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
    class Node {
        friend class Tree;
    private:
        char gender;
        int height;
        string name;
        Node* left; // Mother
        Node* right; // Father
    public:
        Node(string name) {
            this->gender = EMPTY;
            this->height = 0;
            this->name = name;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    class Tree {
    public:
        /**
         * Constructors.
         * Can there be more than one constructor in a class?
         * Yes! we can have more than one constructor, as long as each has a different list 
         * of argument.
         */
        Tree() {root = nullptr;}
        Tree(string name) {
            if (name == "") throw MyException("ERROR! the input must be a non-empty string");
            root = new Node(name);
        }

        /**
         * A destructor.
         * Can there be more than one destructor in a class?
         * No! There can only one destructor in a class, no parameters and no return type.
         */
        ~Tree() {destroy(root);} // destroy is a protected method

        /**
         * Given any name refers to a mother, this method returns the tree after adding
         * her name as the left node of the given descendant.
         * NOTE that an exception would be thrown in case of descendant's non-existence, an empty 
         * string or mother's existence.
         */
        Tree& addMother(const string descendant, const string parent) {
            if (descendant == "" | parent == "") throw MyException("ERROR! the input must be a non-empty string");
            flag = 0;
            gender = FEMALE;
            insert(&root, descendant, parent); // A protected method
            if (flag == 1) return *this;
            throw MyException("ERROR! addMother method failed due to descendant's non-existence");
        }

        /**
         * Given any name refers to a father, this method returns the tree after adding
         * his name as the right node of the given descendant.
         * NOTE that an exception would be thrown in case of descendant's non-existence, an empty
         * string or father's existence.
         */
        Tree& addFather(const string descendant, const string parent) {
            if (descendant == "" | parent == "") throw MyException("ERROR! the input must be a non-empty string");
            flag = 0;
            gender = MALE;
            insert(&root, descendant, parent); // A protected method
            if (flag == 1) return *this;
            throw MyException("ERROR! addFather failed due to descendant's non-existence");
        }

        /**
         * This method displays the tree in a human friendly format.
         */
        void display() const {
            if (root == nullptr) cout << "The tree is empty" << endl;
            else traversal(root); // A protected method
        }

        /**
         * This method returns the relation between the root and any given name.
         * NOTE that an exception would be thrown in case of an empty string.
         */
        string relation(const string name) const {
            if (name == "") throw MyException("ERROR! the input must be a non-empty string");
            int len = length(root, name); // A protected method
            if (len == -1) return "unrelated"; // No relation found
            if (len == 0) return "me";
            if (len == 1) return gender == FEMALE ? "mother" : "father";
            /* if (len > 1) */ string related = "";
            for (int i = 2; i < len; i++) related += "great-"; // Holds if len is greater than 2
            return gender == FEMALE ? related += "grandmother" : related += "grandfather";
        }

        /**
         * This method finds and returns the name of any given relation.
         * NOTE that an exception would be thrown in case of an empty string, or when the 
         * tree cannot handle the given relation.
         */
        string find(const string relation) const {
            if (root == nullptr) throw MyException("ERROR! the tree is empty");
            else if (relation == "") throw MyException("ERROR! the input must be a non-empty string");

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
            string r;

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

        /**
         * Given any name, this method returns the tree after removing it and 
         * it's descendants.
         * NOTE that an exception would be thrown in case of an empty string.
         */
        Tree& remove(const string name) {
            if (root == nullptr) throw MyException("ERROR! the tree is empty");
            if (name == "") throw MyException("ERROR! the input must be a non-empty string");
            flag = 0;
            remove(&root, name); // A protected method
            if (flag == 1) return *this;
            throw MyException("ERROR! remove method failed due to name's non-existence");
        }

    protected: // Can be called by any subclass within its class, but not by unreleated classes.
        Node* root;
        void destroy(Node* current);
        void insert(Node** current, const string descendant, const string parent);
        void traversal(const Node* current) const;
        int length(const Node* current, const string name) const;
        void remove(Node** current, const string name);
        string limitedBFS(Node* current, const int height) const;
    }; // class Tree
}; // namespace family

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

            else { // Refers to a father
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
                destroy(rem); // Free memory
                flag = 1; // Removed
                return;
            }
        }

        if ((*current)->right != nullptr) {
            if ((*current)->right->name == name) {
                Node* rem = (*current)->right;
                (*current)->right = nullptr; // Update
                destroy(rem); // Free memory
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
    nodes.push(current);
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