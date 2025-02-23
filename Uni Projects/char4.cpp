#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char patientName[] = "M. Rehman";
    int length = strlen(patientName);
    cout<<length;
    cout << "Using for loop: ";
    for (int i = 0; i < length; i++)
    {
        cout << patientName[i];
    }

    cout << "\nUsing while loop: ";
    int j = 0;
    while (patientName[j] != '\0')
    {
        cout << patientName[j];
        j++;
    }

    cout << "\nUsing do-while loop: ";
    int k = 0;
    do
    {
        cout << patientName[k];
        k++;
    } while (patientName[k] != '\0');

    return 0;
}