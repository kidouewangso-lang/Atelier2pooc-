#include <iostream>
using namespace std;

int main() {
    // 1️⃣ Déclaration d’un entier
    int a = 42;

    // 2️⃣ Déclaration d’une référence vers a
    int& ref_a = a;

    // 3️⃣ Déclaration d’un pointeur vers a
    int* p_a = &a;

    // 4️⃣ Affichage
    cout << "Valeurs :\n";
    cout << "a      = " << a << endl;
    cout << "ref_a  = " << ref_a << endl;
    cout << "*p_a   = " << *p_a << endl;

    cout << "\nAdresses :\n";
    cout << "&a     = " << &a << endl;
    cout << "&ref_a = " << &ref_a << endl;
    cout << "p_a    = " << p_a << endl;

    cout << "\nValeur pointée par le pointeur :\n";
    cout << "*p_a   = " << *p_a << endl;

    return 0;
}
