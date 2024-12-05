/**
 * @author JD Ojeda
 * Synopsis: Write a program that reads an integer from the user 
 * and checks if it is a prime number. 
 * Use a for loop to determine whether the number is divisible by any number other 
 * than 1 and itself.
*/
#include <iostream>
#include <cmath>
using namespace std; // for the class we use this but in literature and in industry -> :(

/**
 * Function to check if the user's input is valid.
 * @param num The number entered by the user.
 * @return True if the number is greater than 1, false otherwise.
 */
bool isValidInput(int num);
/**
 * Function to check if the user's input is a prime number.
 * @param num The number to check.
 * @return True if the number is prime, false otherwise.
 */
bool isPrime(int num);

int main () {
    int num;
    // prompt user for a number greater than 1
    cout << "Enter a positive integer greater than 1: ";
    cin >> num;
    // ensure that the number is greater than 1
    while (!isValidInput(num)) {
        cout << "Invalid input. Enter a positive integer greater than 1: ";
        cin >> num;
    }
    // check if the user's number is prime
    if (isPrime(num)) {
        cout << num << " is prime." << endl;
    } else {
        cout << num << " is not prime." << endl;
    }

    return 0;
}

// function definitions for isValidInput and isPrime
bool isValidInput(int num) {
    // Check if the number is greater than 1 (true or false)
    return num > 1;
}

bool isPrime(int num) {
    if (num <= 1) { // anything lower than 2 is not prime
        return false;
    }
    // check divisors of the number
    for (int i = 2; i <= sqrt(num); i++) {
        // any found means not prime
        if (num % i == 0) {
            return false;
        }
    }
    // if no divisors were found after the loop then we have a prime
    return true;
}
