#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Staff
{
    string name;
    int salary;
    string department;

public:
    Staff(string n = "", int sal = 0, string d = "")
        : name(n), salary(sal), department(d) {}

    void displayStaffData() const
    {
        cout << "Staff Member Name: "
             << name
             << ", Salary: " << salary
             << ", Department: " << department << endl;
    }

    static void getStaffData(vector<Staff> &staffs)
    {
        int Size;
        cout << "Enter the number of Staff Members: ";
        while (!(cin >> Size) || Size < 0)
        {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        ofstream outFile("Staff.txt");
        if (!outFile.is_open())
        {
            cerr << "Error: Could not open file Staff.txt for writing.\n";
            return;
        }

        for (int i = 0; i < Size; i++)
        {
            string n, d;
            int sal;

            cout << "\nEnter details for Staff Member " << i + 1 << ":\n";

            cout << "Enter Staff Name: ";
            getline(cin, n);

            cout << "Enter Department: ";
            getline(cin, d);

            cout << "Enter Salary: " << endl;
            while (!(cin >> sal) || sal < 0)
            {
                cout << "Invalid input. Please enter a valid salary: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            staffs.push_back(Staff(n, sal, d));
            outFile << n << "," << sal << "," << d << endl;
        }
        outFile.close();
    }
};

#endif