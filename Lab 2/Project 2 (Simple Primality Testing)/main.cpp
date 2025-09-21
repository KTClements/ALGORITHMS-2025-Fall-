#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <cmath>

void printVector(const std::vector<int>& vec) {
    std::cout << "{ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    std::cout << " }";
}

int main() {
    // a) Generate 10 random whole numbers between -20 to +20 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-20, 20);

    std::vector<int> numbers;
    std::cout << "Generated Set: ";
    for (int i = 0; i < 10; ++i) {
        numbers.push_back(distrib(gen));
    }
    printVector(numbers);
    std::cout << std::endl;

    // d) Start the timer to show how much time passed 
    auto start = std::chrono::high_resolution_clock::now();

    bool found = false;
    std::vector<int> result_subset;

    int num_elements = numbers.size();
    int num_subsets = static_cast<int>(std::pow(2, num_elements));

    for (int i = 1; i < num_subsets; ++i) {
        std::vector<int> current_subset;
        long long current_sum = 0;

        // b) Choosing a subset of numbers 
        for (int j = 0; j < num_elements; ++j) {
            if ((i >> j) & 1) {
                current_subset.push_back(numbers[j]);
            }
        }
        
        // c) Test the subset 
        current_sum = std::accumulate(current_subset.begin(), current_subset.end(), 0LL);

        if (current_sum == 0) {
            found = true;
            result_subset = current_subset;
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;

    // d) Show the result and the time passed 
    if (found) {
        std::cout << "Answer: Yes" << std::endl;
        std::cout << "Subset that sums to 0: ";
        printVector(result_subset);
        std::cout << std::endl;
    } else {
        std::cout << "Answer: No" << std::endl;
        std::cout << "No subset sums to 0." << std::endl;
    }

    std::cout << "Time elapsed: " << elapsed.count() << " microseconds." << std::endl;

    return 0;
}