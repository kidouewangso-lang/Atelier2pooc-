#include <iostream>
using namespace std;

// Classe qui compte combien de fois on appelle sa méthode
class Compteur {
private:
    // Attribut statique partagé par TOUTES les instances
    static int nombreAppels;
    


public:
    // Méthode sans argument ni valeur de retour
    void afficherAppel() {
     nombreAppels++; // Incrémentation à chaque appel
   
        cout << "appel numéro " << nombreAppels << endl;
    }

   
};

// ⚠️ Définition et initialisation de l’attribut statique (obligatoire)
int Compteur::nombreAppels = 0;

int main() {
    Compteur c1, c2,c3; // Deux objets, mais le compteur est partagé !

    c1.afficherAppel();
    c2.afficherAppel();
    
    
    c3.afficherAppel();

    return 0;
}
