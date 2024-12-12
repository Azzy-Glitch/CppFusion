#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Student
{
    string Class;
    string name;
    int numbers;

public:
    Student(string n = "", string c = "", int num = 0)
        : Class(c), name(n), numbers(num) {}

    void displayStudentData() const
    {
        cout << "Student Name: " << name
             << ", Class: " << Class
             << ", Numbers: " << numbers << endl;
    }

    static void getStudentData(vector<Student> &students)
    {
        int Size;
        cout << "Enter the number of Students: ";
        while (!(cin >> Size) || Size < 0)
        {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        ofstream outFile("Students.txt");
        if (!outFile.is_open())
        {
            cerr << "Error: Could not open file Students.txt for writing.\n";
            return;
        }

        for (int i = 0; i < Size; i++)
        {
            string n, c;
            int num;

            cout << "\nEnter details for Student " << i + 1 << ":\n";

            cout << "Enter Student Name: ";
            getline(cin, n);

            cout << "Enter Class: ";
            getline(cin, c);

            cout << "Enter Numbers: " << endl;
            while (!(cin >> num) || num < 0)
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            students.push_back(Student(n, c, num));
            outFile << n << "," << c << "," << num << endl;
        }
        outFile.close();
    }
};

#endif