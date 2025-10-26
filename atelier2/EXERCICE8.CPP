#include <iostream>
#include <string>
using namespace std;

class Voiture {
private:
    // 🔹 Attributs
    string marque;
    string modele;
    int annee;
    float kilometrage;
    float vitesse;

public:
    // 🔹 1. Constructeur par défaut
    Voiture()
        : marque("Inconnue"), modele("Inconnu"), annee(0), kilometrage(0.0f), vitesse(0.0f) {
        cout << "Constructeur par défaut appelé 🚗" << endl;
    }

    // 🔹 2. Constructeur avec paramètres
    Voiture(const string& m, const string& mod, int a, float km, float v)
        : marque(m), modele(mod), annee(a), kilometrage(km), vitesse(v) {
        cout << "Constructeur avec paramètres appelé pour " << marque << " " << modele << endl;
    }

    // 🔹 3. Méthode pour accélérer
    void accelerer(float valeur) {
        if (valeur > 0) {
            vitesse += valeur;
            cout << "La voiture accélère de " << valeur << " km/h. Nouvelle vitesse : " << vitesse << " km/h.\n";
        } else {
            cout << "Valeur d'accélération invalide.\n";
        }
    }

    // 🔹 4. Méthode pour freiner
    void freiner(float valeur) {
        if (valeur > 0) {
            vitesse -= valeur;
            if (vitesse < 0) vitesse = 0;
            cout << "La voiture freine de " << valeur << " km/h. Nouvelle vitesse : " << vitesse << " km/h.\n";
        } else {
            cout << "Valeur de freinage invalide.\n";
        }
    }

    // 🔹 5. Méthode pour afficher les informations
    void afficherInfo() const {
        cout << "\n===== Informations sur la voiture =====\n";
        cout << "Marque       : " << marque << endl;
        cout << "Modèle       : " << modele << endl;
        cout << "Année        : " << annee << endl;
        cout << "Kilométrage  : " << kilometrage << " km" << endl;
        cout << "Vitesse      : " << vitesse << " km/h" << endl;
        cout << "========================================\n";
    }

    // 🔹 6. Méthode pour avancer
    void avancer(float distance) {
        if (distance > 0) {
            kilometrage += distance;
            cout << "La voiture a parcouru " << distance << " km. Nouveau kilométrage : " << kilometrage << " km.\n";
        } else {
            cout << "Distance invalide.\n";
        }
    }

    // 🔹 7. Destructeur
    ~Voiture() {
        cout << "Destruction de la voiture " << marque << " " << modele << " 🚙" << endl;
    }
};

// ==================== PROGRAMME PRINCIPAL ====================
int main() {
    cout << "=== Création d'une voiture par défaut ===\n";
    Voiture v1; // Appel du constructeur par défaut
    v1.afficherInfo();

    cout << "\n=== Création d'une voiture personnalisée ===\n";
    Voiture v2("Toyota", "Corolla", 2020, 35000.0f, 0.0f);
    v2.afficherInfo();

    cout << "\n=== Simulation de conduite ===\n";
    v2.accelerer(50);
    v2.avancer(120);
    v2.freiner(20);
    v2.afficherInfo();

    cout << "\nFin du programme.\n";

    return 0;
}
