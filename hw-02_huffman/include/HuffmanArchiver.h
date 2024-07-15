#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "HuffmanNode.h"

class HuffmanArchiver {
private:
    std::unordered_map<char, std::string> huffmanCodes;

    static std::shared_ptr<HuffmanNode> buildHuffmanTree(const std::unordered_map<char, long long int>& frequencies);
    void generateHuffmanCodes(const std::shared_ptr<HuffmanNode>& root, const std::string& code);

public:
    HuffmanArchiver();
    void compressFile(std::istream& inputFile, std::ostream& outputFile);
    void decompressFile(std::istream& inputFile, std::ostream& outputFile);

    std::size_t compressedFileSize;
    std::size_t unCompressedFileSize;
    std::size_t optionalSize;
};

#endif // HUFFMAN_ARCHIVER_H
