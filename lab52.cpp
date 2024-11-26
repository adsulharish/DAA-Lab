#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }

    Node(Node *l, Node *r)
    {
        ch = '\0';
        freq = l->freq + r->freq;
        left = l;
        right = r;
    }

    bool operator>(const Node &other) const
    {
        return freq > other.freq;
    }
};

void generateCodes(Node *root, const std::string &code, std::unordered_map<char, std::string> &huffmanCodes)
{
    if (root == nullptr)
        return;

    if (root->ch != '\0')
        huffmanCodes[root->ch] = "1"+code;

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

void huffmanCompress(const std::string &input, std::unordered_map<char, std::string> &huffmanCodes, std::string &compressedOutput)
{
    std::unordered_map<char, int> freqMap;

    for (int i = 0; i < input.size(); i++)
    {
        freqMap[input[i]]++;
    }

    std::priority_queue<Node *, std::vector<Node *>, std::greater<Node *>> minHeap;

    for (const auto &entry : freqMap)
    {
        minHeap.push(new Node(entry.first, entry.second));
    }

    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();
        minHeap.push(new Node(left, right));
    }

    Node *root = minHeap.top();

    generateCodes(root, "", huffmanCodes);

    for (int i = 0; i < input.size(); i++)
    {
        compressedOutput += huffmanCodes[input[i]];
    }
}

double calculateCompressionRatio(const std::string &originalText, const std::string &compressedText)
{
    double originalSize = originalText.size() * 8; // in bits
    double compressedSize = compressedText.size(); // in bits
    return compressedSize / originalSize;
}

std::string readTextFromFile(const std::string &filePath)
{
    std::ifstream inputFile(filePath);
    if (!inputFile)
    {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return "";
    }

    std::string line;
    std::string content;
    while (std::getline(inputFile, line))
    {
        content += line + "\n";
    }

    inputFile.close();
    return content;
}

int main()
{
    // Modify the file path as needed
    std::string filePath = "stock.html"; // Path to your text file
    std::string input = readTextFromFile(filePath);

    if (input.empty())
    {
        std::cerr << "No content found in the file!" << std::endl;
        return 1;
    }

    std::unordered_map<char, std::string> huffmanCodes;
    std::string compressedOutput;

    huffmanCompress(input, huffmanCodes, compressedOutput);

    std::cout << "Huffman Codes:" << std::endl;
    for (const auto &entry : huffmanCodes)
    {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    double compressionRatio = calculateCompressionRatio(input, compressedOutput);
    std::cout << "Compression Ratio: " << compressionRatio << std::endl;

    return 0;
}
