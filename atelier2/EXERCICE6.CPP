#include <iostream>
using namespace std;

// Version 1: Using pointers (C-style)
void incrementer(int* x) {
    (*x)++;
}

void permuter(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Version 2: Using references (C++ style)
void incrementer(int& x) {
    x++;
}

void permuter(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 5, y = 10;
    
    cout << "Initial values: x = " << x << ", y = " << y << endl;

    // Testing pointer version
    cout << "\nTesting pointer version:" << endl;
    incrementer(&x);
    cout << "After increment: x = " << x << endl;
    
    permuter(&x, &y);
    cout << "After swap: x = " << x << ", y = " << y << endl;

    // Testing reference version
    cout << "\nTesting reference version:" << endl;
    incrementer(x);
    cout << "After increment: x = " << x << endl;
    
    permuter(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;

    return 0;
}