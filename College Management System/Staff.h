#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <fstream>
#include <algorithm>

class Staff : public Person
{
    std::string departmentName;
    std::string positionTitle;
public:
    static std::vector<Staff> staffMembers;

    Staff(const std::string &n = "", const std::string &dept = "",
          const std::string &pos = "")
        : Person(n), departmentName(dept), positionTitle(pos) {}

    void display() const override
    {
        std::cout << "Staff Member: " << personName << "\nDepartment: " << departmentName
                  << "\nPosition: " << positionTitle << "\n\n";
    }

    void getData() override
    {
        std::cout << "Enter staff name: ";
        while (std::getline(std::cin, personName) && !isValidName(personName))
        {
            std::cout << "Invalid name! Enter again: ";
        }

        std::cout << "Enter department: ";
        std::getline(std::cin, departmentName);

        std::cout << "Enter position: ";
        std::getline(std::cin, positionTitle);
    }

    void saveToFile() const override
    {
        std::ofstream file("staff.txt", std::ios::app);
        if (file)
        {
            file << personName << "," << departmentName << "," << positionTitle << "\n";
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
            if (staff.personName.find(query) != std::string::npos ||
                staff.departmentName.find(query) != std::string::npos ||
                staff.positionTitle.find(query) != std::string::npos)
            {
                staff.display();
            }
        }
    }

    static Staff* findStaffByName(const std::string& name) {
        for (auto& staff : staffMembers) {
            if (staff.personName == name) {
                return &staff;
            }
        }
        return nullptr;
    }

    static void updateStaff(Staff& updatedStaff) {
        for (auto& staff : staffMembers) {
            if (staff.personName == updatedStaff.personName) {
                staff = updatedStaff;
                break;
            }
        }
    }

    static void removeStaff(const std::string& name) {
        staffMembers.erase(
            std::remove_if(staffMembers.begin(), staffMembers.end(),
                [name](const Staff& s) { return s.personName == name; }),
            staffMembers.end()
        );
    }
};

std::vector<Staff> Staff::staffMembers;

#endif