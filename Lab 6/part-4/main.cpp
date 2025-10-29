#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int maximize_sum_of_mins(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());

    int maximized_sum = 0;

    for (size_t i = 0; i < nums.size(); i += 2) {
        maximized_sum += nums[i];
    }

    return maximized_sum;
}

int main() {
    std::vector<int> gifts = {7, 3, 5, 9};

    std::cout << "Input array: {7, 3, 5, 9}" << std::endl;

    int result = maximize_sum_of_mins(gifts);

    std::cout << "The maximized sum of the lowest values is: " << result << std::endl;

    std::vector<int> gifts2 = {1, 4, 3, 2, 6, 5};

    std::cout << "\nInput array: {1, 4, 3, 2, 6, 5}" << std::endl;
    int result2 = maximize_sum_of_mins(gifts2);
    std::cout << "The maximized sum of the lowest values is: " << result2 << std::endl;

    return 0;
}