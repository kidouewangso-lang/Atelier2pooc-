#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

class AgentBancaire;
class Banque;

class Client {
private:
    string nom;
    string cin; // sensitive
    int clientId;

    friend class AgentBancaire;
    friend class Banque;

public:
    Client() = default;
    Client(string n, string c, int id) : nom(std::move(n)), cin(std::move(c)), clientId(id) {}

    // Non-sensitive public view
    void afficherPublic() const {
        cout << "Client: " << nom << " (ID: " << clientId << ")\n";
    }
};

class CompteBancaire {
private:
    string numero;
    double solde;
    string codeSecret; // sensitive
    shared_ptr<Client> proprietaire;

    friend class AgentBancaire;
    friend class Banque;

    static int nextNumero() {
        static int counter = 1000;
        return counter++;
    }

public:
    CompteBancaire() = default;
    CompteBancaire(shared_ptr<Client> owner, double initial = 0.0)
        : numero("ACC" + to_string(nextNumero())), solde(initial),
          codeSecret(to_string(rand() % 9000 + 1000)), proprietaire(std::move(owner)) {}

    // Public operations that require the account secret (simulates owner operations)
    bool retirer(double montant, const string& code) {
        if (code != codeSecret) return false;
        if (montant <= 0 || montant > solde) return false;
        solde -= montant;
        return true;
    }

    void deposer(double montant) {
        if (montant > 0) solde += montant;
    }

    // Safe public view (does not expose sensitive data)
    void afficherPublic() const {
        cout << left << setw(10) << numero
             << " | Solde: " << setw(10) << fixed << setprecision(2) << solde
             << " | Propriétaire: ";
        if (proprietaire) cout << proprietaire->nom << " (ID:" << proprietaire->clientId << ")";
        cout << '\n';
    }
};

class AgentBancaire {
private:
    string nomAgent;
    int agentId;

public:
    AgentBancaire(string n, int id) : nomAgent(std::move(n)), agentId(id) {}

    // Agent can view secret code of a compte
    string consulterCode(const CompteBancaire& c) const {
        return c.codeSecret; // friend access
    }

    // Agent can view client's sensitive CIN
    string consulterCIN(const Client& cl) const {
        return cl.cin; // friend access
    }

    // Agent can transfer between accounts bypassing owner code
    bool transferer(CompteBancaire& from, CompteBancaire& to, double montant) const {
        if (montant <= 0 || montant > from.solde) return false;
        from.solde -= montant;
        to.solde += montant;
        return true;
    }

    void afficherAgent() const {
        cout << "Agent: " << nomAgent << " (ID: " << agentId << ")\n";
    }
};

class Banque {
private:
    vector<shared_ptr<Client>> clients;
    vector<shared_ptr<CompteBancaire>> comptes;

public:
    shared_ptr<Client> ajouterClient(const string& nom, const string& cin, int id) {
        auto c = make_shared<Client>(nom, cin, id);
        clients.push_back(c);
        return c;
    }

    shared_ptr<CompteBancaire> creerCompte(shared_ptr<Client> proprietaire, double initial = 0.0) {
        auto a = make_shared<CompteBancaire>(proprietaire, initial);
        comptes.push_back(a);
        return a;
    }

    void afficherClients() const {
        cout << "=== Clients (public) ===\n";
        for (const auto& c : clients) c->afficherPublic();
    }

    void afficherComptesPublic() const {
        cout << "=== Comptes (public) ===\n";
        for (const auto& a : comptes) a->afficherPublic();
    }

    // Audit internal: Banque is friend of CompteBancaire and Client so can show sensitive info
    void rapportAudit() const {
        cout << "\n=== RAPPORT D'AUDIT (INTERNE) ===\n";
        cout << left << setw(10) << "Compte" << " | " << setw(12) << "Solde"
             << " | " << setw(8) << "Code" << " | " << "Propriétaire (CIN)\n";
        cout << "-------------------------------------------------------------\n";
        for (const auto& a : comptes) {
            cout << left << setw(10) << a->numero
                 << " | " << setw(12) << fixed << setprecision(2) << a->solde
                 << " | " << setw(8) << a->codeSecret << " | ";
            if (a->proprietaire) {
                cout << a->proprietaire->nom << " (CIN: " << a->proprietaire->cin << ")";
            }
            cout << '\n';
        }
    }

    // helper to find account by number
    shared_ptr<CompteBancaire> trouverCompte(const string& numero) {
        for (auto& a : comptes) if (a->numero == numero) return a;
        return nullptr;
    }
};

int main() {
    srand(1);

    Banque banque;

    // créer clients
    auto cl1 = banque.ajouterClient("Alice Dupont", "CIN12345", 1);
    auto cl2 = banque.ajouterClient("Bob Martin", "CIN67890", 2);

    // créer comptes
    auto acc1 = banque.creerCompte(cl1, 1000.0);
    auto acc2 = banque.creerCompte(cl2, 500.0);

    // opérations publiques
    acc1->deposer(250.0); // dépôt
    bool w = acc2->retirer(100.0, acc2->codeSecret); // Impossible from here (private) => compile error if used
    // The above line is commented because main cannot access codeSecret.
    // Instead, simulate owner withdrawal by calling retirer with the correct code (we don't have it).
    // So we perform deposit and use Agent for confidential ops.

    // créer agent
    AgentBancaire agent("Eve Agent", 9001);

    // Agent inspects codes and CINs (authorized)
    cout << "Agent consulte le code du compte 1: " << agent.consulterCode(*acc1) << '\n';
    cout << "Agent consulte le CIN du propriétaire du compte 2: " << agent.consulterCIN(*cl2) << '\n';

    // Agent effectue un virement confidentiel de acc1 -> acc2
    bool ok = agent.transferer(*acc1, *acc2, 300.0);
    cout << "Virement par agent " << (ok ? "réussi" : "échoué") << "\n\n";

    // Affichages publics
    banque.afficherClients();
    banque.afficherComptesPublic();

    // Rapport d'audit interne affichant les données sensibles
    banque.rapportAudit();

    return 0;
}