/**
 * @author JD Ojeda
 * Synopsis: This program tracks employee sales performance over three months,
 * calculates their total and average sales, determines their best month, and 
 * computes the overall average sales for all employees.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// function prototypes
void readFile(const string &filename, vector<int> &ids, vector<string> &names,
              vector<int> &month1, vector<int> &month2, vector<int> &month3);
void calculateStats(const vector<int> &month1, const vector<int> &month2, const vector<int> &month3,
                    vector<int> &totals, vector<double> &averages, vector<int> &bestPerformances);
double calculateOverallAverage(const vector<int> &totals);
void writeFile(const string &filename, const vector<int> &ids, const vector<string> &names,
               const vector<int> &month1, const vector<int> &month2, const vector<int> &month3,
               const vector<int> &totals, const vector<double> &averages, const vector<int> &bestPerformances,
               double overallAverage);

int main() {
    // vectors for storing employee data
    vector<int> employeeIDs;
    vector<string> employeeNames;
    vector<int> month1Sales, month2Sales, month3Sales;
    vector<int> totalSales;
    vector<double> averageSales;
    vector<int> bestPerformance;

    string inputFileName, outputFileName;

    // input file name
    cout << "Enter the input file name: ";
    cin >> inputFileName;

    // read employee data from file
    readFile(inputFileName, employeeIDs, employeeNames, month1Sales, month2Sales, month3Sales);

    // calculate statistics
    calculateStats(month1Sales, month2Sales, month3Sales, totalSales, averageSales, bestPerformance);

    // compute overall average sales
    double overallAverage = calculateOverallAverage(totalSales);

    // output file name
    cout << "Enter the output file name: ";
    cin >> outputFileName;

    // write results to the output file
    writeFile(outputFileName, employeeIDs, employeeNames, month1Sales, month2Sales, month3Sales,
              totalSales, averageSales, bestPerformance, overallAverage);

    cout << "Results written to " << outputFileName << endl;

    return 0;
}

// function to read data from the input file
void readFile(const string &filename, vector<int> &ids, vector<string> &names,
              vector<int> &month1, vector<int> &month2, vector<int> &month3) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    int id, sales1, sales2, sales3;
    string name;
    while (inputFile >> id >> name >> sales1 >> sales2 >> sales3) {
        ids.push_back(id);
        names.push_back(name);
        month1.push_back(sales1);
        month2.push_back(sales2);
        month3.push_back(sales3);
    }

    inputFile.close();
}

// function to calculate total sales, averages, and best monthly performance
void calculateStats(const vector<int> &month1, const vector<int> &month2, const vector<int> &month3,
                    vector<int> &totals, vector<double> &averages, vector<int> &bestPerformances) {
    for (size_t i = 0; i < month1.size(); ++i) {
        int total = month1[i] + month2[i] + month3[i];
        totals.push_back(total);

        double avg = total / 3.0;
        averages.push_back(avg);

        int best = month1[i];
        if (month2[i] > best) best = month2[i];
        if (month3[i] > best) best = month3[i];
        bestPerformances.push_back(best);
    }
}

// function to calculate the overall average sales
double calculateOverallAverage(const vector<int> &totals) {
    double sum = 0.0;
    for (int total : totals) {
        sum += total;
    }
    return sum / totals.size();
}

// function to write data to the output file
void writeFile(const string &filename, const vector<int> &ids, const vector<string> &names,
               const vector<int> &month1, const vector<int> &month2, const vector<int> &month3,
               const vector<int> &totals, const vector<double> &averages, const vector<int> &bestPerformances,
               double overallAverage) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    outputFile << left << setw(10) << "ID" << setw(20) << "Name" << setw(10)
               << "Month1" << setw(10) << "Month2" << setw(10) << "Month3"
               << setw(10) << "Total" << setw(10) << "Average" << "Best" << endl;

    for (size_t i = 0; i < ids.size(); ++i) {
        outputFile << left << setw(10) << ids[i] << setw(20) << names[i] << setw(10)
                   << month1[i] << setw(10) << month2[i] << setw(10) << month3[i]
                   << setw(10) << totals[i] << setw(10) << fixed << setprecision(2)
                   << averages[i] << bestPerformances[i] << endl;
    }

    outputFile << endl << "Overall Average Sales: " << fixed << setprecision(2) << overallAverage << endl;
    outputFile.close();
}
