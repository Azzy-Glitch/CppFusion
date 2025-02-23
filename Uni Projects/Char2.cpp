#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char source[50], destination[50], another[50];

    cout << "Enter first string: ";
    cin.getline(source, 50);

    strcpy(destination, source);
    cout << "Copied string: " << destination << endl;

    cout << "Length: " << strlen(source) << endl;

    strcat(destination, " Student");
    cout << "After concatenation: " << destination << endl;

    cout << "Enter another string to compare: ";
    cin.getline(another, 50);

    if (strcmp(source, another) == 0)
    {
        cout << "Same strings!" << endl;
    }
    else
    {
        cout << "Different strings!" << endl;
    }

    return 0;
}
