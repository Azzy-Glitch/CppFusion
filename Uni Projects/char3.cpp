#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char correctUsername[10] = "Doctor";
    char correctPassword[10] = "2917";

    char inputUser[10], inputPass[10];
    int attempts = 3;

    while (attempts > 0)
    {
        cout << "\nHospital Login (Attempts left: " << attempts << ")\n";
        cout << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        if (strcmp(inputUser, correctUsername) == 0 &&
            strcmp(inputPass, correctPassword) == 0)
        {
            cout << "Access granted! Welcome to patient records.\n";
            return 0;
        }
        else
        {
            cout << "Invalid credentials!\n";
            attempts--;
        }
    }

    cout << "System locked! Contact administrator.";
    return 0;
}