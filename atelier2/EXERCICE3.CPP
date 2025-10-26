// EXO3FORMATABLEAU.CPP
// Deux versions : (a) formalisme tableau, (b) formalisme pointeur
#include <iostream>

void version_tableau() {
    std::cout << "Version (a) - formalisme tableau\n";
    int tab[10];
    std::cout << "Entrez 10 entiers (séparés par espaces ou retours) :\n";
    for (int i = 0; i < 10; ++i) {
        std::cin >> tab[i]; // seul formalisme tableau utilisé
    }

    int min = tab[0];
    int max = tab[0];
    for (int i = 1; i < 10; ++i) {
        if (tab[i] < min) min = tab[i];
        if (tab[i] > max) max = tab[i];
    }

    std::cout << "Min = " << min << ", Max = " << max << "\n\n";
}

void version_pointeur() {
    std::cout << "Version (b) - formalisme pointeur\n";
    int tab[10];
    std::cout << "Entrez 10 entiers (séparés par espaces ou retours) :\n";
    // lecture : on peut utiliser un pointeur pour stocker, ici on illustre
    int *p = tab;
    for (int i = 0; i < 10; ++i) {
        std::cin >> *(p + i); // écriture via arithmétique de pointeur
    }

    // initialisation via pointeur
    int *ptr = tab; // début du tableau
    int min = *ptr;
    int max = *ptr;
    // parcours uniquement avec des pointeurs
    for (int i = 1; i < 10; ++i) {
        int val = *(ptr + i);
        if (val < min) min = val;
        if (val > max) max = val;
    }

    std::cout << "Min = " << min << ", Max = " << max << "\n\n";
}

int main() {
    // Exécution séquentielle des deux versions.
    // L'utilisateur devra entrer 10 nombres pour chaque version.
    version_tableau();
    version_pointeur();
    return 0;
}