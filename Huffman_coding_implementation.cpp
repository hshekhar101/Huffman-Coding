/* Copyright 2023, Himanshu Shekhar, All rights reserved. */

#include <bits/stdc++.h>
using namespace std;

// creating node for huffman tree class
class Node
{
public:
    char ch;
    int count;
    Node *left;
    Node *right;

    // creating our own constructor
    Node(char ch, int count)
    {
        this->ch = ch;
        this->count = count;
        left = NULL;
        right = NULL;
    }

    // This will return true if count of current node is greater than count of other node.
    // This will be helpful while constructing priority queue on the basis of count.
    bool operator<(const Node &other) const
    {
        return count > other.count;
    }
};

// This function is constructing huffman tree and will return the root of the huffman tree.
Node *buildHuffmanTree(unordered_map<char, int> &frequency)
{
    priority_queue<Node *> PQ; // This is the min-heap priority queue on the basis of count of node.
    for (auto x : frequency)
    {
        char ch = x.first;
        char count = x.second;
        Node *newnode = new Node(ch, count);
        PQ.push(newnode);
    }

    while (PQ.size() > 1)
    {
        Node *leftchild = PQ.top();
        PQ.pop();
        Node *rightchild = PQ.top();
        PQ.pop();
        Node *tempRoot = new Node('*', leftchild->count + rightchild->count);
        tempRoot->left = leftchild;
        tempRoot->right = rightchild;
        PQ.push(tempRoot);
    }
    return PQ.top();
}

// constructing Encoding Helper
void BinaryCodeGeneratorHelper(Node *node, string binaryCode, unordered_map<char, string> &huffmanCode)
{
    if (node == NULL)
    {
        return;
    }
    if (node->left == NULL && node->right == NULL)
    {
        huffmanCode[node->ch] = binaryCode;
        return;
    }
    BinaryCodeGeneratorHelper(node->left, binaryCode + "0", huffmanCode);
    BinaryCodeGeneratorHelper(node->right, binaryCode + "1", huffmanCode);
}

// constructing and returning the mapping of each character with their binary code. Binary code is stored in the form of string.
unordered_map<char, string> BinaryCodeGenerator(Node *root)
{
    unordered_map<char, string> huffmanCode;
    if (root == NULL)
    {
        return huffmanCode; // returning empty unorderedmap
    }
    string binaryCode;
    BinaryCodeGeneratorHelper(root, binaryCode, huffmanCode);
    return huffmanCode;
}

// Encoding the given string in binary form and returning the binary form of string
string Encoding(string &str, unordered_map<char, string> &huffmanCode)
{
    string answer = "";
    for (int i = 0; i < str.length(); i++)
    {
        answer += huffmanCode[str[i]];
    }
    return answer;
}

// constructing an unordered map of <string, char> of huffmancode
unordered_map<string, char> reversing_huffmanCode(unordered_map<char, string> huffmanCode)
{
    unordered_map<string, char> answer;
    for (auto x : huffmanCode)
    {
        char ch = x.first;
        string str = x.second;
        answer[str] = ch;
    }
    return answer;
}

// function which will decode the encodedBinaryString and return the original string
string Decoding(string encodedString, unordered_map<string, char> complementOf_huffmanCode)
{
    string answer = "";
    string str = "";
    for (int i = 0; i < encodedString.length(); i++)
    {
        str += encodedString[i];
        if (complementOf_huffmanCode.count(str) > 0)
        {
            answer += complementOf_huffmanCode[str];
            str = "";
        }
    }
    return answer;
}

int main()
{
    string str;
    cin >> str;
    unordered_map<char, int> frequency; // character is the key
    for (int i = 0; i < str.length(); i++)
    {
        frequency[str[i]]++;
    }
    Node *root = buildHuffmanTree(frequency);
    unordered_map<char, string> huffmanCode = BinaryCodeGenerator(root);

    string encodedString = Encoding(str, huffmanCode);
    cout << "Encoded/Compressed form of string : " << encodedString << endl;

    unordered_map<string, char> complementOf_huffmanCode = reversing_huffmanCode(huffmanCode);
    string decodedString = Decoding(encodedString, complementOf_huffmanCode);
    cout << "Decoded/Uncompressed form of string : " << decodedString << endl;
    return 0;
}