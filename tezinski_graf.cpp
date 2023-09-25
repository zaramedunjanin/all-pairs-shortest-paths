#include "tezinski_graf.h"
#include <limits.h>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>

TezinskiGraf::TezinskiGraf(int n, bool usmjeren = false):broj_cvorova(n),usmjeren(usmjeren){
    W.resize(broj_cvorova);
    for(int i = 0; i< broj_cvorova; i++){
        W[i].resize(broj_cvorova);
        for(int j = 0; j< broj_cvorova; j++){
            if(i == j)
                W[i][j] = 0;
            else
                W[i][j] = INT_MAX;
        }
        }

    lista_susjedstva.resize(broj_cvorova);
}

void TezinskiGraf::dodajGranu(int i, int j, double w) {
    lista_susjedstva[i].push_back({j,w});
    W[i][j] = w;
    if(!usmjeren)
        lista_susjedstva[j].push_back({i,w});
}

vector<double> TezinskiGraf::DijkstraSporo(int pocetni) {
    vector<bool> obradjeni(broj_cvorova, false);
    vector<double> udaljenosti(broj_cvorova, INT_MAX);
    obradjeni[pocetni] = true;
    udaljenosti[pocetni] = 0;
    int trenutni = pocetni;

    for(int i = 0; i < broj_cvorova - 1; i++) {
        for(auto el: lista_susjedstva[trenutni])
            if(!obradjeni[el.first] && udaljenosti[trenutni] + el.second < udaljenosti[el.first])
                udaljenosti[el.first] = udaljenosti[trenutni] + el.second;

        pair<double,int> minimum = {INT_MAX,-1};
        for(int j = 0; j < broj_cvorova; j++)
            if(!obradjeni[j] && udaljenosti[j] < minimum.first)
                minimum = {udaljenosti[j], j};

        trenutni = minimum.second;
        obradjeni[trenutni] = true;
    }
    return udaljenosti;
}

pair<bool, vector<double>> TezinskiGraf::BelmanFord(int pocetni) {

    vector<double> udaljenosti(broj_cvorova, INT_MAX);
    udaljenosti[pocetni] = 0;
    for(int iteracija = 1; iteracija < broj_cvorova; iteracija++)
        for(int i = 0; i < broj_cvorova; i++)
            for(auto el: lista_susjedstva[i])
                if(udaljenosti[el.first] > udaljenosti[i] + el.second)
                    udaljenosti[el.first] = udaljenosti[i] + el.second;

    for(int i = 0; i < broj_cvorova; i++)
        for(auto el: lista_susjedstva[i])
            if(udaljenosti[el.first] > udaljenosti[i] + el.second)
                return {false, udaljenosti};

    return {true, udaljenosti};
}

pair<double, vector<pair<int,int>>> TezinskiGraf::Prim() {
    int pocetni = 0;
    vector<bool> obradjeni(broj_cvorova, false);
    vector<double> udaljenosti(broj_cvorova, INT_MAX);  //udaljenost od obradjenog dijela
    obradjeni[pocetni] = true;
    udaljenosti[pocetni] = 0;
    int trenutni = pocetni;
    set<pair<double, int>> stablo;
    vector<int> prethodnik(broj_cvorova, -1);
    pair<double, vector<pair<int,int>>> MST{0,vector<pair<int,int>> ()};

    for(int i = 0; i < broj_cvorova - 1; i++) {
        for(auto el: lista_susjedstva[trenutni]) {
            if(!obradjeni[el.first] && el.second < udaljenosti[el.first]) {
                if(stablo.find({udaljenosti[el.first],el.first}) != stablo.end())
                    stablo.erase({udaljenosti[el.first],el.first});

                udaljenosti[el.first] = el.second;
                stablo.insert({udaljenosti[el.first],el.first});
                prethodnik[el.first] = trenutni;
            }
        }
        int novi = stablo.begin()->second;
        MST.first += stablo.begin()->first;
        MST.second.push_back({prethodnik[novi], novi});
        stablo.erase(stablo.begin());
        trenutni = novi;
        obradjeni[trenutni] = true;
    }
    return MST;
}


pair<double, vector<pair<int,int>>> TezinskiGraf::Kruskal() {

    vector<pair<double,pair<int,int>>> grane;
    for(int i = 0; i < broj_cvorova; i++)
        for(auto el:lista_susjedstva[i]) {
            if(i < el.first)
                grane.push_back({el.second,{i,el.first}});
        }

    sort(grane.begin(),grane.end());
    pair<double, vector<pair<int,int>>> MST{0,vector<pair<int,int>> ()};
    DisjunktniSkupovi ds(broj_cvorova);
    int brojac = 0;
    for(int i = 0; i < grane.size(); i++) {
        if(ds.Nadji(grane[i].second.first) != ds.Nadji(grane[i].second.second)) {
            ds.Spoji(grane[i].second.first,grane[i].second.second);
            brojac++;
            MST.first += grane[i].first;
            MST.second.push_back(grane[i].second);
        }
        if(brojac == broj_cvorova - 1)
            break;
    }
    return MST;
}


vector<double> TezinskiGraf::DijkstraBrzo(int pocetni) {
    vector<bool> obradjeni(broj_cvorova, false);
    vector<double> udaljenosti(broj_cvorova, INT_MAX);
    obradjeni[pocetni] = true;
    udaljenosti[pocetni] = 0;
    int trenutni = pocetni;
    set<pair<double, int>> stablo;
    for(int i = 0; i < broj_cvorova - 1; i++) {
        for(auto el: lista_susjedstva[trenutni]) {
            if(!obradjeni[el.first] && udaljenosti[trenutni] + el.second < udaljenosti[el.first]) {
                if(stablo.find({udaljenosti[el.first],el.first}) != stablo.end())
                    stablo.erase({udaljenosti[el.first],el.first});
                udaljenosti[el.first] = udaljenosti[trenutni] + el.second;
                stablo.insert({udaljenosti[el.first],el.first});

            }

        }
        trenutni = stablo.begin()->second;
        stablo.erase(stablo.begin());
        obradjeni[trenutni] = true;

    }
    return udaljenosti;
}

double TezinskiGraf::maksimalanProtok(int pocetni, int krajnji) {
    int n = broj_cvorova;
    //najprije pravimo matricu udaljenosti pomocnog grafa i popunjavamo je nulama
    vector<vector<double>> matricaUdaljenosti(n);
    for(int i = 0; i < n; i++)
        matricaUdaljenosti[i].resize(n);

    //sada pravimo listu susjedstva pomocnog grafa
    //bitno je samo da li postoji grana (ne i njen kapacitet)
    //moramo pamtiti i da li je ta grana u originalnom grafu (true ako jeste)
    vector<list<pair<int,bool>>> susjedi(n);
    for(int i=0;i<n;i++)
        for(auto it = lista_susjedstva[i].begin();it!=lista_susjedstva[i].end();it++) {
            susjedi[i].push_back({it->first,true});
            susjedi[it->first].push_back({i,false});
            matricaUdaljenosti[i][it->first] = it->second;
            //na pocetku samo postoji grana od i do it->first koja je jednaka kapacitetu
            //grana u suprotnom smjeru zasad ostaje na 0
        }

    double maksimalan_protok = 0;
    //sada trazimo puteve od pocetnog do krajnjeg u pomocnom grafu
    //kada vise ne bude puteva onda prekidamo petlju
    while(true) {
        //koristimo BFS
        queue<int> red;
        red.push(pocetni);
        //za svaki cvor pamtimo ko ga je pronasao kako bi rekonstruisali put
        //-1 znaci da nije pronadjen, a -2 da se radi o pocetnom cvoru
        //pored toga pamtimo da li ta grana po kojoj je pronadjen pripada originalnom grafu
        vector<pair<int,bool>> ko_ga_je_nasao(n,{-1,false});
        ko_ga_je_nasao[pocetni].first = -2;
        while(!red.empty()) {
            int trenutni = red.front();
            red.pop();
            for(auto it = susjedi[trenutni].begin();it!=susjedi[trenutni].end();it++) {
                //moguce je da u pomocnom grafu postoji grana ali ako je njena tezina 0 to znaci da je u sustini nema
                if(matricaUdaljenosti[trenutni][it->first] == 0)
                continue;

                if(ko_ga_je_nasao[it->first].first == -1) {
                    red.push(it->first);
                    ko_ga_je_nasao[it->first] = {trenutni,it->second};
                }
            }
            //ako smo vec nasli krajnji nema potrebe dalje traziti
            if(ko_ga_je_nasao[krajnji].first != -1)
                break;
        }
        //ako nema puta znaci da smo nasli najveci protok
        if(ko_ga_je_nasao[krajnji].first == -1)
            break;
        //sada treba rekonstruisati put
        //u putu cuvamo grane i za svaku granu pamtimo da li grana pripada originalnom grafu
        vector<pair<pair<int,int>,bool>> put;
        //usput ćemo i vidjeti koja je najmanja grana na tom putu
        double duzina_najmanje_grane = INT_MAX;
        int trenutni = krajnji;
        do {
            put.push_back({{ko_ga_je_nasao[trenutni].first,trenutni},ko_ga_je_nasao[trenutni].second});
            if(matricaUdaljenosti[ko_ga_je_nasao[trenutni].first][trenutni] < duzina_najmanje_grane)
                duzina_najmanje_grane = matricaUdaljenosti[ko_ga_je_nasao[trenutni].first][trenutni];

            trenutni = ko_ga_je_nasao[trenutni].first;
        } while(trenutni != pocetni);
        //povecavamo protok za vrijednost najmanje grane
        maksimalan_protok += duzina_najmanje_grane;
        //modifikujemo graf
        for(int i = 0;i<put.size();i++) {
            cout<<"("<<put[i].first.first<<","<<put[i].first.second<<")";
            if(put[i].second) {
                matricaUdaljenosti[put[i].first.first][put[i].first.second] -= duzina_najmanje_grane;
                matricaUdaljenosti[put[i].first.second][put[i].first.first] += duzina_najmanje_grane;
            }
            else {
                matricaUdaljenosti[put[i].first.first][put[i].first.second] += duzina_najmanje_grane;
                matricaUdaljenosti[put[i].first.second][put[i].first.first] -= duzina_najmanje_grane;
            }
        }
        cout<<endl;
    }
    return maksimalan_protok;
}

//Implementacija algoritama

void TezinskiGraf::print_all_pairs_shortest_path(vector<vector<int>> predecessor_matrix, int i, int j){
    if(i == j)
        cout<<i;
    else if(predecessor_matrix[i][j] == 0)
        cout<<"No path from "<<i<<" to "<<j<<" exists";
    else{
        print_all_pairs_shortest_path(predecessor_matrix,i,predecessor_matrix[i][j]);
        cout<<j;
    }
}

vector<vector<double>> TezinskiGraf::extend_shortest_paths(vector<vector<double>> &L){
    vector<vector<double>> l(broj_cvorova,vector<double> (broj_cvorova, {INT_MAX}));

    for(int i = 0; i < broj_cvorova; i++)
        for(int j = 0; j < broj_cvorova; j++){
            for(int k = 0; k < broj_cvorova; k++)
                l[i][j] = min(l[i][j], L[i][k]+W[k][j]);
        }
    return l;
}

vector<vector<double>> TezinskiGraf::extend_shortest_paths(vector<vector<double>> &L1, vector<vector<double>> &L2){
    vector<vector<double>> l(broj_cvorova,vector<double> (broj_cvorova, {INT_MAX}));

    for(int i = 0; i < broj_cvorova; i++)
        for(int j = 0; j < broj_cvorova; j++){
            for(int k = 0; k < broj_cvorova; k++)
                l[i][j] = min(l[i][j], L1[i][k]+L2[k][j]);
        }
    return l;
}

vector<vector<double>> TezinskiGraf::slow_all_pairs_shortest_paths(){
    vector<vector<double>> L = W;
    for(int m = 0; m < broj_cvorova-1; m++){
        //Ispisivanje koraka
        for(int i = 0; i< L.size(); i++){
            for(int j = 0; j< L[i].size(); j++)
                cout<<L[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
        L = extend_shortest_paths(L);


    }
    return L;
}

vector<vector<double>> TezinskiGraf::faster_all_pairs_shortest_paths(){
    vector<vector<double>> L = W;
    int m = 1;
    while(m < broj_cvorova-1){
        //Ispisivanje koraka
        for(int i = 0; i< L.size(); i++){
            for(int j = 0; j< L[i].size(); j++)
                cout<<L[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
        L = extend_shortest_paths(L, L);

        m *= 2;
    }
    //Ispisivanje koraka
    for(int i = 0; i< L.size(); i++){
        for(int j = 0; j< L[i].size(); j++)
            cout<<L[i][j]<<" ";
        cout<<endl;
        }
    cout<<endl;
    return L;
}

int TezinskiGraf::min_length_negative_weight_cycle(){
    vector<vector<double>> w = W;
    for(int m = 0; m < broj_cvorova-1; m++){
        w = extend_shortest_paths(w,w);
        for(int i = 0; i<broj_cvorova; i++){
            for(int j = 0; j<broj_cvorova; j++){
                if(i == j && w[i][j]<0)
                    return m;

            }
        }
    }
    return 0;
}

vector<vector<double>> TezinskiGraf::Floyd_Warshall(){
    vector<vector<double>> D = W;
    for(int k = 0; k < broj_cvorova; k++)
        for(int i = 0; i < broj_cvorova; i ++)
            for(int j = 0; j < broj_cvorova; j++)
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

    return D;
}

vector<vector<double>> TezinskiGraf::Floyd_Warshall_predecessor(){
    vector<vector<double>> D = W;
    vector<vector<int>> predecessor_matrix(broj_cvorova, vector<int> (broj_cvorova,{-1}));

    for(int k = 0; k < broj_cvorova; k++){
        for(int i = 0; i < broj_cvorova; i++){
            for(int j = 0; j < broj_cvorova; j++){
                if(k == 0)
                    if(W[i][j] < INT_MAX && i != j)
                    predecessor_matrix[i][j] = i;
                if(D[i][j] > D[i][k]+D[k][j])
                    predecessor_matrix[i][j] = predecessor_matrix[k][j];
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
    return D;
}

vector<vector<double>> TezinskiGraf::Johnson(){
    vector<double> h(broj_cvorova,{-1});
    vector<vector<double>> D(broj_cvorova, vector<double> (broj_cvorova,{INT_MAX}));
    TezinskiGraf G(broj_cvorova+1,true);
    for(int i = 0; i < broj_cvorova; i++){
        G.dodajGranu(broj_cvorova,i,0);
        for(auto el: lista_susjedstva[i])
            G.dodajGranu(i,el.first,el.second);
    }
    pair<bool, vector<double>> BF = G.BelmanFord(broj_cvorova);

    if(!BF.first)
        cout<<"The input graph contains a negative-weight cycle";
    else{
        G.broj_cvorova -=1;
        G.lista_susjedstva.pop_back();
        for(int i = 0; i < G.broj_cvorova; i++)
            h[i] = BF.second[i];
        for(int i = 0; i < G.broj_cvorova; i++){
            for(auto it = G.lista_susjedstva[i].begin(); it!= G.lista_susjedstva[i].end(); it++){
                it->second = it->second + h[i] - h[it->first];
            }
        }
        vector<vector<double>> D(broj_cvorova, vector<double> (broj_cvorova,{INT_MAX}));
        for(int i = 0; i < broj_cvorova; i++){
            vector<double> Dijkstra_udaljenost = G.DijkstraBrzo(i);
            for(int j = 0; j < broj_cvorova; j++){
                D[i][j] = Dijkstra_udaljenost[j]+ h[j]-h[i];
            }
        }
        return D;
    }
}



