#include <iostream>
using namespace std;

int main() {
    int n;  // taille du tableau
    cout << "Entrez la taille du tableau : ";
    cin >> n;

    // 1️⃣ Allocation dynamique du premier tableau
    int* tab = new int[n];

    // 2️⃣ Lecture des éléments
    cout << "Entrez " << n << " nombres entiers :" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Nombre " << i + 1 << " : ";
        cin >> tab[i];
    }

    // 3️⃣ Allocation dynamique du second tableau
    int* carre = new int[n];

    // 4️⃣ Calcul des carrés
    for (int i = 0; i < n; i++) {
        carre[i] = tab[i] * tab[i];
    }

    // 5️⃣ Suppression du premier tableau
    delete[] tab;
    tab = nullptr;  // par sécurité (évite les pointeurs pendants)

    // 6️⃣ Affichage du tableau des carrés
    cout << "\nLes carrés des nombres sont :" << endl;
    for (int i = 0; i < n; i++) {
        cout << carre[i] << " ";
    }
    cout << endl;

    // 7️⃣ Suppression du second tableau
    delete[] carre;
    carre = nullptr;

    return 0;
}
