# Huffman-Coding

It is a data compression algorithm. This algorithm is used everywhere like file compression, image compression, and network protocols.
The main idea behind Huffman coding is to assign shorter codes to more frequently occurring symbols and vice versa. This results in a more efficient representation of data, reducing the overall size of the original file.

Implementation of Huffman-Coding is done in 5 steps:-
1) Frequency calculation - Calculate the frequency of each character and store it in an unordered_map<char, int>.
2) Constructing a Huffman tree - Each node consists of a character and its frequency and also the address of its left and right child.
3) Assigning Binary Codes - Assigning Binary code to each character on the basis of adding a character with '0' in the path if it lies in the left child and '1' if it lies in the right child. This <char, string> pair is stored in an unordered_map. Here, the string is a string of Binary code.
4) Encoding - On the basis of Unordered_map<char, string>, each character of string is replaced with its corresponding binary code.
5) Decoding - Before Decoding, constructed an unordere_map<string, char> using preivious unordered map of <char, string> type. Then replacing each string with the corresponding character.
