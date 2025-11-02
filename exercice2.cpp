#include <iostream>
#include <cstring> // pour memset
using namespace std;

class Fichier {
private:
    char* P;       // pointeur vers la zone mémoire du fichier
    int longueur;  // taille du fichier (en octets)

public:
    // 🔹 Constructeur par défaut
    Fichier() {
        P = nullptr;
        longueur = 0;
        cout << "Constructeur : objet Fichier créé." << endl;
    }

    // 🔹 Méthode Creation : alloue une zone mémoire
    void Creation(int taille) {
        if (P != nullptr) {
            delete[] P; // libérer si déjà alloué
        }
        longueur = taille;
        P = new char[longueur];  // allocation dynamique
        cout << "Mémoire de " << longueur << " octets allouée." << endl;
    }

    // 🔹 Méthode Remplit : remplir arbitrairement la zone mémoire
    void Remplit() {
        if (P == nullptr) {
            cout << "Erreur : aucune mémoire allouée !" << endl;
            return;
        }

        // Remplissage arbitraire : chaque case reçoit une lettre ou un chiffre
        for (int i = 0; i < longueur; i++) {
            P[i] = 'A' + (i % 26); // lettres A..Z en boucle
        }

        cout << "Zone mémoire remplie avec des valeurs arbitraires." << endl;
    }

    // 🔹 Méthode Affiche : afficher le contenu mémoire
    void Affiche() const {
        if (P == nullptr) {
            cout << "Erreur : aucune mémoire à afficher !" << endl;
            return;
        }

        cout << "Contenu mémoire (" << longueur << " octets) :" << endl;
        for (int i = 0; i < longueur; i++) {
            cout << P[i];
        }
        cout << endl;
    }

    // 🔹 Destructeur : libère la mémoire
    ~Fichier() {
        if (P != nullptr) {
            delete[] P;
            cout << "Mémoire libérée." << endl;
        }
        cout << "Destructeur : objet Fichier détruit." << endl;
    }
};

// 🔸 Programme principal
int main() {
    cout << "=== DÉBUT DU PROGRAMME ===" << endl;

    // Création d'un objet Fichier dynamiquement
    Fichier* f = new Fichier();

    // Appel des méthodes
    f->Creation(30);   // alloue 30 octets
    f->Remplit();       // remplit la mémoire
    f->Affiche();       // affiche le contenu

    // Suppression de l’objet (appelle le destructeur)
    delete f;

    cout << "=== FIN DU PROGRAMME ===" << endl;
    return 0;
}
