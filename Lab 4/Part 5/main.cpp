#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

std::string addLargeIntegers(std::string num1, std::string num2) {
    if (num1.length() < num2.length()) {
        std::swap(num1, num2);
    }
    std::string sum = "";
    int len1 = num1.length();
    int len2 = num2.length();
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    int carry = 0;
    for (int i = 0; i < len2; i++) {
        int currentSum = ((num1[i] - '0') + (num2[i] - '0') + carry);
        sum.push_back(currentSum % 10 + '0');
        carry = currentSum / 10;
    }
    for (int i = len2; i < len1; i++) {
        int currentSum = ((num1[i] - '0') + carry);
        sum.push_back(currentSum % 10 + '0');
        carry = currentSum / 10;
    }
    if (carry) {
        sum.push_back(carry + '0');
    }
    std::reverse(sum.begin(), sum.end());
    return sum;
}

// a. An iterative Fibonacci that accepts an integer input 
std::string iterativeFibonacci(int n) {
    if (n <= 0) return "0";
    if (n == 1) return "1";

    std::string a = "0";
    std::string b = "1";
    std::string c;

    for (int i = 2; i <= n; i++) {
        c = addLargeIntegers(a, b);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    std::cout << "--- Large Fibonacci Number Calculator ---" << std::endl;
    
    int n;
    std::cout << "\nEnter an integer 'n' between 1 and 100,000 to find the n-th Fibonacci number: ";
    std::cin >> n;
    if (n >= 1 && n <= 100000) {
        std::cout << "\nCalculating F(" << n << ")..." << std::endl;
        std::string fib_n = iterativeFibonacci(n);
        std::cout << "The " << n << "-th Fibonacci number is: " << std::endl;
        std::cout << fib_n << std::endl;
    } else {
        std::cout << "Input is out of the valid range [1, 100000]." << std::endl;
    }

    // b. Find out what is the largest Fibonacci that you can calculate 
    int largest_n = 100000;
    std::cout << "\n------------------------------------" << std::endl;
    std::cout << "\nb. The largest specified Fibonacci number to calculate is F(" << largest_n << ")." << std::endl;

    // c. Find out the time required for the calculation 
    std::cout << "c. Calculating F(" << largest_n << ") and measuring the time..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::string largest_fib = iterativeFibonacci(largest_n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\nCalculation of F(" << largest_n << ") is complete." << std::endl;
    std::cout << "Time required for the calculation: " << elapsed.count() << " seconds." << std::endl;
    std::cout << "F(" << largest_n << ") has " << largest_fib.length() << " digits." << std::endl;

    return 0;
}