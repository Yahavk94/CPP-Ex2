/**
 * 04-2020
 * @author Yahav Karpel
 */

#pragma once

#include "Node.hpp"
#include "Utils.hpp"

namespace family {
    class Tree {
    public:
        /**
         * A constructor.
         */
        Tree(std::string name);

        /**
         * A destructor.
         */
        ~Tree();

        /**
         * Given any name refers to a mother, this method returns the tree after adding
         * her name as the left node of the given descendant.
         * NOTE that an exception would be thrown in case of descendant's non-existence, an empty 
         * string, an empty tree or mother's existence.
         */
        Tree& addMother(const std::string descendant, const std::string parent);

        /**
         * Given any name refers to a father, this method returns the tree after adding
         * his name as the right node of the given descendant.
         * NOTE that an exception would be thrown in case of descendant's non-existence, an empty
         * string, an empty tree or father's existence.
         */
        Tree& addFather(const std::string descendant, const std::string parent);

        /**
         * This method displays the tree in a human-friendly format.
         */
        void display() const;

        /**
         * This method returns the relation between the root and any given name.
         * NOTE that an exception would be thrown in case of an empty string or an empty tree.
         */
        const std::string relation(const std::string name) const;

        /**
         * This method finds and returns the name of any given relation.
         * NOTE that an exception would be thrown in case of an empty string, an empty tree or when 
         * the tree cannot handle the given relation.
         */
        const std::string find(const std::string relation) const;

        /**
         * Given any name, this method returns the tree after removing it and 
         * it's descendants.
         * NOTE that an exception would be thrown in case of an empty string or an empty tree.
         */
        Tree& remove(const std::string name);

    private:
        Node* root;
        void destroy(Node** current);
        void insert(Node** current, const std::string descendant, const std::string parent);
        void traversal(const Node* current) const;
        const int length(const Node* current, const std::string name) const;
        void remove(Node** current, const std::string name);
        const std::string limitedBFS(Node* current, const int height) const;
    }; // class Tree
}; // namespace family