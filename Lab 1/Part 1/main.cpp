#include <iostream>
#include <cstring>
using namespace std;

template <class genType, int size = 50>
class genClass
{
public:
    genType storage[size];
};

int main()
{
    genClass<int> intObject;
    genClass<float, 123> floatObject;

    // a. Assign 1 to 10 to the first 10 elements of intObject
    for (int i = 0; i < 10; ++i) {
        intObject.storage[i] = i + 1;
    }

    // b. Assign 1.0 to 3.0 offset 0.1 to the first 20 elements of floatObject.
    for (int i = 0; i < 20; ++i) {
        floatObject.storage[i] = 1.0f + (i * 0.1f);
    }

    // c. Use cout to display the first 10 elements of intObject and floatObject.
    cout << "First 10 elements of intObject:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << intObject.storage[i] << " ";
    }
    cout << endl << endl;

    cout << "First 10 elements of floatObject:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << floatObject.storage[i] << " ";
    }
    cout << endl;

    cin.ignore();
    return 0;
}