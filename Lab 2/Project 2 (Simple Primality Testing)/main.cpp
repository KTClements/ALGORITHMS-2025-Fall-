#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <cstdlib>

long generateSixDigitNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::string num_str = "";

    std::uniform_int_distribution<> first_digit_dist(1, 9);
    num_str += std::to_string(first_digit_dist(gen));

    std::uniform_int_distribution<> other_digits_dist(0, 9);
    for (int i = 0; i < 5; ++i) {
        num_str += std::to_string(other_digits_dist(gen));
    }

    return std::stoll(num_str);
}

// b) Algorithm to test if a number is prime
bool isPrime(long n, long& testCount) {
    testCount = 0;

    if (n <= 1) {
        testCount = 1;
        return false;
    }

    if (n == 2) {
        testCount = 1;
        return true;
    }

    if (n % 2 == 0) {
        testCount = 1;
        return false;
    }

    long limit = static_cast<long>(std::sqrt(n));
    for (long i = 3; i <= limit; i += 2) {
        testCount++;
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    // a) Generate at least 20 of randomly generated numbers
    int num_to_generate = 20;
    std::vector<long> numbers;
    for (int i = 0; i < num_to_generate; ++i) {
        numbers.push_back(generateSixDigitNumber());
    }

    for (long num : numbers) {
        long tests_performed = 0;
        bool result = isPrime(num, tests_performed);
        
        std::cout << "Number: " << num << " | ";
        if (result) {
            std::cout << "Answer: Prime";
        } else {
            std::cout << "Answer: Not Prime";
        }
        // c) Display number of tests performed for each number 
        std::cout << " | Tests performed: " << tests_performed << std::endl;
    }

    return 0;
}