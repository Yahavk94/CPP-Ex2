#pragma once

#include <iostream>
using namespace std;

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
        Node(string name);
    }; // class Node

    class Tree {
    public:
        /**
         * Constructors.
         * Can there be more than one constructor in a class?
         * Yes! we can have more than one constructor, as long as each has a different list 
         * of argument.
         */
        Tree();
        Tree(string name);

        /**
         * A destructor.
         * Can there be more than one destructor in a class?
         * No! There can only one destructor in a class, no parameters and no return type.
         */
        ~Tree(); // destroy is a protected method

        /**
         * Given any name refers to a mother, this method returns the tree after adding
         * her name as the left node of the given descendant.
         * NOTE that an exception would be thrown in case of descendant's non-existence, an empty 
         * string, an empty tree or mother's existence.
         */
        Tree& addMother(const string descendant, const string parent);

        /**
         * Given any name refers to a father, this method returns the tree after adding
         * his name as the right node of the given descendant.
         * NOTE that an exception would be thrown in case of descendant's non-existence, an empty
         * string, an empty tree or father's existence.
         */
        Tree& addFather(const string descendant, const string parent);

        /**
         * This method displays the tree in a human-friendly format.
         */
        void display() const;

        /**
         * This method returns the relation between the root and any given name.
         * NOTE that an exception would be thrown in case of an empty string or an empty tree.
         */
        string relation(const string name) const;

        /**
         * This method finds and returns the name of any given relation.
         * NOTE that an exception would be thrown in case of an empty string, an empty tree or when 
         * the tree cannot handle the given relation.
         */
        string find(const string relation) const;

        /**
         * Given any name, this method returns the tree after removing it and 
         * it's descendants.
         * NOTE that an exception would be thrown in case of an empty string or an empty tree.
         */
        Tree& remove(const string name);

    protected: // Can be called by any subclass within its class, but not by unreleated classes.
        Node* root;
        void destroy(Node** current);
        void insert(Node** current, const string descendant, const string parent);
        void traversal(const Node* current) const;
        int length(const Node* current, const string name) const;
        void remove(Node** current, const string name);
        string limitedBFS(Node* current, const int height) const;
    }; // class Tree
}; // namespace family