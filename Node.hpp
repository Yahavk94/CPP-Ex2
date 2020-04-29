#pragma once

#include <string>
#include <iostream>

/**
 * 04-2020
 * @author Yahav Karpel
 */

namespace family {
    class Node {
        friend class Tree;
    private:
        char gender;
        int height;
        std::string name;
        Node* left; // Mother
        Node* right; // Father
        Node(std::string name);
        ~Node();
    }; // class Node
}; // namespace family