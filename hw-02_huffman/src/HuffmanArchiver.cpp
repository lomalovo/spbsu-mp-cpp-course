#include "HuffmanArchiver.h"
#include "HuffmanNode.h"
#include "binManip.h"
#include <unordered_map>
#include <queue>
#include <sstream>
#include <memory>


HuffmanArchiver::HuffmanArchiver() : compressedFileSize(0), unCompressedFileSize(0), optionalSize(0) {}

std::shared_ptr<HuffmanNode> HuffmanArchiver::buildHuffmanTree(const std::unordered_map<char, long long int>& frequencies) {
    std::priority_queue<
        std::shared_ptr<HuffmanNode>,
        std::vector<std::shared_ptr<HuffmanNode>>,
        CompareNodes
    > pq;

    for (const auto& pair : frequencies) {
        pq.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
    }

    if (pq.empty()) {
        return nullptr;
    }

    while (pq.size() > 1) {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();
        auto newNode = std::make_shared<HuffmanNode>('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    auto root = pq.top();
    pq.pop();
    return root;
}

void HuffmanArchiver::generateHuffmanCodes(const std::shared_ptr<HuffmanNode>& root, const std::string& code) {
    if (root == nullptr)
        return;
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0");
    generateHuffmanCodes(root->right, code + "1");
}

void HuffmanArchiver::compressFile(std::istream& inFile, std::ostream& outFile) {

    std::unordered_map<char, long long int> frequencies;
    char ch;
    while (inFile.get(ch)) {
        frequencies[ch]++;
        unCompressedFileSize++;
    }

    auto root = buildHuffmanTree(frequencies);

    if (frequencies.size() == 1) {
        generateHuffmanCodes(root, "0");
    } else {
        generateHuffmanCodes(root, "");
    }

    inFile.clear();
    inFile.seekg(0);


    // Таблицу храним таким образом: размер таблицы, набор {char, размер кода, код},
    // а потом количество битов в последнем байте, которые нам нужны
    int tableSize = frequencies.size();
    write_int(outFile, tableSize);
    optionalSize += sizeof(int);

    long long int count = 0;
    for (const auto& pair : frequencies) {
        int len = huffmanCodes[pair.first].length();
        count += len * pair.second;
        write_char(outFile, pair.first);
        write_int(outFile, len);
        for (int i = 0; i < len; ++i){
            write_char(outFile, huffmanCodes[pair.first][i]);
        }
        optionalSize += sizeof(char) + sizeof(int) + sizeof(char) * len;
    }


    char diff = static_cast<char>(count % 8);
    compressedFileSize = count / 8 + (diff != 0);
    write_char(outFile, diff);
    optionalSize += sizeof(char);

    char byte = 0;
    char bitCount = 0;

    while (inFile.get(ch)) {
        std::string code = huffmanCodes[ch];
        for (char bit : code) {
            if (bit == '1') {
                byte |= 1 << (7 - bitCount);
            }
            ++bitCount;

            if (bitCount == 8) {
                write_char(outFile, byte);
                byte = 0;
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0) {
        write_char(outFile, byte);
    }
}

void buildHuffmanTreeFromCodes(char ch, const std::string& code, const std::shared_ptr<HuffmanNode>& root) {
    if (root == nullptr) {
        throw std::invalid_argument("Корень - это nullptr");
    }

    std::shared_ptr<HuffmanNode> currentRoot = root;
    for (char bit : code) {
        if (bit == '0') {
            if (currentRoot->left == nullptr) {
                currentRoot->left = std::make_shared<HuffmanNode>();
            }
            currentRoot = currentRoot->left;
        } else if (bit == '1') {
            if (currentRoot->right == nullptr) {
                currentRoot->right = std::make_shared<HuffmanNode>();
            }
            currentRoot = currentRoot->right;
        }
    }

    currentRoot->data = ch;
}

void HuffmanArchiver::decompressFile(std::istream& inFile, std::ostream& outFile) {

    int tableSize;
    read_int(inFile, tableSize);
    optionalSize += sizeof(int);

    std::string code;

    for (int i = 0; i < tableSize; ++i) {
        char ch;
        int len;
        char codeCh;
        read_char(inFile, ch);
        read_int(inFile, len);
        code = "";
        for (int j = 0; j < len; ++j) {
            read_char(inFile, codeCh);
            code += codeCh;
        }

        huffmanCodes[ch] = code;
        optionalSize += sizeof(char) + sizeof(int) + sizeof(char) * len;
    }


    char diff;
    read_char(inFile, diff);
    optionalSize += sizeof(char);

    auto root = std::make_shared<HuffmanNode>();
    // std::cout << "Codes after uncompr" << std::endl;
    for (const auto& codes : huffmanCodes) {
        buildHuffmanTreeFromCodes(codes.first, codes.second, root);
    }

    if (!root) {
        throw std::runtime_error("Что то пошло не так с построением");
    }

    auto current = root;
    char bit;
    read_char(inFile, bit);
    while (inFile.good()) {
        compressedFileSize += sizeof(char);
        for (int i = 7; i >= 0; --i) {
            if (inFile.peek() == EOF && ((7 - i) >= static_cast<int>(diff)) && (diff > 0)) {
                break;
            }

            unsigned char bitValue = (bit >> i) & 1;
            current = bitValue == 1 ? current->right : current->left;

            if (current == nullptr) {
                throw std::runtime_error("Что-то не так");
            }

            if (current->left == nullptr && current->right == nullptr) {
                write_char(outFile, current->data);
                unCompressedFileSize += sizeof(char);
                current = root;
            }
        }
        read_char(inFile, bit);
    }
}
