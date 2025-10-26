#include <iostream>
#include <string>

using namespace std;

// Fonction récursive qui affiche toutes les permutations de s,
// en permutant les caractères entre les indices l et r inclus.
void permute(string &s, int l, int r) {
    if (l == r) {
        cout << s << '\n';
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap(s[l], s[i]);
        permute(s, l + 1, r);
        swap(s[l], s[i]); // backtrack
    }
}

int main() {
    string s;
    // Lire une ligne (chaîne) depuis l'entrée standard
    if (!getline(cin, s)) return 0;
    if (!s.empty())
        permute(s, 0, static_cast<int>(s.size()) - 1);
    return 0;
}