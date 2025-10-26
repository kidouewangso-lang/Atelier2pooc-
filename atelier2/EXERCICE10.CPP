#include <iostream>
#include <cmath>
using namespace std;

class Complexe {
private:
    double re; // partie réelle
    double im; // partie imaginaire

public:
    // 🔹 Constructeur par défaut et paramétré
    Complexe(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    // 🔹 Méthode d'affichage
    void afficher() const {
        cout << "(" << re;
        if (im >= 0) cout << " + " << im << "i)";
        else cout << " - " << -im << "i)";
    }

    // 🔹 Saisie d’un nombre complexe
    void saisir() {
        cout << "Partie reelle : ";
        cin >> re;
        cout << "Partie imaginaire : ";
        cin >> im;
    }

    // 🔹 Addition
    Complexe operator+(const Complexe& c) const {
        return Complexe(re + c.re, im + c.im);
    }

    // 🔹 Soustraction
    Complexe operator-(const Complexe& c) const {
        return Complexe(re - c.re, im - c.im);
    }

    // 🔹 Multiplication
    Complexe operator*(const Complexe& c) const {
        return Complexe(re * c.re - im * c.im, re * c.im + im * c.re);
    }

    // 🔹 Division
    Complexe operator/(const Complexe& c) const {
        double denom = c.re * c.re + c.im * c.im;
        if (denom == 0) {
            cout << "Erreur : division par zero !" << endl;
            return Complexe();
        }
        double realPart = (re * c.re + im * c.im) / denom;
        double imagPart = (im * c.re - re * c.im) / denom;
        return Complexe(realPart, imagPart);
    }

    // 🔹 Égalité
    bool operator==(const Complexe& c) const {
        return (re == c.re && im == c.im);
    }
};

// ====================== 🔸 Fonction principale ======================

int main() {
    Complexe c1, c2, resultat;
    int choix;

    cout << "=== CALCUL SUR LES NOMBRES COMPLEXES ===\n";

    cout << "\n--- Entrez le premier nombre complexe ---\n";
    c1.saisir();

    cout << "\n--- Entrez le deuxieme nombre complexe ---\n";
    c2.saisir();

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Addition\n";
        cout << "2. Soustraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Egalite\n";
        cout << "0. Quitter\n";
        cout << "==================\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
        case 1:
            resultat = c1 + c2;
            cout << "\nSomme : ";
            resultat.afficher();
            cout << endl;
            break;

        case 2:
            resultat = c1 - c2;
            cout << "\nDifference : ";
            resultat.afficher();
            cout << endl;
            break;

        case 3:
            resultat = c1 * c2;
            cout << "\nProduit : ";
            resultat.afficher();
            cout << endl;
            break;

        case 4:
            resultat = c1 / c2;
            cout << "\nDivision : ";
            resultat.afficher();
            cout << endl;
            break;

        case 5:
            cout << "\nLes deux nombres ";
            if (c1 == c2)
                cout << "sont egaux." << endl;
            else
                cout << "ne sont pas egaux." << endl;
            break;

        case 0:
            cout << "\nFin du programme." << endl;
            break;

        default:
            cout << "Choix invalide !" << endl;
        }
    } while (choix != 0);

    return 0;
}
