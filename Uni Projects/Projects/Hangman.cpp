#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_TRIES = 6;
const int MAX_WORD_LENGTH = 15;
const int MAX_GUESSED_LETTERS = 26;

void initializeGame(char secretWord[], char displayWord[], char guessedLetters[]);
void drawHangman(int incorrectGuesses);
bool updateDisplayWord(char secretWord[], char displayWord[], char guess);
void showGameState(char displayWord[], char guessedLetters[], int incorrectGuesses);
bool isGameWon(char secretWord[], char displayWord[]);

int main()
{
    srand(time(0));

    char wordList[][MAX_WORD_LENGTH] = {
        "programming",
        "algorithm",
        "variable",
        "function",
        "pointer",
        "array"};

    char secretWord[MAX_WORD_LENGTH];
    char displayWord[MAX_WORD_LENGTH];
    char guessedLetters[MAX_GUESSED_LETTERS] = {0};
    int incorrectGuesses = 0;
    int totalWords = sizeof(wordList) / sizeof(wordList[0]);

    // Select random word
    strcpy(secretWord, wordList[rand() % totalWords]);

    initializeGame(secretWord, displayWord, guessedLetters);

    while (incorrectGuesses < MAX_TRIES)
    {
        showGameState(displayWord, guessedLetters, incorrectGuesses);

        char guess;
        cout << "\nEnter a letter: ";
        cin >> guess;
        guess = tolower(guess);

        if (!isalpha(guess))
        {
            cout << "Invalid input! Please enter a letter.\n";
            continue;
        }

        bool alreadyGuessed = false;
        for (int i = 0; i < MAX_GUESSED_LETTERS; i++)
        {
            if (guessedLetters[i] == guess)
            {
                alreadyGuessed = true;
                break;
            }
        }

        if (alreadyGuessed)
        {
            cout << "You already guessed that letter!\n";
            continue;
        }

        for (int i = 0; i < MAX_GUESSED_LETTERS; i++)
        {
            if (guessedLetters[i] == 0)
            {
                guessedLetters[i] = guess;
                break;
            }
        }

        if (!updateDisplayWord(secretWord, displayWord, guess))
        {
            incorrectGuesses++;
            cout << "Incorrect guess! ";
        }

        if (isGameWon(secretWord, displayWord))
        {
            showGameState(displayWord, guessedLetters, incorrectGuesses);
            cout << "\nCongratulations! You won!\n";
            cout << "The word was: " << secretWord << endl;
            return 0;
        }
    }

    drawHangman(incorrectGuesses);
    cout << "\nGame Over! You lost!\n";
    cout << "The word was: " << secretWord << endl;

    return 0;
}

void initializeGame(char secretWord[], char displayWord[], char guessedLetters[])
{
    int length = strlen(secretWord);
    for (int i = 0; i < length; i++)
    {
        displayWord[i] = '_';
    }
    displayWord[length] = '\0';

    memset(guessedLetters, 0, MAX_GUESSED_LETTERS);
}

bool updateDisplayWord(char secretWord[], char displayWord[], char guess)
{
    bool found = false;
    int length = strlen(secretWord);

    for (int i = 0; i < length; i++)
    {
        if (tolower(secretWord[i]) == guess)
        {
            displayWord[i] = secretWord[i];
            found = true;
        }
    }
    return found;
}

bool isGameWon(char secretWord[], char displayWord[])
{
    int length = strlen(secretWord);
    for (int i = 0; i < length; i++)
    {
        if (displayWord[i] == '_')
            return false;
    }
    return true;
}

void showGameState(char displayWord[], char guessedLetters[], int incorrectGuesses)
{
    system("cls||clear");

    cout << "HANGMAN GAME\n";
    cout << "============\n";
    drawHangman(incorrectGuesses);

    cout << "\nWord: ";
    for (int i = 0; displayWord[i] != '\0'; i++)
    {
        cout << displayWord[i] << " ";
    }

    cout << "\n\nGuessed letters: ";
    for (int i = 0; i < MAX_GUESSED_LETTERS; i++)
    {
        if (guessedLetters[i] != 0)
        {
            cout << guessedLetters[i] << " ";
        }
    }

    cout << "\n\nIncorrect guesses remaining: "
         << MAX_TRIES - incorrectGuesses << endl;
}

void drawHangman(int incorrectGuesses)
{
    cout << "\n  -----\n  |   |\n";

    switch (incorrectGuesses)
    {
    case 6:
        cout << "  O   |\n /|\\  |\n / \\  |\n";
        break;
    case 5:
        cout << "  O   |\n /|\\  |\n /    |\n";
        break;
    case 4:
        cout << "  O   |\n /|\\  |\n      |\n";
        break;
    case 3:
        cout << "  O   |\n /|   |\n      |\n";
        break;
    case 2:
        cout << "  O   |\n  |   |\n      |\n";
        break;
    case 1:
        cout << "  O   |\n      |\n      |\n";
        break;
    default:
        cout << "      |\n      |\n      |\n";
    }

    cout << "      |\n=========\n";
}