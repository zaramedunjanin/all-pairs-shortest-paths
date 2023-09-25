#ifndef GRAF
#define GRAF
#include <vector>
#include <list>
#include <stack>
using namespace std;

class Graf{
    int broj_cvorova;
    bool usmjeren;
    vector<list<int>> lista_susjedstva;

    void DFSRek(int pocetni, vector<bool> &posjecen, vector<pair<int,int>> &vremena, int &time);
    void DFS2Rek(int pocetni, vector<bool> &posjecen,stack<int> &redoslijedZavrsavanja);
    void DFS3Rek(int pocetni, vector<bool> &posjecen,list<int> &komponente);
    public:
    Graf(int n, bool usmjeren = false):broj_cvorova(n), usmjeren(usmjeren) { lista_susjedstva.resize(n); }
    void dodajGranu(int i, int j);
    void BFS(int pocetni = 0);
    void DFS(int pocetni = 0);
    void Udaljenosti(int pocetni);
    vector<int> put(int pocetni, int krajnji);
    list<int> Topoloski_sort();
    void TopoloskiRek(int cvor,vector<bool>&posjecen,list<int>&rezultat);
    void ispisi();
    list<list<int>> komponenteJakePovezanosti();
    vector<vector<int>> transitive_closure();
    vector<vector<int>> fast_transitive_closure();
};

#endif // GRAF
