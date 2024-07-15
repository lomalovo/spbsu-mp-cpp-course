#include <iostream>
#include <fstream>
#include <stdexcept>
#include "HuffmanArchiver.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 5) {
            throw std::invalid_argument("Недостаточно аргументов.");
        }

        bool compress = false;
        bool decompress = false;
        std::string inputFile;
        std::string outputFile;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-c") {
                compress = true;
            } else if (arg == "-u") {
                decompress = true;
            } else if (arg == "-f" || arg == "--file") {
                if (i + 1 < argc) {
                    inputFile = argv[++i];
                } else {
                    throw std::invalid_argument("Вы не указали название входного файла.");
                }
            } else if (arg == "-o" || arg == "--output") {
                if (i + 1 < argc) {
                    outputFile = argv[++i];
                } else {
                    throw std::invalid_argument("Вы не указали название файла для вывода.");
                }
            }
        }

        if (!(compress ^ decompress)) {
            throw std::invalid_argument("Вы не выбрали режим или выбрали сразу оба.");
        }

        HuffmanArchiver archiver;

        if (compress) {
            std::ifstream inFile(inputFile, std::ios::binary);
            if (!inFile.is_open()) {
                throw std::invalid_argument("Не удалось открыть входной файл.");
            }
            std::ofstream outFile(outputFile, std::ios::binary);
            if (!outFile.is_open()) {
                throw std::invalid_argument("Не удалось открыть файл для вывода.");
            }

            archiver.compressFile(inFile, outFile);
            std::cout << archiver.unCompressedFileSize << std::endl;
            std::cout << archiver.compressedFileSize << std::endl;
            std::cout << archiver.optionalSize << std::endl;
        } else {
            std::ifstream inFile(inputFile, std::ios::binary);
            if (!inFile.is_open()) {
                throw std::invalid_argument("Не удалось открыть входной файл.");
            }
            std::ofstream outFile(outputFile, std::ios::binary);
            if (!outFile.is_open()) {
                throw std::invalid_argument("Не удалось открыть файл для вывода.");
            }

            archiver.decompressFile(inFile, outFile);
            std::cout << archiver.compressedFileSize << std::endl;
            std::cout << archiver.unCompressedFileSize << std::endl;
            std::cout << archiver.optionalSize << std::endl;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}
