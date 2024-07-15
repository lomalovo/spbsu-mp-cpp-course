#include "employees.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    EmployeesArray employeesArray;
    std::string command;
    while (std::cin >> command) {
        if (command == "exit") {
            break;
        } else if (command == "load") {
            std::string filename;
            std::cin >> filename;
            std::ifstream ifs(filename, std::ios::binary);
            if (!ifs) {
                std::cerr << "Error: Unable to open file " << filename << std::endl;
                continue;
            }
            employeesArray.readBinary(ifs);
            ifs.close();
        } else if (command == "save") {
            std::string filename;
            std::cin >> filename;
            std::ofstream ofs(filename, std::ios::binary);
            if (!ofs) {
                std::cerr << "Error: Unable to open file " << filename << std::endl;
                continue;
            }
            employeesArray.writeBinary(ofs);
            ofs.close();
        } else if (command == "add") {
            int type;
            std::cin >> type;
            if (type == 1) {
                std::string name;
                int base_salary;
                bool has_bonus;
                std::cin >> name >> base_salary >> has_bonus;
                Employee* developer = new Developer(name, base_salary, has_bonus);
                employeesArray.add(developer);
            } else if (type == 2) {
                std::string name;
                int base_salary, sold_nm, price;
                std::cin >> name >> base_salary >> sold_nm >> price;
                Employee* salesManager = new SalesManager(name, base_salary, sold_nm, price);
                employeesArray.add(salesManager);
            } else {
                std::cerr << "Error: Invalid employee type" << std::endl;
            }
        } else if (command == "list") {
            employeesArray.write(std::cout);
            std::cout << "== Total salary: " << employeesArray.total_salary() << std::endl << std::endl;
        } else {
            std::cerr << "Error: Unknown command" << std::endl;
        }
    }

    return 0;
}
