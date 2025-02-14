#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// Node structure for Huffman Tree
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;

    // Constructor
    HuffmanNode(char ch, int freq) {
        character = ch;
        frequency = freq;
        left = right = nullptr;
    }
};

// Custom comparator for priority queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency; // Min-heap based on frequency
    }
};

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(string chars, vector<int> freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // Create leaf nodes for each character and push to minHeap
    for (int i = 0; i < chars.length(); i++) {
        minHeap.push(new HuffmanNode(chars[i], freq[i]));
    }

    // Build the Huffman tree
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top(); // Root node
}

// Function to generate and print Huffman codes (Preorder traversal)
void generateHuffmanCodes(HuffmanNode* root, string code) {
    if (!root) return;

    // Print the code if it's a leaf node (character node)
    if (root->character != '$') {
        cout << root->character << ": " << code << endl;
    }

    // Recursive traversal (Preorder: Root → Left → Right)
    generateHuffmanCodes(root->left, code + "0");
    generateHuffmanCodes(root->right, code + "1");
}

// Driver function
int main() {
    string characters = "abcdef";
    vector<int> frequencies = {5, 9, 12, 13, 16, 45};

    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(characters, frequencies);

    // Print Huffman Codes in Preorder Traversal
    cout << "Huffman Codes (Preorder Traversal):" << endl;
    generateHuffmanCodes(root, "");

    return 0;
}
