#ifndef GETANDDISPLAY_H
#define GETANDDISPLAY_H

#include <vector>
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

class GetAndDisplay
{
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Staff> staffs;

public:
    void getAndDisplayData()
    {
        Student::getStudentData(students);
        Teacher::getTeacherData(teachers);
        Staff::getStaffData(staffs);

        cout << "\nDisplaying Student Data:\n";
        for (const auto &student : students)
        {
            student.displayStudentData();
        }

        cout << "\nDisplaying Teacher Data:\n";
        for (const auto &teacher : teachers)
        {
            teacher.displayTeacherData();
        }

        cout << "\nDisplaying Staff Data:\n";
        for (const auto &staff : staffs)
        {
            staff.displayStaffData();
        }
    }
};

#endif