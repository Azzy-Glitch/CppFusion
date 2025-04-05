#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <fstream>
#include <algorithm>

class Student : public Person
{
    std::string className;
    int rollNumber;
    std::map<std::string, std::pair<int, char>> academicRecord; // subject: (marks, grade)
public:
    static std::vector<Student> students;

    char calculateGrade(int marks) const
    {
        if (marks >= 90)
            return 'A';
        if (marks >= 80)
            return 'B';
        if (marks >= 70)
            return 'C';
        if (marks >= 60)
            return 'D';
        return 'F';
    }

    Student(const std::string &n = "", const std::string &cls = "", int roll = 0)
        : Person(n), className(cls), rollNumber(roll) {}

    void display() const override
    {
        std::cout << std::left
                  << std::setw(20) << personName
                  << std::setw(15) << className
                  << std::setw(10) << rollNumber
                  << "\n";
    }

    void displayAcademicRecord() const
    {
        printSectionHeader("Academic Record");
        std::cout << "Student Name: " << personName << "\n"
                  << "Class: " << className << "\n"
                  << "Roll Number: " << rollNumber << "\n\n";

        std::cout << std::left
                  << std::setw(20) << "Subject"
                  << std::setw(10) << "Marks"
                  << std::setw(10) << "Grade"
                  << "\n";
        printDivider(40);

        for (const auto &subject : academicRecord)
        {
            std::cout << std::setw(20) << subject.first
                      << std::setw(10) << subject.second.first
                      << std::setw(10) << subject.second.second
                      << "\n";
        }
        printDivider(40);
    }

    void getData() override
    {
        std::cout << "Enter student name: ";
        while (std::getline(std::cin, personName) && !isValidName(personName))
        {
            std::cout << "Invalid name! Enter again: ";
        }

        std::cout << "Enter class: ";
        std::getline(std::cin, className);

        std::cout << "Enter roll number: ";
        while (!(std::cin >> rollNumber) || rollNumber <= 0)
        {
            std::cout << "Invalid input! Enter positive number: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        int numberOfSubjects;
        std::cout << "Number of subjects: ";
        while (!(std::cin >> numberOfSubjects) || numberOfSubjects <= 0)
        {
            std::cout << "Invalid input! Enter positive number: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        for (int i = 0; i < numberOfSubjects; i++)
        {
            std::string currentSubjectName;
            int subjectMarks;

            std::cout << "Subject " << i + 1 << " name: ";
            std::getline(std::cin, currentSubjectName);

            std::cout << "Marks (0-100): ";
            while (!(std::cin >> subjectMarks) || subjectMarks < 0 || subjectMarks > 100)
            {
                std::cout << "Invalid marks! Enter between 0-100: ";
                clearInputBuffer();
            }
            clearInputBuffer();

            academicRecord[currentSubjectName] = {subjectMarks, calculateGrade(subjectMarks)};
        }
    }

    void saveToFile() const override
    {
        std::ofstream file("students.dat", std::ios::app);
        if (file)
        {
            file << personName << "|" << className << "|" << rollNumber;
            for (const auto &subject : academicRecord)
            {
                file << "|" << subject.first << ":"
                     << subject.second.first << ":"
                     << subject.second.second;
            }
            file << "\n";
        }
    }

    static void loadFromFile()
    {
        students.clear();
        std::ifstream file("students.dat");
        std::string line;

        while (std::getline(file, line))
        {
            size_t pos = 0;
            std::vector<std::string> tokens;

            while ((pos = line.find('|')) != std::string::npos)
            {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() >= 3)
            {
                Student student(tokens[0], tokens[1], std::stoi(tokens[2]));

                for (size_t i = 3; i < tokens.size(); i++)
                {
                    size_t colon1 = tokens[i].find(':');
                    size_t colon2 = tokens[i].rfind(':');

                    if (colon1 != std::string::npos && colon2 != std::string::npos)
                    {
                        std::string subject = tokens[i].substr(0, colon1);
                        int marks = std::stoi(tokens[i].substr(colon1 + 1, colon2 - colon1 - 1));
                        char grade = tokens[i][colon2 + 1];

                        student.academicRecord[subject] = {marks, grade};
                    }
                }
                students.push_back(student);
            }
        }
    }

    static void displayAll()
    {
        if (students.empty())
        {
            std::cout << "\nNo student records found!\n";
            return;
        }

        printSectionHeader("Student Records");
        std::cout << std::left
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Class"
                  << std::setw(10) << "Roll No."
                  << "\n";
        Student::printDivider(45);

        for (const auto &student : students)
        {
            student.display();
        }
        printDivider(45);
    }

    static void searchByRollNumber(int roll)
    {
        for (const auto &student : students)
        {
            if (student.rollNumber == roll)
            {
                student.displayAcademicRecord();
                return;
            }
        }
        std::cout << "\nStudent with roll number " << roll << " not found!\n";
    }

    static Student* findStudentByRollNumber(int rollNumber) {
        for (auto& student : students) {
            if (student.rollNumber == rollNumber) {
                return &student;
            }
        }
        return nullptr;
    }

    static void updateStudent(Student& updatedStudent) {
        for (auto& student : students) {
            if (student.rollNumber == updatedStudent.rollNumber) {
                student = updatedStudent;
                break;
            }
        }
    }

    static void removeStudent(int rollNumber) {
        students.erase(
            std::remove_if(students.begin(), students.end(),
                [rollNumber](const Student& s) { return s.rollNumber == rollNumber; }),
            students.end()
        );
    }

private:
    static void printSectionHeader(const std::string &title)
    {
        std::cout << "\n=== " << title << " ===\n";
    }

    static void printDivider(int length)
    {
        std::cout << std::string(length, '-') << "\n";
    }
};

std::vector<Student> Student::students;

#endif