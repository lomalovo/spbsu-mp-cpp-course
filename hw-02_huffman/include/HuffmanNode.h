#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

class HuffmanNode {
public:
    char data;
    unsigned frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode() : data('\0'), frequency(0), left(nullptr), right(nullptr) {};
    HuffmanNode(char data, unsigned frequency) 
        : data(data), frequency(frequency), left(nullptr), right(nullptr) {};
};

struct CompareNodes {
    bool operator()(const std::shared_ptr<HuffmanNode>& lhs, const std::shared_ptr<HuffmanNode>& rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};


#endif // HUFFMAN_NODE_H
