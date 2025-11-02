#include <iostream>
using namespace std;

class Pile {
private:
    int* elements;   // Tableau dynamique
    int sommet;      // Indice du sommet de la pile
    int capacite;    // Taille maximale

public:
    // 🔹 Constructeur
    Pile(int taille) {
        capacite = taille;
        elements = new int[capacite];
        sommet = -1; // pile vide
    }

    // 🔹 Empiler (push)
    void push(int valeur) {
        if (sommet >= capacite - 1) {
            cout << "Erreur : pile pleine !" << endl;
        } else {
            sommet++;
            elements[sommet] = valeur;
            cout << "Empile : " << valeur << endl;
        }
    }

    // 🔹 Dépiler (pop)
    int pop() {
        if (sommet < 0) {
            cout << "Erreur : pile vide !" << endl;
            return -1;
        } else {
            int valeur = elements[sommet];
            sommet--;
            cout << "Depile : " << valeur << endl;
            return valeur;
        }
    }

    // 🔹 Vérifie si la pile est vide
    bool estVide() const {
        return (sommet == -1);
    }

    // 🔹 Vérifie si la pile est pleine
    bool estPleine() const {
        return (sommet == capacite - 1);
    }

    // 🔹 Affiche les éléments de la pile
    void afficher() const {
        if (estVide()) {
            cout << "Pile vide !" << endl;
            return;
        }
        cout << "Contenu de la pile : ";
        for (int i = 0; i <= sommet; i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

    // 🔹 Destructeur
    ~Pile() {
        delete[] elements;
        cout << "Pile detruite." << endl;
    }
};

int main() {
    // 🔸 Création de deux piles
    Pile p1(5);
    Pile p2(3);

    // 🔸 Test de p1
    p1.push(10);
    p1.push(20);
    p1.push(30);
    p1.afficher();

    p1.pop();
    p1.afficher();

    // 🔸 Test de p2
    p2.push(100);
    p2.push(200);
    p2.afficher();

    p2.pop();
    p2.afficher();

    return 0;
}
