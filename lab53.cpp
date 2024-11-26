#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// A Huffman tree node
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    
    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
    Node(char cha,int f , Node* l1,Node* r1){
        ch = cha;
        freq = f;
        left = l1;
        right = r1;
    }
};

// Comparison object for the min-heap
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Function to store the Huffman codes in a map
void storeCodes(Node* root, string str, unordered_map<char, string> &huffmanCode) {
    if (!root) return;

    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    storeCodes(root->left, str + "0", huffmanCode);
    storeCodes(root->right, str + "1", huffmanCode);
}

// Function to build the Huffman tree
Node* buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (auto pair : freq) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() != 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        int sum = left->freq + right->freq;
        minHeap.push(new Node('\0', sum, left, right));
    }

    return minHeap.top();
}

// Function to encode a string using Huffman coding
string encode(string text, unordered_map<char, string> &huffmanCode) {
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }
    return encodedStr;
}

// Function to calculate compression ratio
double calculateCompressionRatio(string original, string compressed) {
    return (double)compressed.size() / (original.size() * 8);
}

// Main function to perform Huffman Coding
void huffmanCoding(string text) {
    Node* root = buildHuffmanTree(text);

    unordered_map<char, string> huffmanCode;
    storeCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    string compressedStr = encode(text, huffmanCode);
    double compressionRatio = calculateCompressionRatio(text, compressedStr);

    cout << "\nOriginal string: " << text << '\n';
    cout << "Compressed string: " << compressedStr << '\n';
    cout << "Compression Ratio: " << compressionRatio << "\n\n";
}

int main() {
    // Test cases
    string testCases[] = {
        "hello world",
        "aaaaaaabbbbbcccdde",
        "this is a test for huffman coding",
        "abcabcabcabcabcabcabcabc",
        "mississippi"
    };

    for (int i = 0; i < 5; i++) {
        cout << "Test Case " << i + 1 << ":\n";
        huffmanCoding(testCases[i]);
    }

    return 0;
}
