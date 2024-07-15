#ifndef BIN_MANIP_H_INCLUDED
#define BIN_MANIP_H_INCLUDED

#include <iostream>
#include <cstdint>
#include <cstring>

std::ostream& write_le_int32(std::ostream& os, int32_t value);

std::istream& read_le_int32(std::istream& is, int32_t& value);

std::ostream& write_bool(std::ostream& os, bool value);

std::istream& read_bool(std::istream& is, bool& value);

std::ostream& write_c_str(std::ostream& os, const char* str);

std::istream& read_c_str(std::istream& is, char* str);

#endif
