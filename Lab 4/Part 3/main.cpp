#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

bool isSmaller(const std::string& str1, const std::string& str2) {
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2) return true;
    if (n2 < n1) return false;
    return str1 < str2;
}

std::string subtractLargeIntegers(std::string num1, std::string num2) {
    if (isSmaller(num1, num2)) {
        return "-" + subtractLargeIntegers(num2, num1);
    }

    std::string diff = "";
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    int carry = 0;

    for (size_t i = 0; i < num2.length(); i++) {
        int sub = ((num1[i] - '0') - (num2[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else {
            carry = 0;
        }
        diff += std::to_string(sub);
    }

    for (size_t i = num2.length(); i < num1.length(); i++) {
        int sub = ((num1[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else {
            carry = 0;
        }
        diff += std::to_string(sub);
    }

    while (diff.length() > 1 && diff.back() == '0') {
        diff.pop_back();
    }

    std::reverse(diff.begin(), diff.end());
    return diff;
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
    std::cout << "--- Large Integer Subtraction Program ---" << std::endl;

    // a. Generate 10 random numeric literals
    std::vector<std::string> randomNumbers;
    for (int i = 0; i < 10; ++i) {
        randomNumbers.push_back(generateRandomLargeNumber());
    }

    std::cout << "\na. Generated 10 random numbers:" << std::endl;
    for (const auto& num : randomNumbers) {
        std::cout << num << std::endl;
    }

    // d. Repeat until there are no more random numbers to be subtracted
    std::string currentDifference = randomNumbers[0];
    for (size_t i = 1; i < randomNumbers.size(); ++i) {
        std::cout << "\n------------------------------------" << std::endl;
        // b. List the two random numbers that are about to be subtracted
        std::cout << "b. Numbers to be subtracted:" << std::endl;
        std::cout << "Num1 = " << currentDifference << std::endl;
        std::cout << "Num2 = " << randomNumbers[i] << std::endl;

        currentDifference = subtractLargeIntegers(currentDifference, randomNumbers[i]);

        // c. List the result
        std::cout << "c. Result:" << std::endl;
        std::cout << "Difference = " << currentDifference << std::endl;
    }

    std::cout << "\nFinal difference: " << currentDifference << std::endl;

    return 0;
}