/**
 * @author JD Ojeda
 * Synopsis: This program calculates the smallest, largest, and average of 20 
 * numbers entered by the user.
*/
#include <iostream>
using namespace std;

// function prototypes
int findSmallest(int arr[], int size); // function to find smallest element in array
int findLargest(int arr[], int size); // function to find largest element in array
double calculateAverage(int arr[], int size); // function to calculate average

int main() {
    int numbers[20]; // array size of 20

    // prompt the user for the 20 numbers
    cout << "Enter 20 numbers";
    for (int i = 0; i < 20; i++) {
        cin >> numbers[i];
    }
    // find the smallest, largest and average of the elements
    int smallest = findSmallest(numbers, 20);
    int largest = findLargest(numbers, 20);
    double average = calculateAverage(numbers, 20);

    //display the results
    cout << "Smallest element: " << smallest << endl;
    cout << "Largest element: " << largest << endl;
    cout << "Average of the array: " << average << endl;

    return 0;
}

//function defintions

// find the smallest in the array
int findSmallest(int arr[], int size) {
    int smallest = arr[0]; // defaulting to making the first element the smallest
    // iterate to find the smallest element in the array in case its not 0 element
    for (int i=1;i<size;i++) {
        if (arr[i] < smallest) {
            //update the smallest
            smallest = arr[i];
        }
    }
    return smallest;
}

// find the largest in the array
int findLargest(int arr[], int size) {
    int largest = arr[0]; // defaulting to making the first element the largest
    // iterate to find the largest element in the array in case its not 0
    for (int i=1;i<size;i++) {
        if (arr[i] > largest) {
            // update the largest
            largest = arr[i];
        }
    }
    return largest;
}

// find the average of the array
double calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i=0;i<size;i++) {
        sum+=arr[i];
    }
    return sum * 1.0 / size; // type casting is also fine but not for OSU, so I use coercion
}
