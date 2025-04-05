#ifndef INSTITUTE_MANAGEMENT_H
#define INSTITUTE_MANAGEMENT_H

#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <direct.h>

class InstituteSystem
{
    static bool isAdminAuthenticated;
    static time_t lastAdministratorActivityTime;

    static void showAdminMenu()
    {
        while (true)
        {
            system("clear || cls");
            std::cout << "\nADMINISTRATOR MENU\n"
                      << "1. Add Student\n"
                      << "2. Add Teacher\n"
                      << "3. Add Staff\n"
                      << "4. Edit Student\n"
                      << "5. Edit Teacher\n"
                      << "6. Edit Staff\n"
                      << "7. Delete Student\n"
                      << "8. Delete Teacher\n"
                      << "9. Delete Staff\n"
                      << "10. Change Password\n"
                      << "11. Backup Data\n"
                      << "12. Return to Main Menu\n"
                      << "Enter choice: ";

            int userChoice;
            std::cin >> userChoice;
            Person::clearInputBuffer();

            switch (userChoice)
            {
            case 1:
                addStudent();
                break;
            case 2:
                addTeacher();
                break;
            case 3:
                addStaff();
                break;
            case 4:
                editStudent();
                break;
            case 5:
                editTeacher();
                break;
            case 6:
                editStaff();
                break;
            case 7:
                deleteStudent();
                break;
            case 8:
                deleteTeacher();
                break;
            case 9:
                deleteStaff();
                break;
            case 10:
                Person::changeAdminPassword();
                break;
            case 11:
                backupData();
                break;
            case 12:
                return;
            default:
                std::cout << "Invalid choice!\n";
            }
            Person::pressToContinue();
            lastAdministratorActivityTime = time(nullptr);
        }
    }

    static void addStudent()
    {
        Student newStudent;
        newStudent.getData();
        newStudent.saveToFile();
        Student::loadFromFile();
        std::cout << "\nStudent added successfully!\n";
    }

    static void addTeacher()
    {
        Teacher newTeacher;
        newTeacher.getData();
        newTeacher.saveToFile();
        Teacher::loadFromFile();
        std::cout << "\nTeacher added successfully!\n";
    }

    static void addStaff()
    {
        Staff newStaff;
        newStaff.getData();
        newStaff.saveToFile();
        Staff::loadFromFile();
        std::cout << "\nStaff member added successfully!\n";
    }

    static void editStudent()
    {
        int rollNumber;
        std::cout << "Enter roll number to edit: ";
        std::cin >> rollNumber;
        Person::clearInputBuffer();
        
        Student* student = Student::findStudentByRollNumber(rollNumber);
        if (student) {
            Student updatedStudent = *student;
            updatedStudent.getData();
            updatedStudent.saveToFile();
            Student::updateStudent(updatedStudent);
            Student::loadFromFile();
            std::cout << "\nStudent record updated successfully!\n";
        } else {
            std::cout << "\nStudent with roll number " << rollNumber << " not found!\n";
        }
    }

    static void editTeacher()
    {
        std::string name;
        std::cout << "Enter teacher name to edit: ";
        std::getline(std::cin, name);
        
        Teacher* teacher = Teacher::findTeacherByName(name);
        if (teacher) {
            Teacher updatedTeacher = *teacher;
            updatedTeacher.getData();
            updatedTeacher.saveToFile();
            Teacher::updateTeacher(updatedTeacher);
            Teacher::loadFromFile();
            std::cout << "\nTeacher record updated successfully!\n";
        } else {
            std::cout << "\nTeacher with name " << name << " not found!\n";
        }
    }

    static void editStaff()
    {
        std::string name;
        std::cout << "Enter staff name to edit: ";
        std::getline(std::cin, name);
        
        Staff* staff = Staff::findStaffByName(name);
        if (staff) {
            Staff updatedStaff = *staff;
            updatedStaff.getData();
            updatedStaff.saveToFile();
            Staff::updateStaff(updatedStaff);
            Staff::loadFromFile();
            std::cout << "\nStaff record updated successfully!\n";
        } else {
            std::cout << "\nStaff member with name " << name << " not found!\n";
        }
    }

    static void deleteStudent()
    {
        int rollNumber;
        std::cout << "Enter roll number to delete: ";
        std::cin >> rollNumber;
        Person::clearInputBuffer();
        
        if (Student::findStudentByRollNumber(rollNumber)) {
            Student::removeStudent(rollNumber);
            std::ofstream file("students.dat");
            for (const auto& student : Student::students) {
                student.saveToFile();
            }
            std::cout << "\nStudent record deleted successfully!\n";
        } else {
            std::cout << "\nStudent with roll number " << rollNumber << " not found!\n";
        }
    }

    static void deleteTeacher()
    {
        std::string name;
        std::cout << "Enter teacher name to delete: ";
        std::getline(std::cin, name);
        
        if (Teacher::findTeacherByName(name)) {
            Teacher::removeTeacher(name);
            std::ofstream file("teachers.txt");
            for (const auto& teacher : Teacher::teachers) {
                teacher.saveToFile();
            }
            std::cout << "\nTeacher record deleted successfully!\n";
        } else {
            std::cout << "\nTeacher with name " << name << " not found!\n";
        }
    }

    static void deleteStaff()
    {
        std::string name;
        std::cout << "Enter staff name to delete: ";
        std::getline(std::cin, name);
        
        if (Staff::findStaffByName(name)) {
            Staff::removeStaff(name);
            std::ofstream file("staff.txt");
            for (const auto& staff : Staff::staffMembers) {
                staff.saveToFile();
            }
            std::cout << "\nStaff record deleted successfully!\n";
        } else {
            std::cout << "\nStaff member with name " << name << " not found!\n";
        }
    }

    static void backupData()
    {
        std::string backupDir = "backup_" + std::to_string(time(nullptr));
        
        // Create directory using platform-specific method
        #ifdef _WIN32
        if (_mkdir(backupDir.c_str()) != 0) {
            std::cerr << "Failed to create backup directory\n";
            return;
        }
        #else
        if (mkdir(backupDir.c_str(), 0777) != 0) {
            std::cerr << "Failed to create backup directory\n";
            return;
        }
        #endif

        // Copy students.dat
        std::ifstream srcStudents("students.dat", std::ios::binary);
        std::ofstream destStudents(backupDir + "/students.dat", std::ios::binary);
        destStudents << srcStudents.rdbuf();
        srcStudents.close();
        destStudents.close();

        // Copy teachers.txt
        std::ifstream srcTeachers("teachers.txt", std::ios::binary);
        std::ofstream destTeachers(backupDir + "/teachers.txt", std::ios::binary);
        destTeachers << srcTeachers.rdbuf();
        srcTeachers.close();
        destTeachers.close();

        // Copy staff.txt
        std::ifstream srcStaff("staff.txt", std::ios::binary);
        std::ofstream destStaff(backupDir + "/staff.txt", std::ios::binary);
        destStaff << srcStaff.rdbuf();
        srcStaff.close();
        destStaff.close();

        std::cout << "\nData backed up successfully to " << backupDir << "!\n";
    }

public:
    static void initialize()
    {
        Student::loadFromFile();
        Teacher::loadFromFile();
        Staff::loadFromFile();
        isAdminAuthenticated = false;
        lastAdministratorActivityTime = time(nullptr);
    }

    static void mainMenu()
    {
        while (true)
        {
            system("clear || cls");
            std::cout << "\nSCHOOL MANAGEMENT SYSTEM\n"
                      << "1. View Student Records\n"
                      << "2. View Teacher Records\n"
                      << "3. View Staff Records\n"
                      << "4. Search Student by Roll Number\n"
                      << "5. Search Teacher by Name\n"
                      << "6. Search Staff by Name\n"
                      << "7. Admin Login\n"
                      << "8. Exit\n"
                      << "Enter choice: ";

            int choice;
            std::cin >> choice;
            Person::clearInputBuffer();

            switch (choice)
            {
            case 1:
                Student::displayAll();
                break;
            case 2:
                Teacher::displayAll();
                break;
            case 3:
                Staff::displayAll();
                break;
            case 4:
            {
                std::cout << "Enter Roll Number: ";
                int roll;
                std::cin >> roll;
                Person::clearInputBuffer();
                Student::searchByRollNumber(roll);
                break;
            }
            case 5:
            {
                std::string name;
                std::cout << "Enter Teacher Name: ";
                std::getline(std::cin, name);
                Teacher::search(name);
                break;
            }
            case 6:
            {
                std::string name;
                std::cout << "Enter Staff Name: ";
                std::getline(std::cin, name);
                Staff::search(name);
                break;
            }
            case 7:
                if (Person::authenticateAdmin())
                {
                    isAdminAuthenticated = true;
                    lastAdministratorActivityTime = time(nullptr);
                    showAdminMenu();
                }
                break;
            case 8:
                std::cout << "\nExiting system...\n";
                return;
            default:
                std::cout << "Invalid choice!\n";
            }
            Person::pressToContinue();
        }
    }
};

bool InstituteSystem::isAdminAuthenticated = false;
time_t InstituteSystem::lastAdministratorActivityTime = 0;

#endif