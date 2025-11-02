#include <iostream>
#include <string>

using namespace std;

class Client {
public:
    int id;
    string nom;
    string prenom;

    // constructeur par défaut
    Client() : id(0), nom(""), prenom("") {}

    // constructeur avec valeurs
    Client(int id_, const string& nom_, const string& prenom_)
        : id(id_), nom(nom_), prenom(prenom_) {}

    // constructeur de copie
    Client(const Client& other)
        : id(other.id), nom(other.nom), prenom(other.prenom) {}

    // destructeur (pas indispensable ici car pas de ressource managée)
    ~Client() = default;

    void afficher() const {
        cout << "Client { id: " << id
             << ", nom: " << nom
             << ", prenom: " << prenom << " }";
    }
};

inline float calculInteret(float solde, float taux) {
    // petit utilitaire, inline pertinent pour éviter l'overhead d'un appel
    return solde * (1.0f + taux);
}

class Compte {
private:
    // pas d'autre ressource globale
public:
    int numero;
    float solde;
    Client* client;             // pointeur vers client (propriété du compte)
    static int nbComptes;       // compteur partagé

    // constructeur par défaut
    Compte()
        : numero(0), solde(0.0f), client(new Client()) {
        ++nbComptes;
        cout << "[Compte] créé (defaut). Total comptes: " << nbComptes << endl;
    }

    // constructeur avec paramètres (on fait une copie profonde du client)
    Compte(int numero_, float solde_, const Client& c)
        : numero(numero_), solde(solde_), client(new Client(c)) {
        ++nbComptes;
        cout << "[Compte] créé (param). Total comptes: " << nbComptes << endl;
    }

    // constructeur de copie (copie profonde)
    Compte(const Compte& other)
        : numero(other.numero), solde(other.solde),
          client(new Client(*other.client)) {
        ++nbComptes;
        cout << "[Compte] créé (copie). Total comptes: " << nbComptes << endl;
    }

    // destructeur : libère la mémoire du client associé
    ~Compte() {
        delete client;
        --nbComptes;
        cout << "[Compte] détruit. Total comptes: " << nbComptes << endl;
    }

    void afficher() const {
        cout << "Compte { numero: " << numero
             << ", solde: " << solde << ", ";
        if (client) client->afficher();
        else cout << "Client: null";
        cout << " }" << endl;
    }

    void appliquerInteret(float taux) {
        solde = calculInteret(solde, taux);
    }

    static void afficherNombreComptes() {
        cout << "Nombre total de comptes existants: " << nbComptes << endl;
    }
};

// définition de la variable statique
int Compte::nbComptes = 0;

int main() {
    // création de clients
    Client c1(1, "Dupont", "Jean");
    Client c2(2, "Martin", "Alice");

    // création de comptes
    Compte* pA1 = new Compte(1001, 1000.0f, c1);   // alloué dynamiquement
    Compte a2(1002, 2500.0f, c2);                  // sur la pile
    Compte a3;                                     // compte par défaut

    Compte::afficherNombreComptes();

    cout << "\nAffichage des comptes initiaux:\n";
    pA1->afficher();
    a2.afficher();
    a3.afficher();

    // copie d'un compte
    cout << "\nCopie du compte a2 dans a4:\n";
    Compte a4 = a2; // utilise constructeur de copie (copie profonde)
    a4.afficher();
    Compte::afficherNombreComptes();

    // appliquer intérêts
    cout << "\nApplication d'intérêts sur pA1 (taux 5%) et a2 (taux 3%):\n";
    pA1->appliquerInteret(0.05f);
    a2.appliquerInteret(0.03f);
    pA1->afficher();
    a2.afficher();

    // suppression d'un compte dynamique
    cout << "\nSuppression de pA1:\n";
    delete pA1; // déclenche le destructeur et décrémente le compteur
    Compte::afficherNombreComptes();

    cout << "\nFin de main, les comptes locaux seront détruits automatiquement.\n";
    return 0;
}

/*
Réponses courtes (réflexion) :
1) Copie superficielle : copier les pointeurs (partage la même mémoire). Copie profonde : dupliquer les objets pointés (chaque instance a sa propre mémoire).
2) Le compteur doit être static pour être partagé par toutes les instances et refléter le nombre total global de comptes.
3) Méthode statique : appartient à la classe, pas à une instance (pas de this). Méthode normale : agit sur une instance et peut accéder aux membres non statiques.
4) Inline pertinent pour de petites fonctions fréquentes pour réduire l'overhead d'appel ; le compilateur peut ignorer inline.
5) Oublier de libérer la mémoire cause des fuites mémoire ; si on supprime plusieurs fois la même mémoire (double delete) -> comportement indéfini.
*/