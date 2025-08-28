#include <iostream>
#include <string>

using namespace std;

// Struct for Question
struct Question {
    string paperName;
    string questionToAttemp;
    bool selectOption = false;
    bool rightAnswer = true;
    int totalMarks = 0;
};

// Struct for Student
struct Student {
    string name;
    int age;
    string rollNo;
    string password;
    Question attemptedPaper[3];
};

// Struct for Teacher
struct Teacher {
    string name;
    string userName;
    string password;
    string subjects[5];
    string papers[10];
};

void pressKeyToContinue() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void registerStudent(Student students[], int& numStudents) {
    cout << "Enter student name: ";
    cin >> students[numStudents].name;
    cout << "Enter student age: ";
    cin >> students[numStudents].age;
    cout << "Enter student roll number: ";
    cin >> students[numStudents].rollNo;
    cout << "Set student password: ";
    cin >> students[numStudents].password;

    numStudents++;
    cout << "Student registered successfully!" << endl;
    pressKeyToContinue();
}

bool loginStudent(Student students[], int numStudents) {
    string rollNo, password;
    cout << "Enter student roll number: ";
    cin >> rollNo;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNo == rollNo && students[i].password == password) {
            cout << "Login successful! Welcome, " << students[i].name << "!" << endl;
            pressKeyToContinue();
            return true;
        }
    }

    cout << "Invalid roll number or password. Login failed." << endl;
    pressKeyToContinue();
    return false;
}

void questionnaire(Student& student, const string& paperToCheck) {
    char input;
    Question questions[3];

    questions[0].paperName = "math";
    questions[0].questionToAttemp = "What is 2 + 2 = 4? (y/n): ";
    questions[0].rightAnswer = true;

    questions[1].paperName = "physics";
    questions[1].questionToAttemp = "Is V = IR the Ohm's Law formula? (y/n): ";
    questions[1].rightAnswer = true;

    questions[2].paperName = "computer";
    questions[2].questionToAttemp = "Is C++ a programming language? (y/n): ";
    questions[2].rightAnswer = true;

    for (int i = 0; i < 3; i++) {
        student.attemptedPaper[i] = questions[i];
    }

    for (int i = 0; i < 3; i++) {
        if (student.attemptedPaper[i].paperName == paperToCheck) {
            cout << student.attemptedPaper[i].questionToAttemp;
            cin >> input;
            student.attemptedPaper[i].selectOption = (input == 'y' || input == 'Y');
            student.attemptedPaper[i].totalMarks = (student.attemptedPaper[i].selectOption == student.attemptedPaper[i].rightAnswer) ? 1 : 0;
            cout << "\nPaper Attempted successfully.\n";
            break;
        }
    }

    pressKeyToContinue();
}

void PaperAttempt(Student& student, Teacher teachers[]) {
    string paperName;
    cout << "Enter the name of the paper you want to attempt: ";
    cin >> paperName;

    bool paperFound = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (teachers[i].papers[j] == paperName) {
                paperFound = true;
                questionnaire(student, paperName);
                return;
            }
        }
    }

    if (!paperFound) {
        cout << "Paper not found. Please check the paper name and try again." << endl;
        pressKeyToContinue();
    }
}

void viewResult(Student& student) {
    string paperName;
    cout << "Enter the name of the paper you want to view the result for: ";
    cin >> paperName;

    bool paperFound = false;
    for (int i = 0; i < 3; i++) {
        if (student.attemptedPaper[i].paperName == paperName) {
            cout << "Result for " << paperName << ": " << student.attemptedPaper[i].totalMarks << " marks\n";
            paperFound = true;
            break;
        }
    }

    if (!paperFound) {
        cout << "Paper not found or result not available." << endl;
    }

    pressKeyToContinue();
}

void updateStudentData(Student& student) {
    int choice;
    cout << "1. Update Name\n2. Update Age\n3. Update Password\nEnter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: cout << "Enter new name: "; cin >> student.name; break;
        case 2: cout << "Enter new age: "; cin >> student.age; break;
        case 3: cout << "Enter new password: "; cin >> student.password; break;
        default: cout << "Invalid choice.\n"; break;
    }

    cout << "Update successful!\n";
    pressKeyToContinue();
}

void registerTeacher(Teacher teachers[], int& numTeachers) {
    cout << "Enter teacher name: ";
    cin >> teachers[numTeachers].name;
    cout << "Enter username: ";
    cin >> teachers[numTeachers].userName;
    cout << "Enter password: ";
    cin >> teachers[numTeachers].password;

    numTeachers++;
    cout << "Teacher registered successfully!" << endl;
    pressKeyToContinue();
}

bool loginTeacher(Teacher teachers[], int numTeachers) {
    string userName, password;
    cout << "Enter username: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < numTeachers; i++) {
        if (teachers[i].userName == userName && teachers[i].password == password) {
            cout << "Login successful. Welcome, " << teachers[i].name << "!" << endl;
            pressKeyToContinue();
            return true;
        }
    }

    cout << "Invalid username or password." << endl;
    pressKeyToContinue();
    return false;
}

void addSubject(Teacher& teacher) {
    string subject;
    cout << "Enter subject to add: ";
    cin >> subject;

    for (int i = 0; i < 5; i++) {
        if (teacher.subjects[i] == subject) {
            cout << "Subject already exists.\n";
            pressKeyToContinue();
            return;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (teacher.subjects[i].empty()) {
            teacher.subjects[i] = subject;
            cout << "Subject added.\n";
            pressKeyToContinue();
            return;
        }
    }

    cout << "Subject limit reached.\n";
    pressKeyToContinue();
}

void addPaper(Teacher& teacher) {
    string paper;
    cout << "Enter paper name to add: ";
    cin >> paper;

    for (int i = 0; i < 10; i++) {
        if (teacher.papers[i] == paper) {
            cout << "Paper already exists.\n";
            pressKeyToContinue();
            return;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (teacher.papers[i].empty()) {
            teacher.papers[i] = paper;
            cout << "Paper added.\n";
            pressKeyToContinue();
            return;
        }
    }

    cout << "Paper limit reached.\n";
    pressKeyToContinue();
}

void viewAllStudents(Student students[], int numStudents) {
    cout << "Students List:\n";
    for (int i = 0; i < numStudents; i++) {
        cout << "Name: " << students[i].name << "\nAge: " << students[i].age << "\nRoll No: " << students[i].rollNo << "\n---\n";
    }
    pressKeyToContinue();
}

void checkPapers(Teacher& teacher, Student students[], int numStudents) {
    string paperName;
    cout << "Enter paper name to check: ";
    cin >> paperName;

    bool found = false;
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < 3; j++) {
            if (students[i].attemptedPaper[j].paperName == paperName) {
                cout << "Student: " << students[i].name << ", Marks: " << students[i].attemptedPaper[j].totalMarks << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "No submissions found for that paper.\n";
    }

    pressKeyToContinue();
}

void viewTeacherInfo(Teacher teacher) {
    cout << "Teacher: " << teacher.name << "\nSubjects:\n";
    for (int i = 0; i < 5; i++) {
        if (!teacher.subjects[i].empty()) cout << "- " << teacher.subjects[i] << endl;
    }

    cout << "Papers:\n";
    for (int i = 0; i < 10; i++) {
        if (!teacher.papers[i].empty()) cout << "- " << teacher.papers[i] << endl;
    }

    pressKeyToContinue();
}

int main() {
    Teacher teachers[3];
    int numTeachers = 0;

    Student students[3];
    int numStudents = 0;

    while (true) {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Register Student\n2. Register Teacher\n3. Login Student\n4. Login Teacher\n0. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(students, numStudents); break;
            case 2: registerTeacher(teachers, numTeachers); break;
            case 3:
                if (loginStudent(students, numStudents)) {
                    int sChoice;
                    do {
                        cout << "\n-- Student Menu --\n1. Attempt Paper\n2. View Result\n3. Update Info\n4. Logout\nEnter choice: ";
                        cin >> sChoice;
                        switch (sChoice) {
                            case 1: PaperAttempt(students[numStudents - 1], teachers); break;
                            case 2: viewResult(students[numStudents - 1]); break;
                            case 3: updateStudentData(students[numStudents - 1]); break;
                        }
                    } while (sChoice != 4);
                }
                break;
            case 4:
                if (loginTeacher(teachers, numTeachers)) {
                    int tChoice;
                    do {
                        cout << "\n-- Teacher Menu --\n1. Add Subject\n2. Add Paper\n3. View Students\n4. Check Papers\n5. View Info\n6. Logout\nEnter choice: ";
                        cin >> tChoice;
                        switch (tChoice) {
                            case 1: addSubject(teachers[numTeachers - 1]); break;
                            case 2: addPaper(teachers[numTeachers - 1]); break;
                            case 3: viewAllStudents(students, numStudents); break;
                            case 4: checkPapers(teachers[numTeachers - 1], students, numStudents); break;
                            case 5: viewTeacherInfo(teachers[numTeachers - 1]); break;
                        }
                    } while (tChoice != 6);
                }
                break;
            case 0:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
                pressKeyToContinue();
        }
    }
}
