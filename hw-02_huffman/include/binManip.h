#ifndef BIN_MANIP_H_INCLUDED
#define BIN_MANIP_H_INCLUDED

#include <iostream>
#include <cstdint>
#include <cstring>

std::ostream& write_int(std::ostream& os, int value);

std::istream& read_int(std::istream& is, int& value);

std::ostream& write_char(std::ostream& os, char value);

std::istream& read_char(std::istream& is, char& value);

#endif
