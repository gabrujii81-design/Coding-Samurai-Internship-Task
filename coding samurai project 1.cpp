#include <bits/stdc++.h>
using namespace std;

/* Huffman Tree Node */
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

/* Comparator for min heap */
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

/* Generate Huffman Codes */
void generateCodes(Node* root, string code,
                   unordered_map<char, string> &huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right)
        huffmanCode[root->ch] = code;

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

int main() {
    ifstream fin("input.txt");
    string text, line;

    while (getline(fin, line))
        text += line;

    fin.close();

    /* Step 1: Frequency count */
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    /* Step 2: Build Min Heap */
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    /* Step 3: Build Huffman Tree */
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();

    /* Step 4: Generate Codes */
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    /* Step 5: Encode */
    string encodedText = "";
    for (char ch : text)
        encodedText += huffmanCode[ch];

    ofstream fout("compressed.txt");
    fout << encodedText;
    fout.close();

    /* Output */
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode)
        cout << pair.first << " : " << pair.second << endl;

    cout << "\nOriginal Size (bits): " << text.size() * 8 << endl;
    cout << "Compressed Size (bits): " << encodedText.size() << endl;

    return 0;
}
