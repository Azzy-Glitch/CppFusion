#include <iostream>
using namespace std;

int main()
{

    int numArray[5] = {1, 2, 3, 4, 5};

    char charArray[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

    cout << "Integer Array: ";
    for (int i = 0; i < 5; i++)
    {
        cout << numArray[i] << " ";
    }

    cout << "\nCharacter Array: ";
    cout << charArray;

    cout << "\n\nCharacter Array with null terminator: ";
    charArray[5] = 'X';
    cout << charArray;

    return 0;
}