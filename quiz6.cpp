/**
 * @author JD Ojeda
 * Synopsis: This program demonstrates the use of a class with dynamically allocated objects
 * to manage and display student data.
*/
#include <iostream>
#include <string>
using namespace std;

// class definition
class Student {
private:
    string name;
    int age;
    double gpa;
public:
    // member function to set the student data
    void setData();

    // member function to display the student data
    void displayData() const;
};

// member function definitions
void Student::setData() { // definitions using the scope resolution operator
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter gpa: ";
    cin >> gpa;
}

void Student::displayData() const {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "GPA: " << gpa << endl;
}

int main() {
    Student *studentPtr = new Student; // dynamically allocate student pointer

    // set the data using the pointer
    studentPtr->setData();

    // display the data using the pointer
    studentPtr->displayData();

    // delete the allocated memory pointer
    delete studentPtr;

    return 0;
}

