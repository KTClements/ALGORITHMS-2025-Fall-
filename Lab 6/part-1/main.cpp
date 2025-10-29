#include <iostream>
#include <vector>
#include <map>

std::map<int, long long> memo;

long long fib_recursive_memo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    if (memo.find(n) != memo.end()) {
        return memo[n];
    }

    long long result = fib_recursive_memo(n - 1) + fib_recursive_memo(n - 2) + fib_recursive_memo(n - 3);
    memo[n] = result;
    return result;
}

int main() {
    int n;
    std::cout << "Enter a non-negative integer n: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Input must be non-negative." << std::endl;
    } else {
        long long result = fib_recursive_memo(n);
        std::cout << "F(" << n << ") = " << result << std::endl;
    }

    return 0;
}