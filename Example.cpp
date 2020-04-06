class Node {
    friend class tree;
private:
    Node *lchild,*rchild;
    int data;
public:
    Node(int x) {
        data = x;
        lchild = rchild = nullptr;
    }
};

class tree {
public:
    tree() { root = nullptr; }
    bool insert(int item) {return insert(item,root);};
    void inorder() const {inorder(root);};

protected:
    Node* root;
    void inorder(const Node* curr) const;
    bool insert(int item, Node* curr);
};

bool tree::insert(int item, Node *currNode) {
    if (root == nullptr) {
        root = new Node(item);
        return true;
    }

    else if (item < currNode->data) {
        if (currNode->lchild == nullptr) {
            currNode->lchild = new Node(item);
            return true;
        }

        else {
            return insert(item, currNode->lchild);
        }
    }

    else if (item > currNode->data) {
        if (currNode->rchild == nullptr) {
            currNode->rchild = new Node(item);
            return true;
        }

        else {
            return insert(item, currNode->rchild);
        }
    }
    else // item == currNode->data
        return false; // duplicate; do not insert
}