#include <iostream>

using namespace std;

int main()
{
    int Num1, Num2;

    cout << "Enter first number: " << endl;
    cin >> Num1;
    cout << "Enter second number: " << endl;
    cin >> Num2;

    int Sum = Num1 + Num2;

    cout << "Sum " << Sum << endl;

    int Num3;

    cout << "Enter another number " << endl;
    cin >> Num3;

    int product = Sum * Num3;

    cout <<"Product = "<<product;

    return 0;
}