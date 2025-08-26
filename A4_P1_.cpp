#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long value;
    Node* left;
    Node* right;
    Node(long long val) : value(val), left(nullptr), right(nullptr) {}
};


class BST {
private:
    Node* root;

    
    void insert(long long value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* curr = root;
        while (true) {
            if (value < curr->value) {
                if (!curr->left) {
                    curr->left = new Node(value);
                    break;
                }
                curr = curr->left;
            } else if (value > curr->value) {
                if (!curr->right) {
                    curr->right = new Node(value);
                    break;
                }
                curr = curr->right;
            } else {
                break;
            }
        }
    }

    void inorder(Node* node, vector<long long>& result) {
        if (!node) return;
        inorder(node->left, result);
        result.push_back(node->value);
        inorder(node->right, result);
    }

    void preorder(Node* node, vector<long long>& result) {
        if (!node) return;
        result.push_back(node->value);
        preorder(node->left, result);
        preorder(node->right, result);
    }

    void postorder(Node* node, vector<long long>& result) {
        if (!node) return;
        postorder(node->left, result);
        postorder(node->right, result);
        result.push_back(node->value);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    void insertValue(long long value) { insert(value); }

    vector<long long> getInorder() {
        vector<long long> result;
        inorder(root, result);
        return result;
    }
    vector<long long> getPreorder() {
        vector<long long> result;
        preorder(root, result);
        return result;
    }
    vector<long long> getPostorder() {
        vector<long long> result;
        postorder(root, result);
        return result;
    }

    ~BST() { clear(root); }
};

void printVector(const vector<long long>& vec) {
    if (vec.empty()) {
        cout << endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    BST bst;
    long long value;

    while (cin >> value) {
        bst.insertValue(value);
    }

    printVector(bst.getInorder());
    printVector(bst.getPreorder());
    printVector(bst.getPostorder());

    cout.flush();

    return 0;
}
