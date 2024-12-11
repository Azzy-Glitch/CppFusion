#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    int User_Choice, Computer_Choice;

    cout << "Enter your choice (1 for rock, 2 for paper, 3 for scissors): ";
    cin >> User_Choice;

    srand(time(0));
    Computer_Choice = rand() % 3 + 1;

    if (User_Choice == Computer_Choice)
    {
        cout << "It's a tie!\n";
    }
    else if (User_Choice == 1 && Computer_Choice == 2)
    {
        cout << "Paper covers rock. Computer wins!\n";
    }
    else if (User_Choice == 1 && Computer_Choice == 3)
    {
        cout << "Rock smashes scissors. You win!\n";
    }
    else if (User_Choice == 2 && Computer_Choice == 1)
    {
        cout << "Paper covers rock. You win!\n";
    }
    else if (User_Choice == 2 && Computer_Choice == 3)
    {
        cout << "Scissors cut paper. Computer wins!\n";
    }
    else if (User_Choice == 3 && Computer_Choice == 1)
    {
        cout << "Rock smashes scissors. Computer wins!\n";
    }
    else if (User_Choice == 3 && Computer_Choice == 2)
    {
        cout << "Scissors cut paper. You win!\n";
    }
    else
    {
        cout << "Invalid choice! Please enter 1, 2, or 3.\n";
    }
    return 0;
}