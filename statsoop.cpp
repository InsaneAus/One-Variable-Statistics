#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>
#include <chrono> // used to measure time and subtract two timepoints to get the interval of time passed in between

using std::cout; // used to output the statement/s
using std::cin; // used for input of values
using std::sort; // 
using std::string;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;
using std::to_string;

class data {
    public:
        void ProgramIntroText() {
            cout << "\nOne-Variable Statistics\n";
            cout << "Displays unsorted & sorted vector, frequency table, sum, mean, median, mode,\n";
            cout << "population standard deviation, variance, range, maximum,\n";
            cout << "and minimum of array. It also displays execution time as well.\n\n";
        }

    public:
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
        void InputNoofElements() { 
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

            for (int i = 0; i < x.size(); i++) {
                cout << x.at(i) << " ";
            }

            sort(x.begin(), x.end());

            cout << "\nSorted Vector: ";

            for (int i = 0; i < x.size(); i++) {
                cout << x.at(i) << " ";
            }
        }
        void DisplayFrequencyTable() {
            cout << "\n\nFrequency Table:\n";
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
            for (int i = 0; i < freq_table.size(); i++) {
                cout << "x: " << x_mode.at(i) << " | freq: " << freq_table.at(i);
                cout << "\n";
            }
        }
        void DisplaySumandMean() { // Calculate Sum and Mean of Vector
            for (int i = 0; i < x.size(); i++) {
                sum += x.at(i);
            }

            cout << "\nResults:\n";

            mean = (double) sum / (double) x.size();

            cout << "Sum: " << sum << "\n";

            cout << "Mean: " << mean << "\n";
        }
        void DisplayMedian() { // Calculate Median
            if (x.size() % 2 == 1) {
                median = x.at(x.size()/2);
            } else if (x.size() % 2 == 0) {
                median = (double) (x.at(((x.size()/2) - 1)) + x.at(x.size()/2))/ (double) 2;
            }

            cout << "Median: " << median;
        }
        void DisplayMode() { // Calculate Mode
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
        void DisplayPopulationStandardDeviation() { // Calculate Population Standard Deviation
            cout << "\n";

            for (int i = 0; i < x.size(); i++) {
                double square = (x.at(i) - mean) * (x.at(i) - mean);
                xminusmean += square;
            }
            standard_deviation = sqrt(xminusmean / (double) x.size());
            cout << "Population Standard Deviation: " << standard_deviation << "\n";
        }
        void DisplayVariance() { // Calculate Variance
            variance = standard_deviation * standard_deviation;
            cout << "Variance: " << variance << "\n";
        }
        void DisplayRange() { // Calculate Range
            range = x.at(x.size()-1) - x.at(0); // Subtracts biggest number by smallest number
            cout << "Range: " << range << "\n";
        }
        void DisplayMaximum() {
            // Get Maximum
            cout << "Maximum: " << x.at(x.size() - 1) << "\n";
        }
        void DisplayMinimum() {
            // Get Minimum
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

class execution_time: public data {
    public:
        void DisplayExecutionTimePerLoop() {
            cout << "\n";
            for (int i = 0; i < time_store.size(); i++) {
            cout << "Time to calculate Stats Loop #" << i + 1 << ": " << time_store.at(i).count() << " microseconds\n";
            }
        }
        execution_time() {
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
                    auto stop_calculate = high_resolution_clock::now();

                    auto duration_calculate = duration_cast<microseconds>(stop_calculate - start_calculate);

                    time_store.push_back(duration_calculate);

                    cout << "\nExecution Time to calculate: " << duration_calculate.count() << " microseconds\n";

                } else if (ele_final == 0) {

                    cout << "\nWhy would you input 0 elements??" << "\n";

                } else if (ele_final < 0) {

                    cout << "\nNegative numbers don't work." << "\n";

                }
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


int main() {
    auto begin_program_stopwatch = high_resolution_clock::now();
    execution_time main = execution_time();
    auto end_program_stopwatch = high_resolution_clock::now();
    auto total_time = duration_cast<seconds>(end_program_stopwatch - begin_program_stopwatch);
    main.DisplayExecutionTimePerLoop();
    cout << "\nTotal Execution Time: " << total_time.count() << " seconds\n";
    return 0;
}
