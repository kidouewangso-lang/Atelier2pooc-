#include <iostream>
using namespace std;

// Fonction sans argument ni valeur de retour
void compteurAppel() {
    // Variable statique locale : elle conserve sa valeur entre les appels
    static int compteur = 0;
    compteur++; // Incrémentation à chaque appel

    cout << "appel numéro " << compteur << endl;
}

int main() {
    // On appelle plusieurs fois la fonction
    compteurAppel();
    compteurAppel();
    compteurAppel();
    compteurAppel();

    return 0;
}

