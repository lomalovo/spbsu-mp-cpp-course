#include "binManip.h"

std::ostream& write_int(std::ostream& os, int value) {
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return os;
}

std::istream& read_int(std::istream& is, int& value) {
    is.read(reinterpret_cast<char*>(&value), sizeof(value));
    return is;
}

std::ostream& write_char(std::ostream& os, char value) {
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return os;
}

std::istream& read_char(std::istream& is, char& value) {
    is.read(reinterpret_cast<char*>(&value), sizeof(value));
    return is;
}
