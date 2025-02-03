#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
using namespace std;

// Function prototypes
string getCurrentDateTime();
void playRPS();
void saveRpsScore(int player, int computer);
void showRpsHistory();
void ticTacToeGame();
void saveTttResult(const string &result);
void showTttHistory();
void memoryGame();
void saveMemoryScore(int correct, int incorrect);
void showMemoryHistory();
void viewScoresMenu();

// Global variables
char box[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char turn = 'X';
bool draw = false;

string getCurrentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return string(buf);
}

int main()
{
    int choice;
    do
    {
        system("cls");
        cout << "\t\tG A M E   M E N U" << endl
             << "1. Rock, Paper, Scissors" << endl
             << "2. Tic Tac Toe" << endl
             << "3. Memory Game" << endl
             << "4. View Scores" << endl
             << "5. Exit" << endl
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            playRPS();
            break;
        case 2:
            ticTacToeGame();
            break;
        case 3:
            memoryGame();
            break;
        case 4:
            viewScoresMenu();
            break;
        case 5:
            cout << "Exiting...";
            break;
        default:
            cout << "Invalid choice!";
            Sleep(1000);
        }
    } while (choice != 5);
    return 0;
}

// Score viewing menu
void viewScoresMenu()
{
    int choice;
    do
    {
        system("cls");
        cout << "\t\tV I E W   S C O R E S" << endl
             << "1. Rock Paper Scissors" << endl
             << "2. Tic Tac Toe" << endl
             << "3. Memory Game" << endl
             << "4. Return to Main Menu" << endl
             << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            showRpsHistory();
            break;
        case 2:
            showTttHistory();
            break;
        case 3:
            showMemoryHistory();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice!";
            Sleep(1000);
        }
    } while (true);
}

// Rock Paper Scissors functions
void playRPS()
{
    char playAgain;
    do
    {
        system("cls");
        string choices[3] = {"Rock", "Paper", "Scissors"};
        int player, computer;
        int pScore = 0, cpScore = 0;

        cout << "Best of how many rounds? ";
        int rounds;
        cin >> rounds;

        for (int i = 0; i < rounds; i++)
        {
            system("cls");
            cout << "Round " << i + 1 << "/" << rounds << endl
                 << "1. Rock\n2. Paper\n3. Scissors\nEnter choice: ";
            cin >> player;
            player--; // Adjust to 0-based index

            computer = rand() % 3;

            cout << "\nYou chose: " << choices[player]
                 << "\nComputer chose: " << choices[computer] << endl;

            if (player == computer)
            {
                cout << "Draw!" << endl;
            }
            else if ((player == 0 && computer == 2) ||
                     (player == 1 && computer == 0) ||
                     (player == 2 && computer == 1))
            {
                cout << "You win this round!" << endl;
                pScore++;
            }
            else
            {
                cout << "Computer wins this round!" << endl;
                cpScore++;
            }
            Sleep(2000);
        }

        system("cls");
        cout << "Final Score - You: " << pScore << " | Computer: " << cpScore << endl;
        saveRpsScore(pScore, cpScore);

        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');
}

void saveRpsScore(int player, int computer)
{
    ofstream file("rps_scores.txt", ios::app);
    if (file.is_open())
    {
        file << "Player: " << player << " | Computer: " << computer
             << " | Date: " << getCurrentDateTime() << endl;
        file.close();
    }
}

void showRpsHistory()
{
    system("cls");
    ifstream file("rps_scores.txt");
    cout << "\nRock Paper Scissors History:\n";
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "No scores recorded yet!" << endl;
    }
    system("pause");
}

// Tic Tac Toe functions
void ticTacToeGame()
{
    char playAgain;
    do
    {
        system("cls");
        // Reset board
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                box[i][j] = '1' + i * 3 + j;
        turn = 'X';
        draw = false;

        while (true)
        {
            system("cls");
            cout << "\n\tTic Tac Toe\nPlayer 1 [X]\nPlayer 2 [O]\n\n";
            for (int i = 0; i < 3; i++)
            {
                cout << "\t";
                for (int j = 0; j < 3; j++)
                {
                    cout << box[i][j] << " ";
                    if (j < 2)
                        cout << "| ";
                }
                if (i < 2)
                    cout << "\n\t---------\n";
            }

            int choice;
            cout << "\nPlayer " << (turn == 'X' ? "1" : "2") << "'s turn: ";
            cin >> choice;

            int row = (choice - 1) / 3;
            int col = (choice - 1) % 3;

            if (choice < 1 || choice > 9 || box[row][col] == 'X' || box[row][col] == 'O')
            {
                cout << "Invalid move!";
                Sleep(1000);
                continue;
            }

            box[row][col] = turn;

            // Check win
            bool win = false;
            for (int i = 0; i < 3; i++)
            {
                if ((box[i][0] == turn && box[i][1] == turn && box[i][2] == turn) ||
                    (box[0][i] == turn && box[1][i] == turn && box[2][i] == turn))
                {
                    win = true;
                    break;
                }
            }
            if (!win)
            {
                if ((box[0][0] == turn && box[1][1] == turn && box[2][2] == turn) ||
                    (box[0][2] == turn && box[1][1] == turn && box[2][0] == turn))
                {
                    win = true;
                }
            }

            if (win)
            {
                system("cls");
                cout << "Player " << (turn == 'X' ? "1" : "2") << " wins!";
                saveTttResult("Player " + string(1, turn) + " wins");
                break;
            }

            // Check draw
            bool full = true;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (box[i][j] != 'X' && box[i][j] != 'O')
                        full = false;

            if (full)
            {
                cout << "Game Draw!";
                saveTttResult("Draw");
                break;
            }

            turn = (turn == 'X') ? 'O' : 'X';
        }

        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');
}

void saveTttResult(const string &result)
{
    ofstream file("ttt_scores.txt", ios::app);
    if (file.is_open())
    {
        file << result << " | Date: " << getCurrentDateTime() << endl;
        file.close();
    }
}

void showTttHistory()
{
    system("cls");
    ifstream file("ttt_scores.txt");
    cout << "\nTic Tac Toe History:\n";
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "No scores recorded yet!" << endl;
    }
    system("pause");
}

// Memory Game functions
void memoryGame()
{
    char playAgain;
    do
    {
        system("cls");
        const int LEN = 5;
        int sequence[LEN], input[LEN];

        srand(time(0));
        cout << "Memorize these numbers (5 seconds):\n";
        for (int i = 0; i < LEN; i++)
        {
            sequence[i] = rand() % 100;
            cout << sequence[i] << " ";
        }

        Sleep(5000);
        system("cls");

        cout << "Enter the numbers separated by spaces: ";
        for (int i = 0; i < LEN; i++)
        {
            cin >> input[i];
        }

        int correct = 0;
        for (int i = 0; i < LEN; i++)
        {
            if (sequence[i] == input[i])
                correct++;
        }

        cout << "\nYou got " << correct << "/" << LEN << " correct!";
        saveMemoryScore(correct, LEN - correct);

        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');
}

void saveMemoryScore(int correct, int incorrect)
{
    ofstream file("memory_scores.txt", ios::app);
    if (file.is_open())
    {
        file << "Correct: " << correct << " | Incorrect: " << incorrect
             << " | Date: " << getCurrentDateTime() << endl;
        file.close();
    }
}

void showMemoryHistory()
{
    system("cls");
    ifstream file("memory_scores.txt");
    cout << "\nMemory Game History:\n";
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "No scores recorded yet!" << endl;
    }
    system("pause");
}