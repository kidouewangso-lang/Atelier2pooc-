#include <iostream>
using namespace std;

// ======================================
// 🔹 STRUCTURE ELEMENT (NOEUD DE LA LISTE)
// ======================================
struct Element {
    int valeur;         // la donnée contenue dans le nœud
    Element* suivant;   // pointeur vers le prochain élément

    // Constructeur pratique
    Element(int val) : valeur(val), suivant(nullptr) {}
};

// ======================================
// 🔹 CLASSE LISTE SIMPLEMENT CHAÎNÉE
// ======================================
class Liste {
private:
    Element* tete; // pointeur vers le premier élément de la liste

public:
    // 🔸 Constructeur
    Liste() : tete(nullptr) {
        cout << "Liste créée (vide)." << endl;
    }

    // 🔸 Méthode pour ajouter un élément au début
    void ajouterDebut(int val) {
        Element* nouveau = new Element(val); // création d’un nouveau nœud
        nouveau->suivant = tete;             // l'ancien premier devient le suivant
        tete = nouveau;                      // la tête pointe vers le nouveau
        cout << "Élément " << val << " ajouté au début." << endl;
    }

    // 🔸 Méthode pour supprimer un élément au début
    void supprimerDebut() {
        if (tete == nullptr) {
            cout << "La liste est déjà vide !" << endl;
            return;
        }

        Element* temp = tete;      // on garde l’adresse du premier élément
        tete = tete->suivant;      // on avance la tête d’un cran
        cout << "Élément " << temp->valeur << " supprimé." << endl;
        delete temp;               // on libère la mémoire
    }

    // 🔸 Méthode pour afficher la liste
    void afficher() const {
        if (tete == nullptr) {
            cout << "La liste est vide." << endl;
            return;
        }

        cout << "Contenu de la liste : ";
        Element* courant = tete; // pointeur temporaire pour parcourir
        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }
        cout << "NULL" << endl;
    }

    // 🔸 Destructeur : libère toute la mémoire
    ~Liste() {
        cout << "Destruction de la liste..." << endl;
        while (tete != nullptr) {
            Element* temp = tete;
            tete = tete->suivant;
            delete temp; // libération mémoire
        }
        cout << "Liste détruite sans fuite mémoire." << endl;
    }
};

// ======================================
// 🔹 FONCTION PRINCIPALE
// ======================================
int main() {
    Liste maListe; // création d'une liste vide

    // Ajouts
    maListe.ajouterDebut(10);
    maListe.ajouterDebut(20);
    maListe.ajouterDebut(30);
    maListe.afficher();

    // Suppressions
    maListe.supprimerDebut();
    maListe.afficher();

    maListe.supprimerDebut();
    maListe.supprimerDebut();
    maListe.supprimerDebut(); // suppression alors que la liste est vide

    return 0;
}
