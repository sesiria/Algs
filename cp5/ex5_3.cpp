
/*
* Exercise 5.3
* Author: sesiria  2018
* generic hashObject sample for STL.
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Example of an Employee class
class Employee
{
  public:
    Employee(const std::string & eName, double sala = 0, int senior = 0)
        : name{eName}, salary(sala), seniority{senior}
    {

    }
    const std::string &getName() const
    {
        return name;
    }

    bool operator==(const Employee &rhs) const
    {
        return getName() == rhs.getName();
    }

    bool operator!=(const Employee &rhs) const
    {
        return !(*this == rhs);
    }

  private:
    std::string name;
    double salary;
    int seniority;

    // additional private members not shown.
};

template <>
class hash<Employee>
{
  public:
    size_t operator()(const Employee &item)
    {
        static hash<std::string> hf;
        return hf(item.getName());
    }
};

class EmployeeFunction
{
  public:
    size_t operator()(const Employee &rhs) const
    {
        static hash<Employee> hf;
        return hf(rhs);
    }

    bool operator()(const Employee &lhs, const Employee &rhs) const
    {
        return lhs.getName() == rhs.getName();
    }
};

int main()
{
    unordered_set<Employee, EmployeeFunction, EmployeeFunction> hashMap;
    hashMap.insert(Employee("Johnson"));
    hashMap.insert(Employee("Kate"));

    unordered_map<Employee, Employee, EmployeeFunction, EmployeeFunction> hashMaps;
    
    return 0;
}