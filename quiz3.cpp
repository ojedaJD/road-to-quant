/**
 * @author JD Ojeda
 * Synopsis: This program calculates the final price of an item after applying a tax rate.
 * It takes user input for the price of the item, calculates the tax amount, 
 * and displays the original price, tax amount, and final price formatted to two decimal places.
*/
#include <iostream>
#include <iomanip> // this is used for formatting output
using namespace std;

// global constant variable
const double TAX_RATE = 0.07; // following const value naming convention

// function prototypes
double calculateFinalPrice(double price);

int main() {
    // price cannot be lower than 0
    double price;

    // prompt the user to enter the price of the item
    cout << "Enter the price of the item: ";
    cin >> price;
    while (price < 0.0) {
        cout << "Please enter a valid input for the price: ";
        cin >> price;
    }

    // call to function to get the final price after tax
    double finalPrice = calculateFinalPrice(price);

    // find the tax amount for the user
    double taxAmount = finalPrice - price;

    // display the results
    cout << fixed << setprecision(2); // values of the double will be to 2 decimals
    cout << "Original Price: $" << price << endl;
    cout << "Tax amount: $" << taxAmount << endl;
    cout << "Final Price: $" << finalPrice << endl;

    return 0;
}

// function definitions
double calculateFinalPrice(double price) {
    double tax = price * TAX_RATE;
    return price + tax;
}
