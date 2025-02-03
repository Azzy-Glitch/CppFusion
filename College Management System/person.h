#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>

class Person {
protected:
    std::string name;
    static std::string adminPassword;

    void printSectionHeader(const std::string& title) const {
        std::cout << "\n=== " << title << " ===\n";
    }

    void printDivider(int length = 40) const {
        std::cout << std::string(length, '-') << "\n";
    }

public:
    Person(const std::string& n = "") : name(n) {}
    virtual ~Person() {}
    
    virtual void display() const = 0;
    virtual void getData() = 0;
    virtual void saveToFile() const = 0;
    
    static void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    static bool isValidName(const std::string& name) {
        return !name.empty() && name.find_first_of("0123456789") == std::string::npos;
    }

    static void pressToContinue() {
        std::cout << "\nPress Enter to continue...";
        clearInputBuffer();
        std::cin.get();
    }

    static bool authenticateAdmin() {
        std::string inputPass;
        std::cout << "Enter admin password: ";
        std::getline(std::cin, inputPass);
        
        if(inputPass == adminPassword) {
            std::cout << "Authentication successful!\n";
            return true;
        }
        std::cout << "Invalid password!\n";
        return false;
    }

    static void changeAdminPassword() {
        if(!authenticateAdmin()) return;
        
        std::string newPass;
        std::cout << "Enter new admin password: ";
        std::getline(std::cin, newPass);
        adminPassword = newPass;
        std::cout << "Password changed successfully!\n";
    }
};

std::string Person::adminPassword = "2917";

#endif