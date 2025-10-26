#include <iostream>
#include <cmath> 
using namespace std;

class Vecteur3D {
private:
    float x, y, z; // composantes du vecteur

public:
    // 🔹 Constructeur avec valeurs par défaut
    Vecteur3D(float x_ = 0, float y_ = 0, float z_ = 0) : x(x_), y(y_), z(z_) {}

    // 🔹 Fonction d'affichage
    void afficher() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }

    // 🔹 Fonction somme : renvoie la somme de deux vecteurs (par valeur)
    Vecteur3D somme(const Vecteur3D& v) const {
        return Vecteur3D(x + v.x, y + v.y, z + v.z);
    }

    // 🔹 Produit scalaire
    float produitScalaire(const Vecteur3D& v) const {
        return (x * v.x + y * v.y + z * v.z);
    }

    // 🔹 Vérifie si deux vecteurs ont les mêmes composantes
    bool coincide(const Vecteur3D& v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    // 🔹 Calcul de la norme du vecteur
    float norme() const {
        return sqrt(x * x + y * y + z * z);
    }

    // 🔹 Méthode normax (version 1 : retour par valeur)
    Vecteur3D normaxValeur(const Vecteur3D& v) const {
        if (this->norme() >= v.norme())
            return *this;
        else
            return v;
    }

    // 🔹 Méthode normax (version 2 : retour par adresse)
    const Vecteur3D* normaxAdresse(const Vecteur3D* v) const {
        if (this->norme() >= v->norme())
            return this;
        else
            return v;
    }

    // 🔹 Méthode normax (version 3 : retour par référence)
    const Vecteur3D& normaxReference(const Vecteur3D& v) const {
        if (this->norme() >= v.norme())
            return *this;
        else
            return v;
    }
};

// ==================== 🔸 Fonction principale ====================

int main() {
    Vecteur3D v1(3, 4, 0);   // norme = 5
    Vecteur3D v2(1, 2, 2);   // norme ≈ 3

    cout << "Vecteur 1 : "; v1.afficher(); cout << endl;
    cout << "Vecteur 2 : "; v2.afficher(); cout << endl;

    // Somme
    cout << "\nSomme : ";
    Vecteur3D v3 = v1.somme(v2);
    v3.afficher();

    // Produit scalaire
    cout << "\nProduit scalaire : " << v1.produitScalaire(v2) << endl;

    // Coincidence
    cout << "\nLes vecteurs sont identiques ? " << (v1.coincide(v2) ? "Oui" : "Non") << endl;

    // Normes
    cout << "\nNorme v1 : " << v1.norme() << endl;
    cout << "Norme v2 : " << v2.norme() << endl;

    // Comparaison par valeur
    cout << "\n🔹 Par valeur -> Le vecteur le plus long : ";
    Vecteur3D maxVal = v1.normaxValeur(v2);
    maxVal.afficher(); cout << endl;

    // Comparaison par adresse
    cout << "🔹 Par adresse -> Le vecteur le plus long : ";
    const Vecteur3D* maxAdr = v1.normaxAdresse(&v2);
    maxAdr->afficher(); cout << endl;

    // Comparaison par référence
    cout << "🔹 Par référence -> Le vecteur le plus long : ";
    const Vecteur3D& maxRef = v1.normaxReference(v2);
    maxRef.afficher(); cout << endl;

    return 0;
}
