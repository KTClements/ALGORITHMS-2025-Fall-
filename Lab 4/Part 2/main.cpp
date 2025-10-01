#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

std::string addLargeIntegers(std::string num1, std::string num2) {
    std::string sum = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        int currentSum = digit1 + digit2 + carry;
        sum += std::to_string(currentSum % 10);
        carry = currentSum / 10;
    }

    std::reverse(sum.begin(), sum.end());
    return sum;
}

std::string generateRandomLargeNumber() {
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> digit_dist(0, 9);
    std::uniform_int_distribution<> first_digit_dist(1, 9);

    std::string num_str;
    num_str += std::to_string(first_digit_dist(gen));
    for (int i = 0; i < 15; ++i) {
        num_str += std::to_string(digit_dist(gen));
    }
    return num_str;
}

int main() {
    std::cout << "--- Large Integer Addition Program ---" << std::endl;

    // a. Generate 10 random numeric literals
    std::vector<std::string> randomNumbers;
    for (int i = 0; i < 10; ++i) {
        randomNumbers.push_back(generateRandomLargeNumber());
    }

    std::cout << "\nStep a. Generated 10 random numbers:" << std::endl;
    for (const auto& num : randomNumbers) {
        std::cout << num << std::endl;
    }

    // d. Repeat step 2 until there are no more random numbers to be added
    std::string currentSum = randomNumbers[0];
    for (size_t i = 1; i < randomNumbers.size(); ++i) {
        std::cout << "\n------------------------------------" << std::endl;
        // b. List the two random numbers that are about to be added together
        std::cout << "Step b. Numbers to be added:" << std::endl;
        std::cout << "$Num1 = " << currentSum << "$" << std::endl;
        std::cout << "$Num2 = " << randomNumbers[i] << "$" << std::endl;

        currentSum = addLargeIntegers(currentSum, randomNumbers[i]);

        // c. List the Sum of step b [cite: 22]
        std::cout << "Step c. Result:" << std::endl;
        std::cout << "$Sum = " << currentSum << "$" << std::endl;
    }
    
    std::cout << "\nFinal sum of all numbers: " << currentSum << std::endl;

    return 0;
}