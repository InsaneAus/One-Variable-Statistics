#include <iostream> // library header that is used for cin (input) and cout (output)
#include <vector> // libary header that defines the vector container class (used for vector (dynamic array))
#include <algorithm> // library header to be used on ranges of elements
#include <cmath> // libary header that is used for mathematical operations
#include <cstdlib> // library header for general purpose functions like random number generation
#include <string> // library header to introduce string types
#include <chrono> // used to measure time and subtract two timepoints to get the interval of time passed in between
// Reduce the need to write "std::" or "std::chrono" to access identifiers from C++ (Lines 9 to 17)
using std::cout; 
using std::cin; 
using std::sort;  
using std::string;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;
using std::chrono::microseconds;
using std::chrono::duration_cast;

// Main method (Lines 20-243)
int main() {
    vector <double> x; // Variable Declaration (Lines 21-43)
    double ele;
    int ele_final;
    double number = 0;

    int freq = 1;
    vector <int> freq_table;
    vector <double> x_mode;
    vector <microseconds> time_store;

    double sum = 0;
    double mean = 0;
    double median = 0;

    int highest_freq = 0;

    double standard_deviation = 0, variance = 0, xminusmean = 0;
    double square = 0;
    double range = 0;

    bool continue_or_quit = false;

    string decision = "y";

    cout << "\nOne-Variable Statistics\n";
    cout << "Displays unsorted & sorted vector, frequency table, sum, mean, median, mode,\n";
    cout << "population standard deviation, variance, range, maximum,\n";
    cout << "and minimum of array. It also displays execution time as well.\n\n";
    
    auto begin_program_stopwatch = high_resolution_clock::now();
    
    // User input for inputting numbers (lines 54 to 79)
    
    while (continue_or_quit == false) { 
        cout << "Note: If the decimal value is inputted, it will be rounded to the nearest integer.\n";
        cout << "No. of elements: ";
        while (!(cin >> ele)) { // Input for no. of elements that will be in the vector
            cout << "- Must not be of the following data types:\n";
            cout << "- String, Character, Boolean\n";
            cout << "Please reinput again here: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        ele_final = round(ele);
        
        if (ele_final > 0) {     

            for (int i = 0; i < ele_final; i++) {
                cout << "Numbers added to vector: " << i << "\n";
                cout << "Input number: ";
                while (!(cin >> number)) {
                    cout << "Must be either an integer or a double.\n";
                    cout << "Reinput again here: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                x.push_back(number); // Adds user input of number to the vector, 'x'.
            }
            // Stopwatch to measure execution time starts with the statement below.
            auto start_calculate = high_resolution_clock::now();

            cout << "\nUnsorted Vector: "; 

            for (int i = 0; i < x.size(); i++) { // Displays the unsorted vector (Lines 85-87)
                cout << x.at(i) << " ";
            }

            sort(x.begin(), x.end()); // Sorts the vector from smallest to largest

            cout << "\nSorted Vector: ";

            for (int i = 0; i < x.size(); i++) { // Displays the sorted Vector (Lines 93 to 95)
                cout << x.at(i) << " ";
            }

            cout << "\n\nFrequency Table:\n"; // Creating the Frequency Table (Lines 97-112)
            for (int i = 0; i < x.size(); i++) {
                if (i + 1 < x.size()) {
                    if (x.at(i+1) == x.at(i)) {
                        freq += 1;
                    } else {
                        freq_table.push_back(freq);
                        x_mode.push_back(x.at(i));
                        freq = 1;
                    }
                } else {
                    freq_table.push_back(freq);
                    x_mode.push_back(x.at(i));
                    freq = 1;
                }
            }
            for (int i = 0; i < freq_table.size(); i++) { // Displays Frequency Table (Lines 113 to 116)
                cout << "x: " << x_mode.at(i) << " | freq: " << freq_table.at(i);
                cout << "\n";
            }

            // Sum and Mean of Vector (Dynamic Array) (Lines 120-130)

            for (int i = 0; i < x.size(); i++) {
                sum += x.at(i);
            }

            cout << "\nResults:\n"; 

            mean = (double) sum / (double) x.size();

            cout << "Sum: " << sum << "\n";

            cout << "Mean: " << mean << "\n";

            // Calculate Median (Lines 134-140)

            if (x.size() % 2 == 1) {
                median = x.at(x.size()/2);
            } else if (x.size() % 2 == 0) {
                median = (double) (x.at(((x.size()/2) - 1)) + x.at(x.size()/2))/ (double) 2;
            }

            cout << "Median: " << median;

            // Calculate Mode (Lines 144-158)

            int highest_freq = freq_table.at(0);

            for (int i = 0; i < freq_table.size(); i++) {
                if (freq_table.at(i) > highest_freq) {
                    highest_freq = freq_table.at(i);
                }
            }

            cout << "\nMode: ";

            for (int i = 0; i < freq_table.size(); i++) {
                if (freq_table.at(i) == highest_freq) {
                    cout << x_mode.at(i) << " ";
                }
            }

            // Calculate Population Standard Deviation (Lines 163-169)
            cout << "\n";

            for (int i = 0; i < x.size(); i++) {
                double square = (x.at(i) - mean) * (x.at(i) - mean);
                xminusmean += square;
            }

            standard_deviation = sqrt(xminusmean / (double) x.size());
            cout << "Population Standard Deviation: " << standard_deviation << "\n";

            // Calculate Variance (Lines 173-174)

            variance = standard_deviation * standard_deviation;
            cout << "Variance: " << variance << "\n";

            // Calculate Range (Lines 178-179)

            range = x.at(x.size()-1) - x.at(0); // Subtracts biggest number by smallest number
            cout << "Range: " << range << "\n";

            // Get Maximum (Line 182)
            cout << "Maximum: " << x.at(x.size() - 1) << "\n";

            // Get Minimum (Line 185)
            cout << "Minimum: " << x.at(0) << "\n";
            // Stops the stopwatch (Line 187)
            auto stop_calculate = high_resolution_clock::now(); 
            // Calculates the execution time (Line 189)
            auto duration_calculate = duration_cast<microseconds>(stop_calculate - start_calculate);

            time_store.push_back(duration_calculate); // Stores the variable inside the 'time_store' vector
            // Displays execution time (Line 193)
            cout << "\nExecution Time to calculate: " << duration_calculate.count() << " microseconds\n";

    } else if (ele_final == 0) {

        cout << "\nWhy would you input 0 elements??" << "\n";

    } else if (ele_final < 0) {

        cout << "\nNegative numbers don't work." << "\n";

    }
        // User input for the user if he or she wants to continue running the code or wants to stop running it.
        cout << "Do it again? Type 'Y' or 'y' to continue. Otherwise, the program ends.\nInput: ";
        cin >> decision;

        if (decision == "n") {
            continue_or_quit == true;
            break;
        } else if (decision == "y" || decision == "Y") {
            ele = 0;
            number = 0;

            freq = 1;
            sum = 0;
            mean = 0;
            median = 0;

            highest_freq = 0;

            standard_deviation = 0, variance = 0, xminusmean = 0;
            square = 0;
            range = 0;
            x.clear();
            x_mode.clear();
            freq_table.clear();
        }
        else {
            cout << "And you quit..." << "\n";
            break;
        }
    }
    auto end_program_stopwatch = high_resolution_clock::now();
    auto total_time = duration_cast<seconds>(end_program_stopwatch - begin_program_stopwatch);
    cout << "\n";
    for (int i = 0; i < time_store.size(); i++) { // Displays execution time (Lines 237-241)
        cout << "Time to calculate Stats Loop #" << i + 1 << ": " << time_store.at(i).count() << " microseconds\n";
    }

    cout << "\nTotal Execution Time: " << total_time.count() << " seconds\n";
    return 0;
}
