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

std::string multiplyLargeIntegers(std::string num1, std::string num2) {
    if (num1 == "0" || num2 == "0") {
        return "0";
    }

    std::string finalProduct = "0";
    int shift = 0;

    for (int i = num2.length() - 1; i >= 0; i--) {
        int multiplier = num2[i] - '0';
        std::string partialProduct = "";
        int carry = 0;

        for (int j = num1.length() - 1; j >= 0; j--) {
            int multiplicand = num1[j] - '0';
            int product = (multiplier * multiplicand) + carry;
            partialProduct += std::to_string(product % 10);
            carry = product / 10;
        }

        if (carry > 0) {
            partialProduct += std::to_string(carry);
        }

        std::reverse(partialProduct.begin(), partialProduct.end());

        for(int k=0; k < shift; ++k) {
            partialProduct += '0';
        }

        finalProduct = addLargeIntegers(finalProduct, partialProduct);
        shift++;
    }

    return finalProduct;
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
    std::cout << "--- Large Integer Multiplication Program ---" << std::endl;

    // a. Generate 2 random numeric literals
    std::string num1 = generateRandomLargeNumber();
    std::string num2 = generateRandomLargeNumber();

    // b. List these two random numbers
    std::cout << "\nb. Numbers to be multiplied:" << std::endl;
    std::cout << "Num1 = " << num1 << std::endl;
    std::cout << "Num2 = " << num2 << std::endl;
    
    // c. List the product of step b
    std::string product = multiplyLargeIntegers(num1, num2);
    std::cout << "\nc. Result:" << std::endl;
    std::cout << "Product = " << product << std::endl;

    return 0;
}