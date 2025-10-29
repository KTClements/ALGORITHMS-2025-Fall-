#include <iostream>
#include <vector>
#include <algorithm>

int knapsack(int C, const std::vector<int>& w, const std::vector<int>& v, int n) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(C + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= C; ++j) {
            if (w[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = std::max(dp[i - 1][j], v[i - 1] + dp[i - 1][j - w[i - 1]]);
            }
        }
    }

    return dp[n][C];
}

int main() {
    int n = 5;
    int C = 12;
    std::vector<int> w = {1, 3, 4, 6, 9};
    std::vector<int> v = {1, 7, 23, 16, 32};

    int optimal_value = knapsack(C, w, v, n);

    std::cout << "Problem Data:" << std::endl;
    std::cout << "  - Capacity (C): " << C << std::endl;
    std::cout << "  - Weights (w): {1, 3, 4, 6, 9}" << std::endl;
    std::cout << "  - Values (v): {1, 7, 23, 16, 32}" << std::endl;
    std::cout << "\nThe optimal value for the 0/1 Box problem is: " << optimal_value << std::endl;

    return 0;
}