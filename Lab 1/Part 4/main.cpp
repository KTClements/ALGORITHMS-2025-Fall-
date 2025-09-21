#include <iostream>

using namespace std;

// a. A function to add all numbers in an integer array
int sumArray(int* arr, int size) {
    int sum = 0;
    int* end = arr + size;
    for (int* ptr = arr; ptr < end; ptr++) {
        sum += *ptr;
    }
    return sum;
}

// c. A function to remove all odd numbers from an ordered array
int removeOddNumbers(int* arr, int size) {
    int* write_ptr = arr;
    int* end = arr + size;

    for (int* read_ptr = arr; read_ptr < end; read_ptr++) {
        if (*read_ptr % 2 == 0) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
    }

    return write_ptr - arr;
}

void printArray(int* arr, int size) {
    cout << "[";
    int* end = arr + size;
    for (int* ptr = arr; ptr < end; ptr++) {
        cout << *ptr;
        if ((ptr + 1) < end) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main() {
    cout << "<< Task a: Sum Array >>" << endl;
    int numbers[] = {10, 20, 30, 40, 50};
    int size_a = sizeof(numbers) / sizeof(int);
    cout << "Array: ";
    printArray(numbers, size_a);
    cout << "Sum: " << sumArray(numbers, size_a) << endl << endl;

    cout << "<< Task c: Remove Odd Numbers >>" << endl;
    int ordered_array[] = {2, 3, 4, 5, 8, 9, 10, 11, 12};
    int size_c = sizeof(ordered_array) / sizeof(int);

    cout << "Original Array: ";
    printArray(ordered_array, size_c);

    int new_size = removeOddNumbers(ordered_array, size_c);

    cout << "Condensed Array (after removing odds): ";
    printArray(ordered_array, new_size);
    cout << "New size: " << new_size << endl;

    cin.ignore();
    return 0;
}