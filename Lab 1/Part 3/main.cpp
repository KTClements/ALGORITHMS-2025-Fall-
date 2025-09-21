#include <iostream>
using namespace std;

class Node
{
public:
    int *space;
    int size;

    Node(int s[], int a = 0)
    {
        size = a;
        space = new int[a];
        for (int i = 0; i < a; i++)
            space[i] = s[i];
    }

    // FIX: User-defined copy constructor for a deep copy
    Node(const Node& other) {
        cout << "*** (Deep copy constructor called)" << endl;
        size = other.size;
        space = new int[size];
        for (int i = 0; i < size; i++) {
            space[i] = other.space[i];
        }
    }

    // FIX: Destructor to prevent memory leaks
    ~Node() {
        delete[] space;
        space = nullptr;
    }

    friend ostream& operator<<(ostream& os, const Node& node);
};

// b. Overload << operator for class Node
ostream& operator<<(ostream& os, const Node& node) {
    os << "[";
    for (int i = 0; i < node.size; i++) {
        os << node.space[i];
        if (i < node.size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main()
{
    int i[] = { 1, 2, 3, 4, 5, 6};
    // The sizeof(i)/4 is not portable; sizeof(int) is better.
    Node test1(i, sizeof(i) / sizeof(int));

    cout << "Before copy, test1 contains: " << test1 << endl;

    Node test2(test1);

    cout << "After copy, test2 contains: " << test2 << endl << endl;

    cout << "Modifying test1.space[2] = 7;" << endl;
    test1.space[2] = 7;

    cout << "test1 now contains: " << test1 << endl;
    cout << "test2 still contains: " << test2 << endl << endl;

    cout << "The value of test2.space[2] is: ";
    cout << test2.space[2] << endl;

    cin.ignore();
    return 0;
}