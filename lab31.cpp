#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair

class Employee {
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
    Employee(const std::string& empName, double salary, double hr, double tr, double other, double pf, double it)
        : name(empName), baseSalary(salary), hrPercent(hr), trPercent(tr), otherPercent(other), pfPercent(pf), itPercent(it) {
        grossSalary = calculateGrossSalary(*this);
        netSalary = calculateNetSalary(*this);
    }

    // Friend function to calculate gross salary
    friend double calculateGrossSalary(const Employee& emp) {
        double hr = (emp.hrPercent / 100.0) * emp.baseSalary;
        double tr = (emp.trPercent / 100.0) * emp.baseSalary;
        double otherAllowances = (emp.otherPercent / 100.0) * emp.baseSalary;
        return emp.baseSalary + hr + tr + otherAllowances;
    }

    // Friend function to calculate net salary
    friend double calculateNetSalary(const Employee& emp) {
        double pf = (emp.pfPercent / 100.0) * emp.baseSalary;
        double it = (emp.itPercent / 100.0) * emp.baseSalary;
        return emp.grossSalary - (pf + it);
    }

    double getNetSalary() const {
        return netSalary;
    }

    std::string getName() const {
        return name;
    }

    // Function to display employee information
    void displayEmployeeInfo() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Employee Name: " << name << std::endl;
        std::cout << "Base Salary: " << baseSalary << std::endl;
        std::cout << "Gross Salary: " << grossSalary << std::endl;
        std::cout << "Net Salary: " << netSalary << std::endl;
    }
};

// Linear search method to find the max and min salary employees
void findMaxMinLinear(const std::vector<Employee>& employees) {
    if (employees.empty()) return;

    const Employee* maxEmp = &employees[0];
    const Employee* minEmp = &employees[0];

    for (const auto& emp : employees) {
        if (emp.getNetSalary() > maxEmp->getNetSalary()) {
            maxEmp = &emp;
        }
        if (emp.getNetSalary() < minEmp->getNetSalary()) {
            minEmp = &emp;
        }
    }

    std::cout << "Linear Search Method:\n";
    std::cout << "Employee with Max Salary:\n";
    maxEmp->displayEmployeeInfo();
    std::cout << "\nEmployee with Min Salary:\n";
    minEmp->displayEmployeeInfo();
}

// Divide and conquer method to find the max and min salary employees
std::pair<const Employee*, const Employee*> findMaxMinDivideAndConquer(const std::vector<Employee>& employees, int left, int right) {
    if (left == right) {
        return {&employees[left], &employees[left]};
    }
    
    if (right == left + 1) {
        if (employees[left].getNetSalary() > employees[right].getNetSalary()) {
            return {&employees[left], &employees[right]};
        } else {
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

int main() {
    std::vector<Employee> employees = {
        Employee("John Doe", 50000, 10, 5, 2, 8, 10),
        Employee("Jane Smith", 75000, 12, 8, 3, 7, 12),
        Employee("Mark Taylor", 60000, 15, 7, 4, 10, 15),
        Employee("Emily Johnson", 80000, 20, 10, 5, 8, 18),
        Employee("Chris Evans", 45000, 18, 6, 4, 5, 10)
    };

    // Find max and min salary using linear search
    findMaxMinLinear(employees);

    std::cout << "\n"; 

    // Find max and min salary using divide and conquer
    std::pair<const Employee*, const Employee*> result = findMaxMinDivideAndConquer(employees, 0, employees.size() - 1);

    std::cout << "Divide and Conquer Method:\n";
    std::cout << "Employee with Max Salary:\n";
    result.first->displayEmployeeInfo();
    std::cout << "\nEmployee with Min Salary:\n";
    result.second->displayEmployeeInfo();

    std::cout << "\n";
    // std::cout << "Details of Employees:\n";

    // for(auto em : employees){
    //     // print details
    //     em.displayEmployeeInfo();
    //     std::cout<<"\n";
    // }

    return 0;
}
