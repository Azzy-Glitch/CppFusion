#ifndef STAFF_H
#define STAFF_H

#include "Person.h"

class Staff : public Person
{
    std::string department;
    std::string position;
    static std::vector<Staff> staffMembers;

public:
    Staff(const std::string &n = "", const std::string &dept = "",
          const std::string &pos = "")
        : Person(n), department(dept), position(pos) {}

    void display() const override
    {
        std::cout << "Staff Member: " << name << "\nDepartment: " << department
                  << "\nPosition: " << position << "\n\n";
    }

    void getData() override
    {
        std::cout << "Enter staff name: ";
        while (std::getline(std::cin, name) && !isValidName(name))
        {
            std::cout << "Invalid name! Enter again: ";
        }

        std::cout << "Enter department: ";
        std::getline(std::cin, department);

        std::cout << "Enter position: ";
        std::getline(std::cin, position);
    }

    void saveToFile() const override
    {
        std::ofstream file("staff.txt", std::ios::app);
        if (file)
        {
            file << name << "," << department << "," << position << "\n";
        }
    }

    static void loadFromFile()
    {
        staffMembers.clear();
        std::ifstream file("staff.txt");
        std::string line;

        while (std::getline(file, line))
        {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            if (pos1 != std::string::npos && pos2 != std::string::npos)
            {
                std::string name = line.substr(0, pos1);
                std::string dept = line.substr(pos1 + 1, pos2 - pos1 - 1);
                std::string pos = line.substr(pos2 + 1);

                staffMembers.emplace_back(name, dept, pos);
            }
        }
    }

    static void displayAll()
    {
        for (const auto &staff : staffMembers)
        {
            staff.display();
        }
    }

    static void search(const std::string &query)
    {
        for (const auto &staff : staffMembers)
        {
            if (staff.name.find(query) != std::string::npos ||
                staff.department.find(query) != std::string::npos ||
                staff.position.find(query) != std::string::npos)
            {
                staff.display();
            }
        }
    }
};

std::vector<Staff> Staff::staffMembers;

#endif