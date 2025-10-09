#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

void printSolution(const std::vector<int>& sol) {
    std::cout << sol[0] << " / " << sol[1] << " * " << sol[2] << " + "
              << sol[3] << " * " << sol[4] << " * " << sol[5] << " / " << sol[6] << " + "
              << sol[7] << " * " << sol[8] << " = 100" << std::endl;
}

void findSolutionsRecursive(std::vector<int>& digits, int k, std::vector<std::vector<int>>& solutions) {
    if (k == digits.size()) {
        // Check if the final sum is 100.
        double a = digits[0], b = digits[1], c = digits[2],
               d = digits[3], e = digits[4], f = digits[5],
               g = digits[6], h = digits[7], i = digits[8];

        double result = (a / b) * c + (d * e * f) / g + (h * i);

        if (result == 100) {
            solutions.push_back(digits);
        }
        return;
    }

    for (int i = k; i < digits.size(); ++i) {
        std::swap(digits[k], digits[i]);

        // Check constraints to avoid dead-end branches of the recursion.
        bool shouldPrune = false;
        
        // After placing the 2nd digit (k=1), check if the first division is possible.
        if (k == 1) { 
            if (digits[0] % digits[1] != 0) {
                shouldPrune = true;
            }
        }
        // After placing the 7th digit (k=6), check the second division.
        else if (k == 6) { 
            if ((digits[3] * digits[4] * digits[5]) % digits[6] != 0) {
                shouldPrune = true;
            }
        }

        // If the branch is not pruned, continue to the next level of recursion.
        if (!shouldPrune) {
             findSolutionsRecursive(digits, k + 1, solutions);
        }

        std::swap(digits[k], digits[i]);
    }
}

int main() {
    std::cout << "Solving: []/[]*[] + []*[]*[]/[] + []*[] = 100 with digits 1-9" << std::endl;
    
    std::vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::vector<int>> solutions;

    findSolutionsRecursive(digits, 0, solutions);

    std::cout << "\n--- Task 1: List all the combinations ---" << std::endl;
    if (solutions.empty()) {
        std::cout << "No solutions found." << std::endl;
    } else {
        std::cout << "Found " << solutions.size() << " solutions:" << std::endl;
        for (const auto& sol : solutions) {
            printSolution(sol);
        }
    }

    return 0;
}