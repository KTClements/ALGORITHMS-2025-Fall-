#include <iostream>

long long sumEvenFibHelper(int n_remaining, long long current_sum, long long prev_even, long long curr_even) {
    
    if (n_remaining == 0) {
        return current_sum;
    }

    long long next_even = 4 * curr_even + prev_even;

    return sumEvenFibHelper(n_remaining - 1, current_sum + curr_even, curr_even, next_even);
}

long long getSumOfFirstNEvenFib(int n) {
    if (n <= 0) {
        return 0;
    }
    
    return sumEvenFibHelper(n, 0, 0, 2);
}

int main() {
    
    int n_problem = 20;
    long long totalSum = getSumOfFirstNEvenFib(n_problem);

    std::cout << "--- Problem 1 Solution ---" << std::endl;
    std::cout << "Calculating the sum of the first " << n_problem << " even Fibonacci numbers..." << std::endl;
    std::cout << "Result: " << totalSum << std::endl;
    std::cout << std::endl;

    int n_example = 3;
    long long exampleSum = getSumOfFirstNEvenFib(n_example);

    std::cout << "--- Testing Code ---" << std::endl;
    std::cout << "Calculating the sum of the first " << n_example << " even Fibonacci numbers (2, 8, 34)..." << std::endl;
    std::cout << "Expected Result: 44" << std::endl;
    std::cout << "Actual Result:   " << exampleSum << std::endl;

    if (exampleSum == 44) {
        std::cout << "Test: PASSED" << std::endl;
    } else {
        std::cout << "Test: FAILED" << std::endl;
    }

    return 0;
}