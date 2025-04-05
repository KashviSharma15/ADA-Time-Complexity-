// Huffman Coding (Optimal Prefix Codes)
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char ch, int freq) : ch(ch), freq(freq), left(NULL), right(NULL) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) { return a->freq > b->freq; }
};

void printCodes(Node* root, string str) {
    if (!root) return;
    if (root->ch != '$') cout << root->ch << ": " << str << endl;
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void huffmanCoding(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto& p : freq)
        minHeap.push(new Node(p.first, p.second));

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }
    printCodes(minHeap.top(), "");
}

// Minimum Number of Coins
void minCoins(int N) {
    int coins[] = {2000, 500, 100, 50, 20, 10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);
    cout << "Coins used: ";

    for (int i = 0; i < n; i++) {
        while (N >= coins[i]) {
            cout << coins[i] << " ";
            N -= coins[i];
        }
    }
    cout << endl;
}

// Job Sequencing Problem
struct Job {
    int id, deadline, profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

void jobSequencing(Job jobs[], int n) {
    sort(jobs, jobs + n, compare);
    bool slot[n];
    slot[n] = {false};
    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                slot[j] = true;
                totalProfit += jobs[i].profit;
                cout << "Job " << jobs[i].id << " scheduled at time " << j+1 << endl;
                break;
            }
        }
    }
    cout << "Total Profit: " << totalProfit << endl;
}

int main() {
    cout << "--- Huffman Coding ---" << endl;
    unordered_map<char, int> freq = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    huffmanCoding(freq);

    cout << "\n--- Minimum Number of Coins ---" << endl;
    minCoins(93);

    cout << "\n--- Job Sequencing Problem ---" << endl;
    Job jobs[] = {{1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 3, 15}};
    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobSequencing(jobs, n);

    return 0;
}
