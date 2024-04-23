#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to find the minimum value using parallel reduction
int parallelMin(const vector<int>& data) {
    int min_val = data[0];
    #pragma omp parallel for reduction(min:min_val)
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

// Function to find the maximum value using parallel reduction
int parallelMax(const vector<int>& data) {
    int max_val = data[0];
    #pragma omp parallel for reduction(max:max_val)
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

// Function to find the sum using parallel reduction
int parallelSum(const vector<int>& data) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    return sum;
}

// Function to find the average using parallel reduction
double parallelAverage(const vector<int>& data) {
    int sum = parallelSum(data);
    return static_cast<double>(sum) / data.size();
}

int main() {
    vector<int> data = {5, 8, 3, 2, 7, 9, 4, 6, 1};

    // Find minimum
    int min_val = parallelMin(data);
    cout << "Minimum: " << min_val << endl;

    // Find maximum
    int max_val = parallelMax(data);
    cout << "Maximum: " << max_val << endl;

    // Find sum
    int sum_val = parallelSum(data);
    cout << "Sum: " << sum_val << endl;

    // Find average
    double avg_val = parallelAverage(data);
    cout << "Average: " << avg_val << endl;

    return 0;
}

