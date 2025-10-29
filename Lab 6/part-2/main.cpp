#include <iostream>
#include <vector>

long long fib_bottom_up(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    std::vector<long long> dp(n + 1);

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    return dp[n];
}

int main() {
    int n;
    std::cout << "Enter a non-negative integer n: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Input must be non-negative." << std::endl;
    } else {
        long long result = fib_bottom_up(n);
        std::cout << "F(" << n << ") = " << result << std::endl;
    }

    return 0;
}