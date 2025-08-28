#include <iostream>
#include <string>
using namespace std;

string name, ID, pass, gender, check_in;
int phone_no, clients, room;
float CNIC, salary, client_fee, revenue, expenditure, profit, total;

void Menu();
void addfood();
void add_waiter();
void income();
void book();

// -------------------- Add Food --------------------
void addfood() {
    string f_name;
    int price, selection;
    int count = 0, total_price = 0;

    cout << "\n      Enter Food Details That You Want to Add\n";
    cout << "Enter the Name of the food: ";
    cin.ignore();
    getline(cin, f_name);
    cout << "Enter the Price of the item: ";
    cin >> price;

    count++;
    total_price += price;

    cout << "Do you want to add more Items? (1 = YES, 0 = NO): ";
    cin >> selection;

    while (selection == 1) {
        cout << "Enter Another food: ";
        cin.ignore();
        getline(cin, f_name);
        cout << "Enter the Price of the item: ";
        cin >> price;

        count++;
        total_price += price;

        cout << "Do you want to add more Items? (1 = YES, 0 = NO): ";
        cin >> selection;
    }

    cout << "\nNumber of Foods: " << count << endl;
    cout << "Total Food Bill: " << total_price << endl;
}

// -------------------- Add Waiter --------------------
void add_waiter() {
    string waiter_name;
    float waiter_salary;
    int choice = 1;

    while (choice == 1) {
        cout << "Enter the Name of waiter: ";
        cin.ignore();
        getline(cin, waiter_name);
        cout << "Enter the Salary of waiter: ";
        cin >> waiter_salary;

        cout << "Do you want to add more waiters? (1 = YES, 0 = NO): ";
        cin >> choice;

        if (choice == 0) {
            cout << "\nDetails of waiters are saved!\n";
        }
    }
}

// -------------------- Income Calculation --------------------
void income() {
    int total_fee = 0;

    cout << "Enter the number of Clients: ";
    cin >> clients;

    for (int i = 1; i <= clients; i++) {
        cout << "Enter the fee of client " << i << ": ";
        cin >> client_fee;
        total_fee += client_fee;
    }

    cout << "Enter the Total expenditure: ";
    cin >> expenditure;

    int hotel_income = total_fee - expenditure;
    cout << "\nIncome: " << hotel_income << endl;
}

// -------------------- Room Booking --------------------
void book() {
    float fee = 10000;
    cout << "Enter the number of rooms you want: ";
    cin >> room;
    cout << "The fee of 1 room is: " << fee << endl;

    total = room * fee;
    cout << "Total fee is: " << total << endl;

    int ch;
    cout << "Press 1 to confirm booking, 0 to discard: ";
    cin >> ch;

    string feedback;
    if (ch == 1) {
        cout << "When do you want to check in? Enter the date: ";
        cin >> check_in;
        cout << room << " Rooms have been reserved for you.\n";
    } else {
        cin.ignore();
        cout << "Sorry! Please share feedback to help us improve:\nFeedback: ";
        getline(cin, feedback);
        cout << "Thank you! We will work on improving our services.\n";
    }
}

// -------------------- Menu for Guest --------------------
void Menu() {
    cout << "\nDetail Of Food:\n"
         << "1) Biryani 210\n2) Haleem 120\n3) White Handi 800\n"
         << "4) Pizza 1200\n5) Burger 180\n6) Shwarma 120\n7) Sajji 2000\n";
}

// -------------------- Main Function --------------------
int main() {
    int x;
    do {
        int choice;
        cout << "-------------------------------------------------*-\n\n";
        cout << "Enter as:\n1- Guest\n2- Admin\n\n";
        cout << "-------------------------------------------------*-\n\n";
        cin >> choice;

        if (choice == 1) {   // Guest
            cout << "\n---------------- Guest Registration ----------------\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter 14 digit CNIC Number: ";
            cin >> CNIC;

            cout << "Phone number: ";
            cin >> phone_no;

            cout << "Gender: ";
            cin >> gender;

            cout << "\nDetail Saved!\n";

            cout << "1- Menu\n2- Book\nChoice: ";
            int ch;
            cin >> ch;

            if (ch == 1) {
                Menu();
                addfood();
            } else if (ch == 2) {
                book();
            }

        } else {  // Admin
            cout << "\n---------------- Admin Login ----------------\n";
            for (int i = 0; i < 1000; i++) {
                if (i != 0)
                    cout << "Incorrect ID or Password! Try again.\n";

                cout << "Enter ID: ";
                cin >> ID;
                cout << "Enter Password: ";
                cin >> pass;

                if (ID == "./cbt" && pass == "cbt") break;
            }

            cout << "\n1- Food\n2- Waiter\n3- Income\nChoice: ";
            int sel;
            cin >> sel;

            if (sel == 1) addfood();
            else if (sel == 2) add_waiter();
            else if (sel == 3) income();
        }

        cout << "\nDo you want to go to main menu? (1 = YES, 0 = NO): ";
        cin >> x;

    } while (x == 1);

    cout << "\nProgram Ended!\nThanks for choosing our hotel!\n";
    return 0;
}