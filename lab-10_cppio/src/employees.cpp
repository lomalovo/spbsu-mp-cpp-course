#include "employees.h"
#include "bin_manip.h"

Employee::Employee() : _name("") {}
Employee::Employee(const std::string& name) : _name(name) {}

Developer::Developer() : _base_salary(0), _has_bonus(false) {}

Developer::Developer(const std::string& name, int base_salary, bool has_bonus)
    : Employee(name), _base_salary(base_salary), _has_bonus(has_bonus) {}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) {
        salary += 1000;
    }
    return salary;
}

void Developer::read(std::istream& is) {
    is >> _name >> _base_salary >> _has_bonus;
}

void Developer::write(std::ostream& os) const {
    os << "Developer" << "\n"
    << "Name: " << _name << "\n"
    << "Base Salary: " << _base_salary << "\n"
    << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

void Developer::readBinary(std::ifstream& ifs) {
    char name_buffer[101];
    read_c_str(ifs, name_buffer);
    _name = name_buffer;
    read_le_int32(ifs, _base_salary);
    read_bool(ifs, _has_bonus);
}

void Developer::writeBinary(std::ofstream& ofs) const {
    write_le_int32(ofs, 1);
    write_c_str(ofs, _name.c_str());
    write_le_int32(ofs, _base_salary);
    write_bool(ofs, _has_bonus);
}

SalesManager::SalesManager() : Employee(""), _base_salary(0), _sold_nm(0), _price(0) {}

SalesManager::SalesManager(const std::string& name, int base_salary, int sold_nm, int price)
    : Employee(name), _base_salary(base_salary), _sold_nm(sold_nm), _price(price) {}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::read(std::istream& is) {
    is >> _name >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::write(std::ostream& os) const {
    os << "Sales Manager" << "\n"
    << "Name: " << _name << "\n"
    << "Base Salary: " << _base_salary << "\n"
    << "Sold items: " << _sold_nm << "\n"
    << "Item price: " << _price << std::endl;
}

void SalesManager::readBinary(std::ifstream& ifs) {
    char name_buffer[101];
    read_c_str(ifs, name_buffer);
    _name = name_buffer;
    read_le_int32(ifs, _base_salary);
    read_le_int32(ifs, _sold_nm);
    read_le_int32(ifs, _price);
}

void SalesManager::writeBinary(std::ofstream& ofs) const {
    write_le_int32(ofs, 2);
    write_c_str(ofs, _name.c_str());
    write_le_int32(ofs, _base_salary);
    write_le_int32(ofs, _sold_nm);
    write_le_int32(ofs, _price);
}

EmployeesArray::EmployeesArray() : _employees(nullptr), _size(0) {}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; ++i) {
        delete _employees[i];
    }
    delete[] _employees;
}

void EmployeesArray::add(Employee* e) {
    Employee** temp = new Employee*[_size + 1];
    std::copy(_employees, _employees + _size, temp);
    temp[_size] = e;
    delete[] _employees;
    _employees = temp;
    ++_size;
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (int i = 0; i < _size; ++i) {
        total += _employees[i]->salary();
    }
    return total;
}


void EmployeesArray::write(std::ostream& os) const {
    for (int i = 0; i < _size; ++i) {
        os << i + 1 << ". ";
        os << *_employees[i];
    }
}

void EmployeesArray::readBinary(std::ifstream& ifs) {
    int add_size;
    read_le_int32(ifs, add_size);
    Employee** temp = new Employee*[_size + add_size];
    std::copy(_employees, _employees + _size, temp);
    for (int i = 0; i < add_size; ++i) {
        int type;
        read_le_int32(ifs, type);
        if (type == 1) {
            temp[_size+i] = new Developer();
        } else if (type == 2) {
            temp[_size+i] = new SalesManager();
        }
        temp[_size+i]->readBinary(ifs);
    }
    _size = _size + add_size;
    delete[] _employees;
    _employees = temp;
}

void EmployeesArray::writeBinary(std::ofstream& ofs) const {
    write_le_int32(ofs, _size);
    for (int i = 0; i < _size; ++i) {
        ofs << *_employees[i];
    }
}

std::ostream& operator<<(std::ostream& os, const Employee& employee) {
    employee.write(os);
    return os;
}

std::istream& operator>>(std::istream& is, Employee& employee) {
    employee.read(is);
    return is;
}

std::ofstream& operator<<(std::ofstream& ofs, const Employee& employee) {
    employee.writeBinary(ofs);
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Employee& employee) {
    employee.readBinary(ifs);
    return ifs;
}