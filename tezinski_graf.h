
#ifndef TEZINSKI_GRAF_H
#define TEZINSKI_GRAF_H
#include <vector>
#include <utility>
#include <list>

using namespace std;

class TezinskiGraf {
    bool usmjeren;
    int broj_cvorova;
    vector<list<pair<int,double>>> lista_susjedstva;
    vector<vector<double>> W;
    public:
    TezinskiGraf(int n, bool usmjeren);
    void dodajGranu(int i, int j, double w);
    vector<double> DijkstraSporo(int pocetni);
    vector<double> DijkstraBrzo(int pocetni);
    pair<bool, vector<double>> BelmanFord(int);
    pair<double, vector<pair<int,int>>> Prim();
    pair<double, vector<pair<int,int>>> Kruskal();
    double maksimalanProtok(int pocetni, int krajnji);

    void print_all_pairs_shortest_path(vector<vector<int>>, int, int);
    vector<vector<double>> extend_shortest_paths(vector<vector<double>>&);
    vector<vector<double>> extend_shortest_paths(vector<vector<double>>&,vector<vector<double>>&);
    vector<vector<double>> slow_all_pairs_shortest_paths();
    vector<vector<double>> faster_all_pairs_shortest_paths();

    int min_length_negative_weight_cycle();
    vector<vector<double>> Floyd_Warshall();
    vector<vector<double>> Floyd_Warshall_predecessor();

    vector<vector<double>> Johnson();

};

class DisjunktniSkupovi {
    vector<int> roditelj;
    public:
    DisjunktniSkupovi(int n) {
        for(int i = 0; i < n; i++)
            roditelj.push_back(i);
    }
    int Nadji(int k) {
        if(roditelj[k] == k)
            return k;
        roditelj[k] = Nadji(roditelj[k]);
        return roditelj[k];
    }

    void Spoji(int i, int j) {
        roditelj[roditelj[j]] = roditelj[i];
    }
};



#endif
