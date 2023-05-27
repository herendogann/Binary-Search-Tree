#ifndef ASS4_PRIMARYTREE_H
#define ASS4_PRIMARYTREE_H
#include "SecondaryTree.h"

// creating node struct for primary tree
struct PrimaryNode {
    string name;
    PrimaryNode *left;
    PrimaryNode *right;
    SecondaryTree secondaryTree;
    SecondaryTree2 secondaryTree2;
    PrimaryNode(string Name){
        name = Name;
        left = nullptr;
        right = nullptr;
    }
};

// creating class for our primary tree which is a BST
class PrimaryTree{
public:
    PrimaryTree() : root(nullptr){}
    void insert(string name){root = insert(root, name);}
    bool remove(string name) {return remove(root, name);}
    PrimaryNode *search(string name) {return search(root, name);}
    bool isEmpty(){ if (root == nullptr) return true; else return false;}

    // function to print all nodes and their secondary trees in level order for 1st part
    void printLevelByLevel1(ofstream *output) {
        if (root == nullptr) return;
        queue < PrimaryNode * > q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                PrimaryNode *node = q.front();
                q.pop();
                *output << "\"" << node->name << "\":";
                if (node->secondaryTree.isEmpty()) {
                    *output << "{}\n";
                } else {
                    *output << "\n";
                    node->secondaryTree.printLevelByLevel(output);
                }
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
    }

    // same function for 2nd part
    void printLevelByLevel2(ofstream *output2) {
        if (root == nullptr) return;
        queue<PrimaryNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                PrimaryNode* node = q.front();
                q.pop();
                *output2 << "\"" <<node->name << "\":";
                if (node->secondaryTree2.isEmpty()){
                    *output2 << "{}\n";
                } else {
                    *output2 << "\n";
                    node->secondaryTree2.printLevelByLevel(output2);
                }
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
    }

private:

    PrimaryNode* insert(PrimaryNode* node, string name) {
        if (node == nullptr) {
            return new PrimaryNode(name);
        }
        if (name < node->name) {
            node->left = insert(node->left, name);
        } else if (name > node->name){
            node->right = insert(node->right, name);
        }
        return node;
    }

    bool remove(PrimaryNode *& node, string name) {
        if (node == nullptr) {
            return false;
        }
        // if the given name is the name of current node
        if (node->name == name) {
            // if node has no children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            // if node has one child
            else if (node->left == nullptr) {
                PrimaryNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                PrimaryNode* temp = node;
                node = node->left;
                delete temp;
            }
            // if node has two children
            else {
                PrimaryNode* temp = FindMin(node->right);
                node->name = temp->name;
                remove(node->right, temp->name);
            }
            return true;
        }
        // if the given name less than node's name, go left; else, go right
        if (name < node->name) {
            return remove(node->left, name);
        } else {
            return remove(node->right, name);
        }
    }
    // function to find the node which has minimum key value
    PrimaryNode* FindMin(PrimaryNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    // function to find a node with a given name
    PrimaryNode *search(PrimaryNode* node, string name) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->name == name) {
            return node;
        }
        if (name < node->name) {
            return search(node->left, name);
        } else {
            return search(node->right, name);
        }
    }


    PrimaryNode *root;
};

#endif //ASS4_PRIMARYTREE_H
