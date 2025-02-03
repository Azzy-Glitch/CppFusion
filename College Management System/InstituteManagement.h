#ifndef INSTITUTE_MANAGEMENT_H
#define INSTITUTE_MANAGEMENT_H

#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

class InstituteSystem
{
    static bool adminAuthenticated;

    static void showAdminMenu()
    {
        while (true)
        {
            system("clear || cls");
            std::cout << "\nADMINISTRATOR MENU\n"
                      << "1. Add Student\n"
                      << "2. Add Teacher\n"
                      << "3. Add Staff\n"
                      << "4. Change Password\n"
                      << "5. Return to Main Menu\n"
                      << "Enter choice: ";

            int choice;
            std::cin >> choice;
            Person::clearInputBuffer();

            switch (choice)
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
                Person::changeAdminPassword();
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice!\n";
            }
            Person::pressToContinue();
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

public:
    static void initialize()
    {
        Student::loadFromFile();
        Teacher::loadFromFile();
        Staff::loadFromFile();
        adminAuthenticated = false;
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
                      << "5. Admin Login\n"
                      << "6. Exit\n"
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
                if (Person::authenticateAdmin())
                {
                    adminAuthenticated = true;
                    showAdminMenu();
                }
                break;
            case 6:
                std::cout << "\nExiting system...\n";
                return;
            default:
                std::cout << "Invalid choice!\n";
            }
            Person::pressToContinue();
        }
    }
};

bool InstituteSystem::adminAuthenticated = false;

#endif