#include <iostream>
using namespace std;

// ===============================
// 🔹 Définition de la classe
// ===============================
class AnalyseurDeNombre {
private:
    int nombre; // attribut privé → encapsulation

public:
    // 🔸 Constructeur
    AnalyseurDeNombre(int n) : nombre(n) {}

    // 🔸 Méthode : tester si le nombre est pair
    bool estPair() const {
        return (nombre % 2 == 0);
    }

    // 🔸 Méthode : tester si le nombre est multiple de 3
    bool estMultipleDe3() const {
        return (nombre % 3 == 0);
    }

    // 🔸 Méthode : analyser complètement le nombre
    void analyser() const {
        cout << "Analyse du nombre " << nombre << " :" << endl;

        if (estPair())
            cout << " - Il est pair" << endl;
        if (estMultipleDe3())
            cout << " - Il est multiple de 3" << endl;
        if (estPair() && estMultipleDe3())
            cout << " - Il est divisible par 6" << endl;

        cout << "-------------------------" << endl;
    }
};

// ===============================
// 🔹 Programme principal
// ===============================
int main() {
    int n;

    cout << "Donnez un entier : ";
    cin >> n;

    // Création d’un objet à partir de la classe
    AnalyseurDeNombre analyseur(n);

    // Appel de la méthode d’analyse
    analyseur.analyser();

    return 0;
}
