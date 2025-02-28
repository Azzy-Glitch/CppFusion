#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <limits>

using namespace std;

struct Employee
{
    int id;
    string name;
    double salary;
};

void displayEmployee(const Employee &emp)
{
    cout << "ID: " << emp.id
         << " | Name: " << emp.name
         << " | Salary: $" << emp.salary << endl;
}

void displayMenu()
{
    cout << "\nEmployee Management System\n";
    cout << "1. Display All Employees\n";
    cout << "2. Sort Employees by Salary (High to Low)\n";
    cout << "3. Show High Earners (>$50k)\n";
    cout << "4. Display Salary Statistics\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void displayAllEmployees(const vector<Employee> &employees)
{
    cout << "\nEmployee List:\n";
    cout << "-----------------------------\n";
    for (const auto &emp : employees)
    {
        displayEmployee(emp);
    }
}

void sortEmployeesBySalary(vector<Employee> &employees)
{
    sort(employees.begin(), employees.end(),
         [](const Employee &a, const Employee &b)
         {
             return a.salary > b.salary;
         });
    cout << "\nEmployees sorted by salary (highest to lowest)\n";
}

void displayHighEarners(const vector<Employee> &employees)
{
    vector<Employee> highEarners;
    copy_if(employees.begin(), employees.end(), back_inserter(highEarners),
            [](const Employee &emp)
            { return emp.salary > 50000; });

    cout << "\nHigh Earners (>$50k):\n";
    cout << "-----------------------------\n";
    for (const auto &emp : highEarners)
    {
        displayEmployee(emp);
    }
}

void displaySalaryStatistics(const vector<Employee> &employees)
{
    if (employees.empty())
    {
        cout << "\nNo employees to calculate statistics\n";
        return;
    }

    double total = accumulate(employees.begin(), employees.end(), 0.0,
                              [](double sum, const Employee &emp)
                              { return sum + emp.salary; });

    auto maxSalary = max_element(employees.begin(), employees.end(),
                                 [](const Employee &a, const Employee &b)
                                 { return a.salary < b.salary; });

    cout << "\nSalary Statistics:\n";
    cout << "-----------------------------\n";
    cout << "Total Salary: $" << total << endl;
    cout << "Average Salary: $" << (total / employees.size()) << endl;
    cout << "Highest Salary: $" << maxSalary->salary
         << " (ID: " << maxSalary->id
         << ", Name: " << maxSalary->name << ")\n";
}

int getIntegerInput()
{
    int value;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cin.ignore();
    return value;
}

int main()
{
    vector<Employee> employees = {
        {101, "hitesh", 100000},
        {102, "saksham", 30000},
        {103, "shubham", 50000},
        {104, "anirudh", 60000},
        {105, "aryan", 70000},
    };

    while (true)
    {
        displayMenu();
        int choice = getIntegerInput();

        switch (choice)
        {
        case 1:
            displayAllEmployees(employees);
            break;
        case 2:
            sortEmployeesBySalary(employees);
            displayAllEmployees(employees);
            break;
        case 3:
            displayHighEarners(employees);
            break;
        case 4:
            displaySalaryStatistics(employees);
            break;
        case 5:
            cout << "\nExiting program...\n";
            return 0;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}