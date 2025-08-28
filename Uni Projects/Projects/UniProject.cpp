#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Game {
    int secretNumber;
    int userGuess;
    int attempts;
};

struct RockPaperScissorGame {
    int PlayerChoice;
    int ComputerChoice;
};

void StartSecretNumberGame(Game &g) {
    srand(time(0));
    g.secretNumber = rand() % 100 + 1;
    g.attempts = 0;

    cout << "\n SECRET NUMBER GAME \n";
    cout << "I've picked a number between 1 and 100.\n";
    cout << "Try to guess it!\n\n";
}

void getUserGuess(Game &g) {
    cout << " Enter your guess (1 - 100): ";
    cin >> g.userGuess;
    g.attempts++;
}

bool checkGuess(Game g) {
    if (g.userGuess < g.secretNumber) {
        cout << " Too low!\n\n";
        return false;
    } else if (g.userGuess > g.secretNumber) {
        cout << " Too high!\n\n";
        return false;
    } else {
        cout << " Correct! You guessed it in " << g.attempts << " attempts!\n";
        return true;
    }
}

void PlaySecretNumberGame() {
    Game game;
    StartSecretNumberGame(game);

    bool correct = false;
    while (!correct) {
        getUserGuess(game);
        correct = checkGuess(game);
    }
}

void ShowRockPaperScissorGameMenu() {
    cout << "\n ROCK, PAPER, SCISSORS \n";
    cout << "1. Rock \n";
    cout << "2. Paper \n";
    cout << "3. Scissors \n";
    cout << "Choose (1-3): ";
}

void getPlayerChoice(RockPaperScissorGame &g) {
    cin >> g.PlayerChoice;
}

void getComputerChoice(RockPaperScissorGame &g) {
    srand(time(0));
    g.ComputerChoice = rand() % 3 + 1;
}

void decideRockPaperScissorGameWinner(RockPaperScissorGame g) {
    cout << " You chose: " << g.PlayerChoice << ",  Computer chose: " << g.ComputerChoice << endl;

    if (g.PlayerChoice == g.ComputerChoice) {
        cout << " It's a draw!\n";
    } else if ((g.PlayerChoice == 1 && g.ComputerChoice == 3) ||
               (g.PlayerChoice == 2 && g.ComputerChoice == 1) ||
               (g.PlayerChoice == 3 && g.ComputerChoice == 2)) {
        cout << " You win!\n";
    } else {
        cout << " You lose!\n";
    }
}

void PlayRockPaperScissorGame() {
    RockPaperScissorGame game;
    ShowRockPaperScissorGameMenu();
    getPlayerChoice(game);
    getComputerChoice(game);
    decideRockPaperScissorGameWinner(game);
}

void showMainMenu() {
    cout << "\n=============================\n";
    cout << " WELCOME TO MINI GAME HUB \n";
    cout << "=============================\n";
    cout << "1. Secret Number Game \n";
    cout << "2. Rock Paper Scissors \n";
    cout << "3. Exit \n";
    cout << "Choose an option (1-3): ";
}

int main() {
    srand(time(0));
    int choice;
    char again;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                PlaySecretNumberGame();
                break;
            case 2:
                PlayRockPaperScissorGame();
                break;
            case 3:
                cout << " Exiting the Game Hub. Goodbye!\n";
                return 0;
            default:
                cout << " Invalid option. Try again.\n";
        }

        cout << "\n Do you want to return to the main menu? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    cout << " Thanks for playing!\n";
    return 0;
}
