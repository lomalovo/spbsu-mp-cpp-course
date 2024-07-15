#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

class Employee {
public:
    Employee();
    Employee(const std::string& name);
    virtual int salary() const = 0;
    virtual void read(std::istream& is) = 0;
    virtual void write(std::ostream& os) const = 0;
    virtual void readBinary(std::ifstream& ifs) = 0;
    virtual void writeBinary(std::ofstream& ofs) const = 0;
    virtual ~Employee() {}
protected:
    std::string _name;
};

class Developer : public Employee {
public:
    Developer();
    Developer(const std::string& name, int base_salary, bool has_bonus);
    int salary() const override;
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;
    void readBinary(std::ifstream& ifs) override;
    void writeBinary(std::ofstream& ofs) const override;
private:
    int _base_salary;
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    SalesManager();
    SalesManager(const std::string& name, int base_salary, int sold_nm, int price);
    int salary() const override;
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;
    void readBinary(std::ifstream& ifs) override;
    void writeBinary(std::ofstream& ofs) const override;
private:
    int _base_salary;
    int _sold_nm;
    int _price;
};

class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(Employee* e);
    int total_salary() const;
    void write(std::ostream& os) const;
    void readBinary(std::ifstream& ifs);
    void writeBinary(std::ofstream& ofs) const;
private:
    Employee** _employees;
    int _size;
};

std::ostream& operator<<(std::ostream& os, const Employee& employee);
std::istream& operator>>(std::istream& is, Employee& employee);
std::ofstream& operator<<(std::ofstream& ofs, const Employee& employee);
std::ifstream& operator>>(std::ifstream& ifs, Employee& employee);

#endif
