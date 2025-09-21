#include <iostream>
using namespace std;

template <class genType>
void mySwap(genType &el1, genType &el2)
{
    genType tmp = el1;
    el1 = el2;
    el2 = tmp;
}

int main()
{
    // a. Make variables n, m, x, y
    int n = 2, m = 3;
    double x = 10.5, y = 2.7;

    // b. Use mySwap to swap these values. Display their values before swap and after swap.
    cout << "--- Swapping Integers ---" << endl;
    cout << "Before swap: n = " << n << ", m = " << m << endl;
    mySwap(n, m);
    cout << "After swap:  n = " << n << ", m = " << m << endl << endl;

    cout << "--- Swapping Doubles ---" << endl;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    mySwap(x, y);
    cout << "After swap:  x = " << x << ", y = " << y << endl << endl;

    // c. What will happen when swapping two different types?
    cout << "--- Experiment: Swpping Different Types ---" << endl;
    cout << "Attempting to call mySwap(n, x)..." << endl;
    cout << "This line will cause a compile-time error. See explanation below." << endl;

    return 0;
}