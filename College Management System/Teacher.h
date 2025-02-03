#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"

class Teacher : public Person
{
    std::string subject;
    double salary;
    static std::vector<Teacher> teachers;

public:
    Teacher(const std::string &n = "", const std::string &subj = "", double sal = 0)
        : Person(n), subject(subj), salary(sal) {}

    void display() const override
    {
        std::cout << "Teacher: " << name << "\nSubject: " << subject
                  << "\nSalary: $" << salary << "\n\n";
    }

    void getData() override
    {
        std::cout << "Enter teacher name: ";
        while (std::getline(std::cin, name) && !isValidName(name))
        {
            std::cout << "Invalid name! Enter again: ";
        }

        std::cout << "Enter subject: ";
        std::getline(std::cin, subject);

        std::cout << "Enter salary: ";
        while (!(std::cin >> salary) || salary <= 0)
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
            file << name << "," << subject << "," << salary << "\n";
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
            if (teacher.name.find(query) != std::string::npos ||
                teacher.subject.find(query) != std::string::npos)
            {
                teacher.display();
            }
        }
    }
};

std::vector<Teacher> Teacher::teachers;

#endif