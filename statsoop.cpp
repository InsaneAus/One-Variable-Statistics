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
// Data class (Lines 19-206)
class data {
    public:
        void ProgramIntroText() { 
            cout << "\nOne-Variable Statistics\n";
            cout << "Displays unsorted & sorted vector, frequency table, sum, mean, median, mode,\n";
            cout << "population standard deviation, variance, range, maximum,\n";
            cout << "and minimum of array. It also displays execution time as well.\n\n";
        }

    public: // Variable Declaration (Lines 29-51)
        vector <double> x;
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
        
        
    public:
        void InputNoofElements() { // User input for inputting numbers (Lines 55-81)
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
        }

        void InputElement() {
            for (int i = 0; i < ele_final; i++) {
                cout << "Numbers added to vector: " << i << "\n";
                cout << "Input number: ";
                while (!(cin >> number)) {
                    cout << "Must be either an integer or a double.\n";
                    cout << "Reinput again here: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                x.push_back(number);
            }
        }
        void SortandUnsortedArray() { 
            cout << "\nUnsorted Vector: ";

            for (int i = 0; i < x.size(); i++) { // Displays unsorted vector (Lines 85-87)
                cout << x.at(i) << " ";
            }

            sort(x.begin(), x.end()); // Sorts the vector from smallest to largest

            cout << "\nSorted Vector: ";

            for (int i = 0; i < x.size(); i++) { // Displays sorted vector (Lines 93-95)
                cout << x.at(i) << " ";
            }
        }
        void DisplayFrequencyTable() {
            cout << "\n\nFrequency Table:\n";
            for (int i = 0; i < x.size(); i++) { // Creating the Frequency Table (Lines 99-113)
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
            for (int i = 0; i < freq_table.size(); i++) { // Displays the Frequency Table (Lines 114-117)
                cout << "x: " << x_mode.at(i) << " | freq: " << freq_table.at(i);
                cout << "\n";
            }
        }
        void DisplaySumandMean() { // Calculate Sum and Mean of Vector (Lines 120-130)
            for (int i = 0; i < x.size(); i++) {
                sum += x.at(i);
            }

            cout << "\nResults:\n";

            mean = (double) sum / (double) x.size();

            cout << "Sum: " << sum << "\n";

            cout << "Mean: " << mean << "\n";
        }
        void DisplayMedian() { // Calculate Median (Lines 133-139)
            if (x.size() % 2 == 1) {
                median = x.at(x.size()/2);
            } else if (x.size() % 2 == 0) {
                median = (double) (x.at(((x.size()/2) - 1)) + x.at(x.size()/2))/ (double) 2;
            }

            cout << "Median: " << median;
        }
        void DisplayMode() { // Calculate Mode (Lines 142-156)
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


        }
        void DisplayPopulationStandardDeviation() { // Calculate Population Standard Deviation (Lines 161-168)
            cout << "\n";

            for (int i = 0; i < x.size(); i++) {
                double square = (x.at(i) - mean) * (x.at(i) - mean);
                xminusmean += square;
            }
            standard_deviation = sqrt(xminusmean / (double) x.size());
            cout << "Population Standard Deviation: " << standard_deviation << "\n";
        }
        void DisplayVariance() { // Calculate Variance (Lines 171-172)
            variance = standard_deviation * standard_deviation;
            cout << "Variance: " << variance << "\n";
        }
        void DisplayRange() { // Calculate Range (Lines 175-176)
            range = x.at(x.size()-1) - x.at(0); // Subtracts biggest number by smallest number
            cout << "Range: " << range << "\n";
        }
        void DisplayMaximum() {
            // Get Maximum (Line 180)
            cout << "Maximum: " << x.at(x.size() - 1) << "\n";
        }
        void DisplayMinimum() {
            // Get Minimum (Line 184)
            cout << "Minimum: " << x.at(0) << "\n";
        }
        void DefaultValue() {
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

        
};
// execution_time class (Lines 208-265)
class execution_time: public data { // execution_time inherits the data class (Line 208)
    public:
        void DisplayExecutionTimePerLoop() { // Displays execution time (Lines 211-214)
            cout << "\n";
            for (int i = 0; i < time_store.size(); i++) {
            cout << "Time to calculate Stats Loop #" << i + 1 << ": " << time_store.at(i).count() << " microseconds\n";
            }
        }
        execution_time() { // execution_time's constructor (Lines 217-263)
            ProgramIntroText();
            while (continue_or_quit == false) {
                InputNoofElements();
                if (ele_final > 0) {
                    InputElement();
                    auto start_calculate = high_resolution_clock::now();
                    SortandUnsortedArray();
                    DisplayFrequencyTable();
                    DisplaySumandMean();
                    DisplayMedian();
                    DisplayMode();
                    DisplayPopulationStandardDeviation();
                    DisplayVariance();
                    DisplayRange();
                    DisplayMaximum();
                    DisplayMinimum();
                    auto stop_calculate = high_resolution_clock::now(); // Stops the stopwatch (Line 233)
                    // Calculates the execution time (Line 235)
                    auto duration_calculate = duration_cast<microseconds>(stop_calculate - start_calculate);
                    // Stores the variable inside the 'time_store' vector (Line 237)
                    time_store.push_back(duration_calculate);
                    // Displays execution time (Line 239)
                    cout << "\nExecution Time to calculate: " << duration_calculate.count() << " microseconds\n";

                } else if (ele_final == 0) {

                    cout << "\nWhy would you input 0 elements??" << "\n";

                } else if (ele_final < 0) {

                    cout << "\nNegative numbers don't work." << "\n";

                } // User input for the user if he or she wants to continue or stop running the code
                cout << "Do it again? Type 'Y' or 'y' to continue. Otherwise, the program ends.\nInput: ";
                cin >> decision;
                if (decision == "n") {
                    continue_or_quit == true;
                    break;
                }
                else if (decision == "y" || decision == "Y") {
                    DefaultValue();
                }
                else {
                    cout << "And you quit..." << "\n";
                    break;
                }
            }
        }
};


int main() { // Main method (Lines 268-276)
    auto begin_program_stopwatch = high_resolution_clock::now();
    execution_time main = execution_time();
    auto end_program_stopwatch = high_resolution_clock::now();
    auto total_time = duration_cast<seconds>(end_program_stopwatch - begin_program_stopwatch);
    main.DisplayExecutionTimePerLoop();
    cout << "\nTotal Execution Time: " << total_time.count() << " seconds\n";
    return 0;
}
