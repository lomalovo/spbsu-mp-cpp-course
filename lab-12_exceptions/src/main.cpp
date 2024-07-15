#include "matrix.hpp"
#include <iostream>
#include <vector>
#include <sstream>

int parseRegister(const std::string& reg) {
    if (reg[0] != '$' || reg.length() < 2) {
        throw std::invalid_argument("Invalid register format.");
    }
    return std::stoi(reg.substr(1));
}

int main() {
    std::vector<Matrix> registers(10);
    std::string line, cmd;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> cmd;
        try {
            if (cmd == "exit") {
                break;
            } else if (cmd == "load") {
                std::string regStr, filename;
                iss >> regStr >> filename;
                int reg = parseRegister(regStr);
                registers[reg].loadFromFile(filename);
            } else if (cmd == "print") {
                std::string regStr;
                iss >> regStr;
                int reg = parseRegister(regStr);
                registers[reg].print();
            } else if (cmd == "add") {
                std::string reg1Str, reg2Str;
                iss >> reg1Str >> reg2Str;
                int reg1 = parseRegister(reg1Str);
                int reg2 = parseRegister(reg2Str);
                registers[reg1] = registers[reg1] + registers[reg2];
            } else if (cmd == "mul") {
                std::string reg1Str, reg2Str;
                iss >> reg1Str >> reg2Str;
                int reg1 = parseRegister(reg1Str);
                int reg2 = parseRegister(reg2Str);
                registers[reg1] = registers[reg1] * registers[reg2];
            } else if (cmd == "elem") {
                std::string regStr;
                int row, col;
                iss >> regStr >> row >> col;
                int reg = parseRegister(regStr);
                std::cout << registers[reg].getElement(row, col) << std::endl;
            }
        } catch (const MatrixException& e) {
            std::cout << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Unable to allocate memory." << std::endl;
        }
    }

    return 0;
}
