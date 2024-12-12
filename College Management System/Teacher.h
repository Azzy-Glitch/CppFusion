#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Teacher
{
    string name;
    string subject;
    int salary;

public:
    Teacher(string n = "", string s = "", int sal = 0)
        : name(n), subject(s), salary(sal) {}

    void displayTeacherData() const
    {
        cout << "Teacher Name: " << name
             << ", Subject: " << subject
             << ", Salary: " << salary << endl;
    }

    static void getTeacherData(vector<Teacher> &teachers)
    {
        int Size;
        cout << "Enter the number of Teachers: ";
        while (!(cin >> Size) || Size < 0)
        {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        ofstream outFile("Teacher.txt");
        if (!outFile.is_open())
        {
            cerr << "Error: Could not open file Teacher.txt for writing.\n";
            return;
        }

        for (int i = 0; i < Size; i++)
        {
            string n, s;
            int sal;

            cout << "\nEnter details for Teacher " << i + 1 << ":\n";

            cout << "Enter Teacher Name: ";
            getline(cin, n);

            cout << "Enter Subject: ";
            getline(cin, s);

            cout << "Enter Salary: " << endl;
            while (!(cin >> sal) || sal < 0)
            {
                cout << "Invalid input. Please enter a valid salary: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            teachers.push_back(Teacher(n, s, sal));
            outFile << n << "," << s << "," << sal << endl;
        }
        outFile.close();
    }
};

#endif