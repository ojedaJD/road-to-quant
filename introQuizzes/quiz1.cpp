/**
 * Program used to prepare for the final exam at OSU for CSE 1222.
 * Exam will have (10ish) -- MC, matching, Drag and drop questions.
 * There will also be coding questions.
 * Have all tabs open prior to beginning the exam so you dont get the boot.
 * 
 */

#include <iostream>
#include <cmath>
using namespace std;

int calculateGCD(int a, int b);
int main () {
    // decalare the vars for ints for the gcd
    int num1, num2;
    // prompt the user for the 2 nums
    cout << "Enter two positive integers: ";
    cin >> num1 >> num2;
    while (num1 < 1 || num2 < 1) {
        cout << "Those numbers are invalid. Please enter two positive integers";
        cin >> num1 >> num2;
    }

    // call gcd function and display the results
    int gcd = calculateGCD(num1, num2);
    cout << "The GCD of " << num1 << " and " << num2 << " is " << gcd << endl;

    // end the program
    return 0;
}

// function defintion
int calculateGCD(int a, int b) {
    // gcd logic
    int smaller;
    // check which of the two numbers is smaller than the other one
    if (a<b) {
        smaller = a;
    } else {
        smaller = b;
    }
    //iterate from smaller to 1 to find the gcd
    for (int i=smaller; i>1; i--) {
        if (a % i == 0 && b % i == 0) { // check if i divides by a and b
            return i; // gcd is i
        }
    }
    return 1; // if 1 is the gcd
}
