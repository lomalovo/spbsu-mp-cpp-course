#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <random>
#include "doctest.h"
#include "HuffmanArchiver.h"

bool CompareFiles (std::ifstream& ifs1, std::ifstream& ifs2) {
    unsigned char ch1, ch2;
    bool flag1, flag2;
    flag1 = bool(ifs1.read(reinterpret_cast<char*>(&ch1), sizeof(ch1)));
    flag2 = bool(ifs2.read(reinterpret_cast<char*>(&ch2), sizeof(ch2)));
    while (flag1 && flag2) {
        if (ch1 != ch2) {
            return false;
        }
        flag1 = bool(ifs1.read(reinterpret_cast<char*>(&ch1), sizeof(ch1)));
        flag2 = bool(ifs2.read(reinterpret_cast<char*>(&ch2), sizeof(ch2)));
    }
    return !(flag1 ^ flag2);
}

bool test_file(std::ifstream& ifs) {
    std::ofstream ofs("sample/tmp/encoded.bin", std::ios::binary);
    HuffmanArchiver arch1;
    arch1.compressFile(ifs, ofs);
    ofs.close();

    std::ifstream ifs1("sample/tmp/encoded.bin", std::ios::binary);
    std::ofstream ofs1("sample/tmp/decoded.txt", std::ios::binary);
    arch1.decompressFile(ifs1, ofs1);
    ifs1.close();
    ofs1.close();

    std::ifstream ifs2("sample/tmp/decoded.txt", std::ios::binary);

    return CompareFiles(ifs, ifs2);
}


TEST_CASE("test README.md") {
    std::ifstream ifs("README.md", std::ios::binary);
    REQUIRE(ifs.is_open());
    CHECK(test_file(ifs));
}

TEST_CASE("test empty") {
    std::ifstream ifs("samples/empty.txt", std::ios::binary);
    REQUIRE(ifs.is_open());
    CHECK(test_file(ifs));
}

TEST_CASE("test one letter") {
    std::ifstream ifs("samples/oneLetter.txt", std::ios::binary);
    REQUIRE(ifs.is_open());
    CHECK(test_file(ifs));
}

TEST_CASE("test 10 a") {
    std::ifstream ifs("samples/10a.txt", std::ios::binary);
    REQUIRE(ifs.is_open());
    CHECK(test_file(ifs));
}

TEST_CASE("test jpg") {
    std::ifstream ifs("samples/testJpg.jpg", std::ios::binary);
    REQUIRE(ifs.is_open());
    CHECK(test_file(ifs));
}

bool generate_random_file(const std::string& filename, std::size_t size) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dis(0, 255);

    for (std::size_t i = 0; i < size; ++i) {
        unsigned char ch = dis(gen);
        ofs.write(reinterpret_cast<const char*>(&ch), sizeof(ch));
    }

    return true;
}

TEST_CASE("test random stream") {
    const std::size_t file_size = 10'000'000;
    const std::string filename = "samples/random_stream.bin";

    for (int i = 0; i < 10; ++i) {
        REQUIRE(generate_random_file(filename, file_size));

        std::ifstream ifs(filename, std::ios::binary);
        CHECK(test_file(ifs));
    }
}
