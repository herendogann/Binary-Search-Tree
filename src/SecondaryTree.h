#ifndef ASS4_SECONDARYTREE_H
#define ASS4_SECONDARYTREE_H
#include <queue>

// secondary node struct for secondary tree (1st part - AVL Tree)
struct SecondaryNode {
    string category;
    string name;
    int price;
    int height;
    SecondaryNode *left;
    SecondaryNode *right;
    SecondaryNode(string Category, string Name, int Price){
        category = Category;
        name = Name;
        price = Price;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
    void updatePrice(int val){price = val;}
};

// creating a class for colors of nodes in LLRB Tree - 2nd part
enum class Color { RED, BLACK };

// secondary node struct for secondary tree (2nd part - LLRB Tree)
struct SecondaryNode2 {
    string category;
    string name;
    int price;
    Color color;
    SecondaryNode2 *left;
    SecondaryNode2 *right;
    SecondaryNode2(string Category, string Name, int Price){
        category = Category;
        name = Name;
        price = Price;
        color = Color::RED;
        left = nullptr;
        right = nullptr;
    }
    void updatePrice(int val){price = val;}
};

// creating class for our secondary tree in part-1 which is an AVL Tree
class SecondaryTree{
public:
    SecondaryTree() : root(nullptr){}
    void insert(string category, string name, int price){root = insert(root, category, name, price);}
    void remove(string name){root = remove(root, name);}
    bool isEmpty(){ if (root == nullptr) return true; else return false;}
    SecondaryNode *search(string name) {return search(root, name);}

    // a function to print nodes of a secondary tree in level order
    void printLevelByLevel(ofstream *output) {
        queue<SecondaryNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            *output << "\t";
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                SecondaryNode* node = queue.front();
                queue.pop();
                *output << "\"" << node->name << "\":\"" << node->price << "\",";
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            *output << "\n";
        }
    }
private:
    int getHeight(SecondaryNode* node) {
        return node ? node->height : 0;
    }
    int getBalance(SecondaryNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    SecondaryNode* rightRotate(SecondaryNode* y) {
        SecondaryNode* x = y->left;
        SecondaryNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }
    SecondaryNode* leftRotate(SecondaryNode* x) {
        SecondaryNode* y = x->right;
        SecondaryNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    SecondaryNode* insert(SecondaryNode* node, string category, string name, int price) {
        if (node == nullptr) {
            return new SecondaryNode(category,name,price);
        }
        if (name < node->name) {
            node->left = insert(node->left, category, name, price);
        } else {
            node->right = insert(node->right, category, name, price);
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        // checking if the node is unbalanced
        int balance = getBalance(node);
        // if it is unbalanced, we must make some rotations
        // left-left
        if (balance > 1 && name < node->left->name) {
            return rightRotate(node);
        }
        // right-right
        if (balance < -1 && name > node->right->name) {
            return leftRotate(node);
        }
        // left-right
        if (balance > 1 && name > node->left->name) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // right-left
        if (balance < -1 && name < node->right->name) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    SecondaryNode* remove(SecondaryNode* node, string name) {
        if (node == nullptr) {
            return nullptr;
        }
        if (name < node->name) {
            node->left = remove(node->left, name);
        } else if (name > node->name) {
            node->right = remove(node->right, name);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                SecondaryNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                SecondaryNode* temp = GetMinValueNode(node->right);
                node->name = temp->name;
                node->right = remove(node->right, temp->name);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        // checking if the node is unbalanced
        int balance = getBalance(node);
        // left-left
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        // right-right
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // left-right
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        // right-left
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    // function to get the node with minimum value
    SecondaryNode* GetMinValueNode(SecondaryNode* node) {
        SecondaryNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    // function to find a node
    SecondaryNode *search(SecondaryNode* node, string name) {
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
    SecondaryNode *root;
};

// creating class for our secondary tree in part-2 which is an LLRB Tree
class SecondaryTree2{
public:
    SecondaryTree2() : root(nullptr){}
    bool isEmpty(){ if (root == nullptr) return true; else return false;}
    void insert(string category, string name, int price){root = insert(root, category, name, price);}
    void remove(string name){if (root == nullptr){return;} else {root->color = Color::BLACK;} root = remove(root,name);}
    SecondaryNode2 *search(string name){return search(root, name);}

    // a function to print nodes of a secondary tree in level order
    void printLevelByLevel(ofstream *output2) {
        queue<SecondaryNode2*> queue;
        queue.push(root);
        while (!queue.empty()) {
            *output2 << "\t";
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                SecondaryNode2* node = queue.front();
                queue.pop();
                *output2 << "\"" << node->name << "\":\"" << node->price << "\",";
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            *output2 << "\n";
        }
    }
private:
    // function to insert a node in our LLRBT
    SecondaryNode2 *insert(SecondaryNode2 *node, string category, string name, int price){
        if (node == nullptr){
            return new SecondaryNode2(category,name,price);
        }
        if (name < node->name){
            node->left = insert(node->left, category,name,price);
        } else if (name > node->name){
            node->right = insert(node->right, category,name,price);
        } else {}
        return balance(node);
    }
    // function to remove a node from our LLRBT
    SecondaryNode2 *remove(SecondaryNode2* node, string name){
        if (node == nullptr) return nullptr;
        if (name < node->name) {
            if (node->left != nullptr && !isRed(node->left) && !isRed(node->left->left)) {
                node = rotateRight(node);
            }
            node->left = remove(node->left, name);
        } else {
            if (isRed(node->left)) {
                node = rotateRight(node);
            }
            if (name == node->name && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            if (node->right != nullptr && !isRed(node->right) && !isRed(node->right->left)) {
                node = rotateLeft(node);
            }
            if (name == node->name) {
                SecondaryNode2* min_node = findMin(node->right);
                node->name = min_node->name;
                node->right = removeMin(node->right);
            } else {
                node->right = remove(node->right, name);
            }
        }
        return balance(node);
    }
    // function to find a node
    SecondaryNode2 *search(SecondaryNode2* node, string name){
        if (node == nullptr){
            return nullptr;
        }
        if (name < node->name){
            return search(node->left, name);
        } else if (name > node->name){
            return search(node->right, name);
        } else {
            return node;
        }
    }
    // function to check red-black balance
    SecondaryNode2 *balance(SecondaryNode2* node){
        if (isRed(node->right)){
            node = rotateLeft(node);
        }
        if (node->left != nullptr && isRed(node->left) && isRed(node->left->left)){
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right)){
            flipColors(node);
        }
        return node;
    }
    // function to change two nodes' colors with each other
    void flipColors(SecondaryNode2* node) {
        node->color = changeColor(node->color);
        node->left->color = changeColor(node->left->color);
        node->right->color = changeColor(node->right->color);
    }
    SecondaryNode2* findMin(SecondaryNode2* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    SecondaryNode2* removeMin(SecondaryNode2* node) {
        if (node->left == nullptr) {
            delete node;
            return nullptr;
        }
        if (node->left != nullptr && isRed(node->left) && !isRed(node->left->left)) {
            node = rotateRight(node);
        }
        node->left = removeMin(node->left);
        return balance(node);
    }

    SecondaryNode2* rotateLeft(SecondaryNode2* node) {
        SecondaryNode2* x = node->right;
        node->right = x->left;
        x->left = node;
        x->color = node->color;
        node->color = Color::RED;
        return x;
    }
    SecondaryNode2* rotateRight(SecondaryNode2* node) {
        SecondaryNode2* x = node->left;
        node->left = x->right;
        x->right = node;
        x->color = node->color;
        node->color = Color::RED;
        return x;
    }
    Color changeColor(Color color) {
        return color == Color::RED ? Color::BLACK : Color::RED;
    }
    bool isRed(SecondaryNode2* node) {
        if (node == nullptr){
            return false;
        }
        return node->color == Color::RED;
    }

    SecondaryNode2 *root;

};

#endif //ASS4_SECONDARYTREE_H
