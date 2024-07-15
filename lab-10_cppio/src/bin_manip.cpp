#include "bin_manip.h"

std::ostream& write_le_int32(std::ostream& os, int32_t value) {
    os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return os;
}

std::istream& read_le_int32(std::istream& is, int32_t& value) {
    is.read(reinterpret_cast<char*>(&value), sizeof(value));
    return is;
}

std::ostream& write_bool(std::ostream& os, bool value) {
    os.put(value ? 1 : 0);
    return os;
}

std::istream& read_bool(std::istream& is, bool& value) {
    char ch;
    is.get(ch);
    value = (ch != 0);
    return is;
}

std::ostream& write_c_str(std::ostream& os, const char* str) {
    while (*str != '\0') {
        os.put(*str++);
    }
    os.put('\0');
    return os;
}

std::istream& read_c_str(std::istream& is, char* buffer) {
    std::size_t bytesRead = 0;
    char ch;
    while (is.get(ch) && ch != '\0') {
        buffer[bytesRead++] = ch;
    }
    buffer[bytesRead] = '\0';
    return is;
}
