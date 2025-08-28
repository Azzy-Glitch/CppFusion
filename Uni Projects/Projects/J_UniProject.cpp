#include <iostream>
using namespace std;

struct Book {
    int serial;
    string name;
    float price;
    int quantity;
};

struct Student {
    int id;
    string name;
    string section;
};

int searchBookByName(Book books[], int size, string searchBook, int &index) {
    for (int i = 0; i < size; i++) {
        if (books[i].name == searchBook) {
            index = i;
            if (books[i].quantity > 0)
                return 1;
            else
                return 2;
        }
    }
    return 0;
}

Student inputStudent() {
    Student s;
    cout << "\nEnter student ID: ";
    cin >> s.id;
    cout << "Enter student name: ";
    cin >> s.name;
    cout << "Enter student section: ";
    cin >> s.section;
    return s;
}

void issueBook(Book &b, Student s) {
    b.quantity--;
    cout << "\n--- Book Issued ---\n";
    cout << "Book: " << b.name << " (Rs. " << b.price << ")\n";
    cout << "Remaining Quantity: " << b.quantity << endl;
    cout << "Issued To: " << s.name << " | ID: " << s.id << " | Section: " << s.section << endl;
}

int main() {

    Book books[3] = {
        {1, "C++", 500, 2},
        {2, "Math", 400, 1},
        {3, "English", 300, 1}
    };

    char choice;
    do {
        string searchName;
        cout << "\nEnter book name to issue: ";
        cin >> searchName;

        int index;
        int status = searchBookByName(books, 3, searchName, index);

        if (status == 0) {
            cout << " Book not found!\n";
        } else if (status == 2) {
            cout << " Book is out of stock!\n";
        } else {
            Student s = inputStudent();
            issueBook(books[index], s);
        }

        cout << "\nDo you want to issue another book? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n All book issuing done. Goodbye!\n";
    return 0;
}
