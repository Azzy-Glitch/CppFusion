#include <iostream>
#include <vector>
// #include <limits>
using namespace std;

class student
{
    string Class;
    string name;
    int numbers;

public:

    student(string n = "", string c = "", int num = 0)
        : Class(c), name(n), numbers(num) {}

    void displayStudentData() const
    {
        cout << "Student Name: " << name
             << ", Class: " << Class
             << ", Numbers: " << numbers << endl;
    }

    static void getStudentData(vector<student> &students)
    {
        int Size;
        cout << "Enter the number of Students: ";
        cin >> Size;
        cin.ignore();

        for (int i = 0; i < Size; i++)
        {
            string n, c;
            int num;

            cout << "\nEnter details for Student " << i + 1 << ":\n";

            cout << "Enter Student Name: ";
            getline(cin, n);

            cout << "Enter Class: ";
            getline(cin, c);

            cout << "Enter Numbers: ";
            while (!(cin >> num) || num < 0)
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            students.push_back(student(n, c, num));
        }
    }
};

class teacher
{
    string name;
    string subject;
    int salary;

public:
    teacher(string n = "", string s = "", int sal = 0)
        : name(n), subject(s), salary(sal) {}

    void displayTeacherData() const
    {
        cout << "Teacher Name: " << name
             << ", Subject: " << subject
             << ", Salary: " << salary << endl;
    }

    static void getTeacherData(vector<teacher> &teachers)
    {
        int Size;
        cout << "Enter the number of Teachers: ";
        cin >> Size;
        cin.ignore();

        for (int i = 0; i < Size; i++)
        {
            string n, s;
            int sal;

            cout << "\nEnter details for Teacher " << i + 1 << ":\n";

            cout << "Enter Teacher Name: ";
            getline(cin, n);

            cout << "Enter Subject: ";
            getline(cin, s);

            cout << "Enter Salary: ";
            while (!(cin >> sal) || sal < 0)
            {
                cout << "Invalid input. Please enter a valid salary: ";
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            teachers.push_back(teacher(n, s, sal));
        }
    }
};

class staff
{
    string name;
    int salary;
    string department;

public:
    staff(string n = "", int sal = 0, string d = "")
        : name(n), salary(sal), department(d) {}

    void displayStaffData() const
    {
        cout << "Staff Member Name: " << name
             << ", Department: " << department
             << ", Salary: " << salary << endl;
    }

    static void getStaffData(vector<staff> &staffs)
    {
        int Size;
        cout << "Enter the number of Staff Members: ";
        cin >> Size;
        cin.ignore();

        for (int i = 0; i < Size; i++)
        {
            string n, d;
            int sal;

            cout << "\nEnter details for Staff Member " << i + 1 << ":\n";

            cout << "Enter Staff Member Name: ";
            getline(cin, n);

            cout << "Enter Department: ";
            getline(cin, d);

            cout << "Enter Salary: ";
            while (!(cin >> sal) || sal < 0)
            {
                cout << "Invalid input. Please enter a valid salary: ";
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            staffs.push_back(staff(n, sal, d));
        }
    }
};

class getAndDisplay
{
    vector<student> students;
    vector<teacher> teachers;
    vector<staff> staffs;

public:
    void getAndDisplayData()
    {
        // Get Data
        student::getStudentData(students);
        teacher::getTeacherData(teachers);
        staff::getStaffData(staffs);

        cout << "\nDisplaying Student Data:\n";
        for (const auto &s : students)
        {
            s.displayStudentData();
        }

        cout << "\nDisplaying Teacher Data:\n";
        for (const auto &t : teachers)
        {
            t.displayTeacherData();
        }

        cout << "\nDisplaying Staff Data:\n";
        for (const auto &st : staffs)
        {
            st.displayStaffData();
        }
    }
};

int main()
{
    getAndDisplay obj;
    obj.getAndDisplayData();

    return 0;
}
