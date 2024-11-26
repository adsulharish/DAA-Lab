#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

// Utility function to trim whitespace from a string
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

class Employee
{
private:
    std::string name;
    double baseSalary;
    double hrPercent;
    double trPercent;
    double otherPercent;
    double pfPercent;
    double itPercent;
    double grossSalary;
    double netSalary;

public:
    // Constructor
    Employee(const std::string &empName, double salary, double hr, double tr, double other, double pf, double it)
        : name(empName), baseSalary(salary), hrPercent(hr), trPercent(tr), otherPercent(other), pfPercent(pf), itPercent(it)
    {
        grossSalary = calculateGrossSalary(*this);
        netSalary = calculateNetSalary(*this);
    }

    // Friend function to calculate gross salary
    friend double calculateGrossSalary(const Employee &emp)
    {
        double hr = (emp.hrPercent / 100.0) * emp.baseSalary;
        double tr = (emp.trPercent / 100.0) * emp.baseSalary;
        double otherAllowances = (emp.otherPercent / 100.0) * emp.baseSalary;
        return emp.baseSalary + hr + tr + otherAllowances;
    }

    // Friend function to calculate net salary
    friend double calculateNetSalary(const Employee &emp)
    {
        double pf = (emp.pfPercent / 100.0) * emp.baseSalary;
        double it = (emp.itPercent / 100.0) * emp.baseSalary;
        return emp.grossSalary - (pf + it);
    }

    double getNetSalary() const
    {
        return netSalary;
    }

    std::string getName() const
    {
        return name;
    }

    // Function to display employee information
    void displayEmployeeInfo() const
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Employee Name: " << name << std::endl;
        std::cout << "Base Salary: " << baseSalary << std::endl;
        std::cout << "Gross Salary: " << grossSalary << std::endl;
        std::cout << "Net Salary: " << netSalary << std::endl;
    }
};

// Function to parse a line from the CSV file and return an Employee object
Employee parseEmployee(const std::string &line)
{
    std::stringstream ss(line);
    std::string name, temp;
    double baseSalary, hrPercent, trPercent, otherPercent, pfPercent, itPercent;

    // Get and trim the employee's name
    std::getline(ss, name, ',');
    name = trim(name);

    // Get and convert the remaining fields
    std::getline(ss, temp, ',');
    baseSalary = std::stod(trim(temp)); // Convert string to double
    std::getline(ss, temp, ',');
    hrPercent = std::stod(trim(temp)); // Convert string to double
    std::getline(ss, temp, ',');
    trPercent = std::stod(trim(temp)); // Convert string to double
    std::getline(ss, temp, ',');
    otherPercent = std::stod(trim(temp)); // Convert string to double
    std::getline(ss, temp, ',');
    pfPercent = std::stod(trim(temp)); // Convert string to double
    std::getline(ss, temp, ',');
    itPercent = std::stod(trim(temp)); // Convert string to double

    return Employee(name, baseSalary, hrPercent, trPercent, otherPercent, pfPercent, itPercent);
}

std::pair<const Employee*, const Employee*> findMaxMinDivideAndConquer(const std::vector<Employee>& employees, int left, int right)
{
    if (left == right)
    {
        return {&employees[left], &employees[left]};
    }
    
    if (right == left + 1)
    {
        if (employees[left].getNetSalary() > employees[right].getNetSalary())
        {
            return {&employees[left], &employees[right]};
        }
        else
        {
            return {&employees[right], &employees[left]};
        }
    }

    int mid = (left + right) / 2;
    auto leftPair = findMaxMinDivideAndConquer(employees, left, mid);
    auto rightPair = findMaxMinDivideAndConquer(employees, mid + 1, right);

    const Employee* maxEmp = (leftPair.first->getNetSalary() > rightPair.first->getNetSalary()) ? leftPair.first : rightPair.first;
    const Employee* minEmp = (leftPair.second->getNetSalary() < rightPair.second->getNetSalary()) ? leftPair.second : rightPair.second;

    return {maxEmp, minEmp};
}

int main()
{
    std::ifstream file("employees3S.csv");
    std::string line;
    std::vector<Employee> employees;

    // Read each line from the CSV file and create an Employee object
    while (std::getline(file, line))
    {
        try
        {
            Employee emp = parseEmployee(line);
            employees.push_back(emp);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Invalid argument encountered while processing line: " << line << std::endl;
            continue; // Skip to the next line
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << " while processing line: " << line << std::endl;
            continue; // Skip to the next line
        }
    }

    // Initialize min and max salaries with extreme values
    double minSalary = std::numeric_limits<double>::max();
    double maxSalary = std::numeric_limits<double>::lowest();
    std::string minSalaryEmployee, maxSalaryEmployee;

    // Find employee with min and max net salary
    for (const auto &emp : employees)
    { 
        if (emp.getNetSalary() < minSalary)
        {
            minSalary = emp.getNetSalary();
            minSalaryEmployee = emp.getName();
        }
        if (emp.getNetSalary() > maxSalary)
        {
            maxSalary = emp.getNetSalary();
            maxSalaryEmployee = emp.getName();
        }
    }

    // Output the results
    std::cout << "Employee with Maximum Net Salary: " << minSalaryEmployee << " (" << minSalary << ")" << std::endl;
    std::cout << "Employee with Minimum Net Salary: " << maxSalaryEmployee << " (" << maxSalary << ")" << std::endl;

    std::cout << "\n";
    std::cout << "By using Divide and Conquer Method:\n";
    auto result = findMaxMinDivideAndConquer(employees, 0, employees.size() - 1);
    std::cout << "Employee with Minimum Net Salary: " << result.first->getName() << " (" << result.first->getNetSalary() << ")" << std::endl;
    std::cout << "Employee with Maximum Net Salary: " << result.second->getName() << " (" << result.second->getNetSalary() << ")" << std::endl;

    return 0;
}
