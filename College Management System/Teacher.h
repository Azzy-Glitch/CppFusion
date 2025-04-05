#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"
#include <fstream>
#include <algorithm>

class Teacher : public Person
{
    std::string teachingSubject;
    double teacherSalary;
public:
    static std::vector<Teacher> teachers;

    Teacher(const std::string &n = "", const std::string &subj = "", double sal = 0)
        : Person(n), teachingSubject(subj), teacherSalary(sal) {}

    void display() const override
    {
        std::cout << "Teacher: " << personName << "\nSubject: " << teachingSubject
                  << "\nSalary: $" << teacherSalary << "\n\n";
    }

    void getData() override
    {
        std::cout << "Enter teacher name: ";
        while (std::getline(std::cin, personName) && !isValidName(personName))
        {
            std::cout << "Invalid name! Enter again: ";
        }

        std::cout << "Enter subject: ";
        std::getline(std::cin, teachingSubject);

        std::cout << "Enter salary: ";
        while (!(std::cin >> teacherSalary) || teacherSalary <= 0)
        {
            std::cout << "Invalid input! Enter positive number: ";
            clearInputBuffer();
        }
        clearInputBuffer();
    }

    void saveToFile() const override
    {
        std::ofstream file("teachers.txt", std::ios::app);
        if (file)
        {
            file << personName << "," << teachingSubject << "," << teacherSalary << "\n";
        }
    }

    static void loadFromFile()
    {
        teachers.clear();
        std::ifstream file("teachers.txt");
        std::string line;

        while (std::getline(file, line))
        {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            if (pos1 != std::string::npos && pos2 != std::string::npos)
            {
                std::string name = line.substr(0, pos1);
                std::string subj = line.substr(pos1 + 1, pos2 - pos1 - 1);
                double sal = std::stod(line.substr(pos2 + 1));

                teachers.emplace_back(name, subj, sal);
            }
        }
    }

    static void displayAll()
    {
        for (const auto &teacher : teachers)
        {
            teacher.display();
        }
    }

    static void search(const std::string &query)
    {
        for (const auto &teacher : teachers)
        {
            if (teacher.personName.find(query) != std::string::npos ||
                teacher.teachingSubject.find(query) != std::string::npos)
            {
                teacher.display();
            }
        }
    }

    static Teacher* findTeacherByName(const std::string& name) {
        for (auto& teacher : teachers) {
            if (teacher.personName == name) {
                return &teacher;
            }
        }
        return nullptr;
    }

    static void updateTeacher(Teacher& updatedTeacher) {
        for (auto& teacher : teachers) {
            if (teacher.personName == updatedTeacher.personName) {
                teacher = updatedTeacher;
                break;
            }
        }
    }

    static void removeTeacher(const std::string& name) {
        teachers.erase(
            std::remove_if(teachers.begin(), teachers.end(),
                [name](const Teacher& t) { return t.personName == name; }),
            teachers.end()
        );
    }
};

std::vector<Teacher> Teacher::teachers;

#endif