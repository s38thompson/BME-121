#include "binary-search-tree.h"
#include <iostream>
#include <queue>
using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;


BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;
    avlBalance = 0;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    // empty tree
    if (n == nullptr)
        return - 1;

    // recursive call until reach deepest leaf
    else
    {
        int ldepth = getNodeDepth(n->left);
        int rdepth = getNodeDepth(n->right);

        if (ldepth >= rdepth)
            return ldepth + 1;

        else
            return rdepth + 1;
    }
}

BinarySearchTree::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    queue<Node*> tree;

    if (root_)
        tree.push(root_);

    while(!tree.empty())
    {
        Node* cur = tree.front();
        tree.pop();

        if (cur->right)
            tree.push(cur->right);

        if (cur->left)
            tree.push(cur->left);

        delete cur;
    }
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    Node* cur = root_;

    if (cur->right == nullptr)
        return cur->val;

    else
    {
        while (cur->right != nullptr)
        {
            cur = cur->right;
        }

        return cur->val;
    }
}

DataType BinarySearchTree::min() const
{
    Node* cur = root_;

    if (cur->left == nullptr)
        return cur->val;

    else
    {
        while (cur->left != nullptr)
        {
            cur = cur->left;
        }

        return cur->val;
    }
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_);
}


void BinarySearchTree::print() const
{
    queue<Node*> tree;

    tree.push(root_);
    tree.push(NULL);

    while(!tree.empty())
    {
        Node* cur = tree.front();

        if(cur)
        {
            cout << cur->val << " ";

            while (tree.front() != NULL)
            {
                if (cur->left)
                    tree.push(cur->left);

                if (cur->right)
                    tree.push(cur->right);

                tree.pop();

                cur = tree.front();
            }

            tree.push(NULL);
        }
        tree.pop();
    }
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* cur = root_;

    // empty tree
    if (cur == nullptr)
        return false;

    // traversing tree until find correct node: exit as soon as reach node
    while (cur!= nullptr && cur->val != val)
    {

        if (val > cur->val)
            cur = cur->right;

        else
            cur = cur->left;
    }

    // checking value at correct node
    if (cur != nullptr && cur->val == val)
        return true;

    return false;
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    Node* node = new Node(val);

    // if value already exists in tree
    if (exists(val))
        return false;

    // inserting first node
    if (root_ == nullptr)
    {
        root_ = node;
        size_++;
        return true;
    }

    Node* cur = root_;

    // traverse until reach nullptr, then insert node
    while (cur != nullptr)
    {
        // val is less than root: insert to left
        if (val < cur->val)
        {
            // if at point of insertion
            if (cur->left == nullptr)
            {
                cur->left = node;
                size_++;
                break;
            }

            // move into left subtree
            else{
                cur = cur->left;
            }
        }

        // val is greater than root: inserted to right
        else
        {
            // if at point of insertion
            if (cur->right == nullptr)
            {
                cur->right = node;
                size_++;
                break;
            }

                // move into right subtree
            else
                cur = cur->right;
        }

    }

    return true;
}

Node* findPredecessor(Node* ptr)
{

}

bool BinarySearchTree::remove(DataType val)
{
    Node* cur = root_;
    Node* parent = nullptr;

    // value doesn't exist in tree (includes empty tree)
    if (!exists(val))
    {
        return false;
    }

    while (cur != nullptr)
    {
        // at node being deleted
        if (cur->val == val)
        {
            // Case 1: no children
            if (cur->right == nullptr && cur->left == nullptr)
            {
                // not root node
                if (cur != root_)
                {
                    if (parent->left == cur)
                    {
                        parent->left = nullptr;
                    }
                    else
                    {
                        parent->right = nullptr;
                    }
                }
                else
                {
                    cur = nullptr;
                }

                delete cur;
                size_--;
                break;
            }

            // Case 2: one child
            else if (cur->right == nullptr || cur->left == nullptr)
            {
                // determine if node has left or right child
                Node* child = (cur->left)? cur->left: cur->right;

                // not root node
                if (cur != root_)
                {
                    if (cur == parent->left)
                    {
                        parent->left = child;
                    }
                    else
                    {
                        parent->right = child;
                    }
                }

                // root node
                else
                {
                    root_ = child;
                }

                delete cur;
                size_--;
                break;
            }

            // Case 3: two children
            else
            {
                Node* deleted = cur;
                Node* predecessor = cur->left;
                Node* pre_parent = deleted;

                // no right subtree so current's left is predecessor
                if (predecessor->right == nullptr)
                {
                    deleted->val = predecessor->val;
                    deleted->left = predecessor->left;
                    size_--;
                    break;
                }

                // iterate until at leaf of current's left's right path
                while (predecessor->right != nullptr)
                {
                    pre_parent = predecessor;
                    predecessor = predecessor->right;
                }

                // store predecessor's value in node deleting
                deleted->val = predecessor->val;
                pre_parent->right = predecessor->left;
                size_--;
                break;
            }
        }

        // move into right subtree
        else if (val > cur->val)
        {
            parent = cur;
            cur = cur->right;
        }

        // move into left tree
        else
        {
            parent = cur;
            cur = cur->left;
        }
    }

    // empty tree: reset root pointer to null
    if (size_ == 0)
    {
        root_ = nullptr;
    }
    return true;
}