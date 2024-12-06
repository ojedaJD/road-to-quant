/**
 * @author JD Ojeda
 * Synopsis: This program reverses a string entered by the user using a vector
 * and displays the reversed string character by character using pointers.
*/
#include <iostream>
#include <string> // normally written std::string but OSU requires this
#include <vector> // normally written std::vector but OSU requires this
using namespace std;

// function prototypes

// reverse string order using pointer
void reverseVector(vector<char> &str); // pass by reference to modify the OG string

// display string char by char using pointer
void displayVector(const vector<char> &str); // read only, cannot modify the string (const)


int main() {

    // string that the user will give us
    string input;

    // prompt the user for the string
    cout << "Enter a string: ";
    getline(cin, input); // reads the entire line from the user and saves to input

    // convert the string into a vector
    vector<char> charVector(input.begin(), input.end());

    // check if the input is empty
    if (charVector.empty()) {
        cout << "Input was left empty." << endl;
        return 0;
    }

    // reverse the vector
    reverseVector(charVector);

    // display the reversed vector
    displayVector(charVector);

    return 0;
}

// function definitions

void reverseVector(vector<char> &str) {
    char *start = &str[0]; // pointer to the first char in the string
    char *end = &str[str.size() - 1]; // pointer to the last cahr in the string

    // iterate until the pointers meet
    while (start < end) {
        char temp = *start; // swap chars
        *start = * end;
        *end = temp;
        start++; // move the pointer forward
        end--; // move the end pointer backwards
    }
    // nothing to return since the function is of the void type
}

void displayVector(const vector<char> &str) {
    const char *ptr = &str[0]; // pointer to the first character in the vector

    while (ptr < &str[str.size()]) { // stop when the pointer reaches the end of the vector
        cout << *ptr; //print the character that the pointer is at
        ptr++; // move the pointer to the next string
    }
    cout << endl;
}
