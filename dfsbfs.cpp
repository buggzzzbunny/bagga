#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int data) {
        this->data = data;
        this->left = this->right = NULL;
    }
};

// Parallel Breadth-First Search
void parallelBFS(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        #pragma omp parallel for
        for (int i = 0; i < q.size(); ++i) {
            Node* current = q.front();
            q.pop();
            cout << "BFS Visited node: " << current->data << endl;

            if (current->left != NULL)
                q.push(current->left);
            if (current->right != NULL)
                q.push(current->right);
        }
    }
}

// Parallel Depth-First Search
void parallelDFS(Node* node) {
    if (node == NULL)
        return;

    cout << "DFS Visited node: " << node->data << endl;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelDFS(node->left);
        
        #pragma omp section
        parallelDFS(node->right);
    }
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Parallel Breadth-First Search:" << endl;
    parallelBFS(root);

    cout << "\nParallel Depth-First Search:" << endl;
    parallelDFS(root);

    return 0;
}
