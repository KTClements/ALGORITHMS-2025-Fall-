#include <iostream>
#include <vector>

using namespace std;

long long waysBottomUp(int n) {
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }

    long long prevPrev = 1;
    long long prev = 2;
    long long current = 0;

    for (int i = 3; i <= n; ++i) {
        current = prev + prevPrev;

        prevPrev = prev;
        prev = current;
    }

    return current;
}

long long waysTopDownHelper(int n, vector<long long>& memo) {
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }

    if (memo[n] != -1) {
        return memo[n];
    }

    memo[n] = waysTopDownHelper(n - 1, memo) + waysTopDownHelper(n - 2, memo);

    return memo[n];
}

long long waysTopDown(int n) {
    vector<long long> memo(n + 1, -1);

    return waysTopDownHelper(n, memo);
}

int main() {
    cout << "--- Question 2: Ways to Eat Honey ---" << endl << endl;

    cout << "--- Testing with Examples (N=1, 2, 3) ---" << endl;

    int test_cases[] = {1, 2, 3};
    int expected_results[] = {1, 2, 3};
    bool tests_passed = true;

    for (int i = 0; i < 3; ++i) {
        int n = test_cases[i];
        int expected = expected_results[i];

        long long bu_result = waysBottomUp(n);
        long long td_result = waysTopDown(n);

        cout << "N = " << n << endl;
        cout << "  Bottom-Up Result:   " << bu_result << (bu_result == expected ? " (Correct)" : " (FAILED)") << endl;
        cout << "  Top-Down Result:    " << td_result << (td_result == expected ? " (Correct)" : " (FAILED)") << endl;

        if (bu_result != expected || td_result != expected) {
            tests_passed = false;
        }
    }

    if (tests_passed) {
        cout << "Test Status: PASSED" << endl;
    } else {
        cout << "Test Status: FAILED" << endl;
    }

    cout << "\n--- Solving Main Problem (N=45) ---" << endl;
    int n_problem = 45;

    long long bottomUpResult = waysBottomUp(n_problem);
    long long topDownResult = waysTopDown(n_problem);

    cout << "1) Bottom-Up Approach Result:   " << bottomUpResult << endl;
    cout << "2) Top-Down Approach Result:    " << topDownResult << endl;

    if (bottomUpResult == topDownResult) {
        cout << "Verification: Both methods match." << endl;
    } else {
        cout << "Verification: ERROR! Methods do not match." << endl;
    }

    return 0;
}