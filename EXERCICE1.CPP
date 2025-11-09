// /home/wang/DOSSIER.CPP/EXERCICE1.CPP
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

// Classe de base
class Ressource {
protected:
    int id;
    string titre;
    string auteur;
    int annee;
public:
    Ressource(int id_, const string& titre_, const string& auteur_, int annee_)
        : id(id_), titre(titre_), auteur(auteur_), annee(annee_) {}
    virtual ~Ressource() = default;

    // accesseurs
    int getId() const { return id; }
    const string& getTitre() const { return titre; }
    const string& getAuteur() const { return auteur; }
    int getAnnee() const { return annee; }

    virtual void afficherInfos() const {
        cout << "[Ressource] id=" << id
             << ", titre=\"" << titre << "\""
             << ", auteur=\"" << auteur << "\""
             << ", annee=" << annee << endl;
    }

    // version par défaut de telecharger dans Ressource
    virtual void telecharger() const {
        cout << "Telechargement generique de la ressource \"" << titre << "\" (id=" << id << ")" << endl;
    }

    // surcharge de l'opérateur ==
    bool operator==(const Ressource& other) const {
        return id == other.id;
    }
};

// Interface Telechargeable (classe non liée à Ressource)
class Telechargeable {
public:
    virtual ~Telechargeable() = default;
    virtual void telecharger() const {
        cout << "[Telechargeable] Telechargement (par défaut)" << endl;
    }
    void afficherMessage() const {
        cout << "[Telechargeable] Cette ressource est telechargeable." << endl;
    }
};

// Livre: héritage multiple Ressource + Telechargeable
class Livre : public Ressource, public Telechargeable {
    int nbPages;
public:
    Livre(int id_, const string& titre_, const string& auteur_, int annee_, int nbPages_)
        : Ressource(id_, titre_, auteur_, annee_), nbPages(nbPages_) {}

    void afficherInfos() const override {
        cout << "[Livre] id=" << id
             << ", titre=\"" << titre << "\""
             << ", auteur=\"" << auteur << "\""
             << ", annee=" << annee
             << ", pages=" << nbPages << endl;
    }

    // redéfinition de telecharger (résout l'ambiguïté)
    void telecharger() const override {
        cout << "[Livre] Telechargement du livre \"" << titre << "\" (" << nbPages << " pages)" << endl;
    }
};

// Magazine
class Magazine : public Ressource, public Telechargeable {
    int numero;
public:
    Magazine(int id_, const string& titre_, const string& auteur_, int annee_, int numero_)
        : Ressource(id_, titre_, auteur_, annee_), numero(numero_) {}

    void afficherInfos() const override {
        cout << "[Magazine] id=" << id
             << ", titre=\"" << titre << "\""
             << ", editeur=\"" << auteur << "\""
             << ", annee=" << annee
             << ", numero=" << numero << endl;
    }

    void telecharger() const override {
        cout << "[Magazine] Telechargement du magazine \"" << titre << "\" (numero " << numero << ")" << endl;
    }
};

// Video
class Video : public Ressource, public Telechargeable {
    double duree; // en minutes
public:
    Video(int id_, const string& titre_, const string& auteur_, int annee_, double duree_)
        : Ressource(id_, titre_, auteur_, annee_), duree(duree_) {}

    void afficherInfos() const override {
        cout << "[Video] id=" << id
             << ", titre=\"" << titre << "\""
             << ", realisateur=\"" << auteur << "\""
             << ", annee=" << annee
             << ", duree=" << duree << " min" << endl;
    }

    void telecharger() const override {
        cout << "[Video] Telechargement de la video \"" << titre << "\" (" << duree << " min)" << endl;
    }
};

// Mediatheque: gestion des ressources
class Mediatheque {
    vector<shared_ptr<Ressource>> ressources;
public:
    void ajouter(shared_ptr<Ressource> r) {
        ressources.push_back(move(r));
    }

    void afficherToutes() const {
        cout << "=== Contenu de la mediatheque ===" << endl;
        for (const auto& r : ressources) r->afficherInfos();
        cout << "=== Fin ===" << endl;
    }

    // recherche par titre (sous-chaine)
    vector<shared_ptr<Ressource>> rechercher(const string& titre) const {
        vector<shared_ptr<Ressource>> res;
        for (const auto& r : ressources) {
            if (r->getTitre().find(titre) != string::npos) res.push_back(r);
        }
        return res;
    }

    // recherche par annee
    vector<shared_ptr<Ressource>> rechercher(int annee) const {
        vector<shared_ptr<Ressource>> res;
        for (const auto& r : ressources) {
            if (r->getAnnee() == annee) res.push_back(r);
        }
        return res;
    }

    // recherche par auteur + annee
    vector<shared_ptr<Ressource>> rechercher(const string& auteur, int annee) const {
        vector<shared_ptr<Ressource>> res;
        for (const auto& r : ressources) {
            if (r->getAuteur() == auteur && r->getAnnee() == annee) res.push_back(r);
        }
        return res;
    }
};

int main() {
    // creation d'objets
    Livre l1(1, "De la terre a la lune", "Jules Verne", 1865, 320);
    Livre l2(2, "Le Petit Prince", "Antoine de Saint-Exupery", 1943, 96);
    Magazine m1(3, "Science et Vie", "Science & Vie", 2020, 1284);
    Video v1(4, "Le Voyage de Chihiro", "Hayao Miyazaki", 2001, 125.0);

    // tester afficherInfos()
    l1.afficherInfos();
    l2.afficherInfos();
    m1.afficherInfos();
    v1.afficherInfos();

    cout << endl;

    // tester telecharger() — ici l'appel appelle la version de la classe dérivée
    l1.telecharger();
    m1.telecharger();
    v1.telecharger();

    cout << endl;

    // appel qualifié pour afficher comportement des bases si nécessaire
    // appeler la version de Ressource
    l1.Ressource::telecharger();
    // appeler la version Telechargeable
    l1.Telechargeable::telecharger();
    // afficher message Telechargeable
    l1.afficherMessage();

    cout << endl;

    // comparaison de ressources (operateur == compare les id)
    cout << "Comparer l1 et l2: ";
    if (l1 == l2) cout << "identiques (meme id)" << endl; else cout << "différents (id differents)" << endl;

    // creation d'une mediatheque et ajout via pointeurs partages
    Mediatheque med;
    med.ajouter(make_shared<Livre>(l1));
    med.ajouter(make_shared<Livre>(l2));
    med.ajouter(make_shared<Magazine>(m1));
    med.ajouter(make_shared<Video>(v1));

    cout << endl;
    med.afficherToutes();

    // chercher par titre
    auto resTitre = med.rechercher("Petit");
    cout << "Recherche par titre \"Petit\": " << resTitre.size() << " trouvee(s)" << endl;
    for (auto& r : resTitre) r->afficherInfos();

    // chercher par annee
    auto resAnnee = med.rechercher(2001);
    cout << "Recherche par annee 2001: " << resAnnee.size() << " trouvee(s)" << endl;
    for (auto& r : resAnnee) r->afficherInfos();

    // chercher par auteur + annee
    auto resAuteurAnnee = med.rechercher("Hayao Miyazaki", 2001);
    cout << "Recherche par auteur \"Hayao Miyazaki\" et annee 2001: " << resAuteurAnnee.size() << " trouvee(s)" << endl;
    for (auto& r : resAuteurAnnee) r->afficherInfos();

    cout << endl;

    // depuis un pointeur vers Ressource, telecharger via Telechargeable nécessite cast
    auto p = med.rechercher(1865);
    if (!p.empty()) {
        shared_ptr<Ressource> pr = p.front();
        pr->afficherInfos();
        // appel la telecharger de Ressource (polymorphe)
        pr->telecharger();
        // si on veut appeler Telechargeable::telecharger, on cast
        if (auto pt = dynamic_cast<Telechargeable*>(pr.get())) {
            pt->telecharger();
            pt->afficherMessage();
        } else {
            cout << "La ressource n'est pas telechargeable via Telechargeable." << endl;
        }
    }

    return 0;
}