#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;

struct Point
{
    int x, y;
};

struct Snake
{
    Point body[1000]; // Increased for larger arenas
    int length;
    char direction;
};

struct Food
{
    Point pos;
};

int width, height; // Will be set at runtime
Snake snake;
Food food;
int score = 0;
int highScore = 0;
HANDLE console;
CHAR_INFO* buffer = nullptr;
COORD bufferSize, bufferCoord;
SMALL_RECT writeRegion;

void loadHighScore()
{
    ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
}

void saveHighScore()
{
    if (score > highScore)
    {
        ofstream file("highscore.txt");
        file << score;
        file.close();
    }
}

void setupConsole()
{
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console dimensions
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left - 2;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top - 3;

    // Set minimum dimensions
    if (width < 20) width = 20;
    if (height < 10) height = 10;

    // Initialize double buffer
    bufferSize = {static_cast<SHORT>(width + 2), static_cast<SHORT>(height + 3)};
    buffer = new CHAR_INFO[bufferSize.X * bufferSize.Y];
    bufferCoord = {0, 0};
    writeRegion = {0, 0, static_cast<SHORT>(width + 1), static_cast<SHORT>(height + 2)};

    // Hide cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void setupGame()
{
    snake.length = 1;
    snake.body[0] = {width / 2, height / 2};
    snake.direction = 'R';
    food.pos = {rand() % width, rand() % height};
    loadHighScore();
}

void draw()
{
    // Clear buffer
    for (int i = 0; i < bufferSize.X * bufferSize.Y; ++i)
    {
        buffer[i].Char.UnicodeChar = ' ';
        buffer[i].Attributes = 7; // Default color
    }

    // Draw borders
    for (int x = 0; x <= width + 1; x++)
    {
        // Top border
        buffer[x].Char.UnicodeChar = '#';
        buffer[x].Attributes = 10; // Green

        // Bottom border
        int bottomOffset = (height + 2) * bufferSize.X;
        buffer[bottomOffset + x].Char.UnicodeChar = '#';
        buffer[bottomOffset + x].Attributes = 10;
    }

    for (int y = 0; y <= height + 1; y++)
    {
        // Left border
        int leftOffset = y * bufferSize.X;
        buffer[leftOffset].Char.UnicodeChar = '#';
        buffer[leftOffset].Attributes = 10;

        // Right border
        int rightOffset = leftOffset + width + 1;
        buffer[rightOffset].Char.UnicodeChar = '#';
        buffer[rightOffset].Attributes = 10;
    }

    // Draw food
    int foodOffset = (food.pos.y + 1) * bufferSize.X + (food.pos.x + 1);
    buffer[foodOffset].Char.UnicodeChar = '@';
    buffer[foodOffset].Attributes = 12; // Red

    // Draw snake
    for (int i = 0; i < snake.length; i++)
    {
        int snakeOffset = (snake.body[i].y + 1) * bufferSize.X + (snake.body[i].x + 1);
        buffer[snakeOffset].Char.UnicodeChar = (i == 0) ? 'O' : 'o';
        buffer[snakeOffset].Attributes = (i == 0) ? 11 : 9; // Head: cyan, Body: blue
    }

    // Draw score
    string scoreStr = "Score: " + to_string(score) + "   High Score: " + to_string(highScore);
    int scoreOffset = (height + 2) * bufferSize.X + 1;
    for (int i = 0; i < scoreStr.length(); i++)
    {
        if (scoreOffset + i < bufferSize.X * bufferSize.Y)
        {
            buffer[scoreOffset + i].Char.UnicodeChar = scoreStr[i];
            buffer[scoreOffset + i].Attributes = 14; // Yellow
        }
    }

    // Write buffer to console
    WriteConsoleOutput(console, buffer, bufferSize, bufferCoord, &writeRegion);
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
        case 'w':
            if (snake.direction != 'D')
                snake.direction = 'U';
            break;
        case 's':
            if (snake.direction != 'U')
                snake.direction = 'D';
            break;
        case 'a':
            if (snake.direction != 'R')
                snake.direction = 'L';
            break;
        case 'd':
            if (snake.direction != 'L')
                snake.direction = 'R';
            break;
        }
    }
}

bool collision()
{
    Point head = snake.body[0];

    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
        return true;

    for (int i = 1; i < snake.length; i++)
    {
        if (snake.body[i].x == head.x && snake.body[i].y == head.y)
            return true;
    }

    return false;
}

void logic()
{
    Point prev = snake.body[0];
    Point temp;

    switch (snake.direction)
    {
    case 'U':
        snake.body[0].y--;
        break;
    case 'D':
        snake.body[0].y++;
        break;
    case 'L':
        snake.body[0].x--;
        break;
    case 'R':
        snake.body[0].x++;
        break;
    }

    for (int i = 1; i < snake.length; i++)
    {
        temp = snake.body[i];
        snake.body[i] = prev;
        prev = temp;
    }

    if (snake.body[0].x == food.pos.x && snake.body[0].y == food.pos.y)
    {
        snake.length++;
        score += 10;
        food.pos = {rand() % width, rand() % height};
    }
}

void showStartScreen()
{
    system("cls");
    cout << "\n\n\t  SNAKE GAME\n";
    cout << "\t-----------------\n";
    cout << "\tPress ENTER to start\n";
    cout << "\tUse WASD to control\n\n";

    while (true)
    {
        if (_kbhit() && _getch() == '\r') // Enter key
            break;
        Sleep(50);
    }
}

int main()
{
    setupConsole();
    showStartScreen();
    setupGame();

    while (true)
    {
        draw();
        input();
        logic();

        if (collision())
        {
            saveHighScore();

            // Show game over message
            system("cls");
            cout << "\n\n\tGAME OVER!\n";
            cout << "\tFinal Score: " << score << endl;
            cout << "\tHigh Score: " << highScore << endl << endl;
            break;
        }

        Sleep(100);
    }

    delete[] buffer;
    return 0;
}
