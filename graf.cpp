#include "graf.h"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

//Osnove

void Graf::dodajGranu(int i, int j){
    lista_susjedstva[i].push_back(j);
    if(!usmjeren)
        lista_susjedstva[j].push_back(i);

}

void Graf::ispisi(){
    for(int i = 0; i < broj_cvorova; i++){
        cout << i << ": ";
        for(auto el:lista_susjedstva[i])
            cout << el << " ";
        cout << endl;
    }
}

void Graf::BFS(int pocetni) {
    vector<bool> posjecen(broj_cvorova, false);
    posjecen[pocetni] = true;
    queue<int> red;
    red.push(pocetni);
    while(!red.empty()) {
        int trenutni = red.front();
        cout<<"Posjecujem "<<trenutni<<endl;
        red.pop();
        for(auto el:lista_susjedstva[trenutni])
            if(!posjecen[el]) {
                posjecen[el] = true;
                red.push(el);
            }
    }
    /*for(int i = 0; i < broj_cvorova; i++) {
    cout<<i<<" "<<posjecen[i]<<endl;
    }*/
}

void Graf::DFS(int pocetni) {
    vector<pair<int,int>> vremena(broj_cvorova);
    vector<bool> posjecen(broj_cvorova,false);
    int time = 0;
    DFSRek(pocetni,posjecen, vremena, time);
    for(int i = 0; i < broj_cvorova; i++)
        cout<<i<<": "<<vremena[i].first<<" "<<vremena[i].second<<endl;
}

void Graf::DFSRek(int pocetni, vector<bool> &posjecen, vector<pair<int,int>> &vremena, int &time) {
    posjecen[pocetni] = true;
    vremena[pocetni].first = time++;
    cout<<pocetni<<endl;
    for(auto el: lista_susjedstva[pocetni])
        if(!posjecen[el])
            DFSRek(el,posjecen,vremena,time);

    vremena[pocetni].second = time++;
}


//Udaljenosti

void Graf::Udaljenosti(int pocetni) {
    vector<int> udaljenosti(broj_cvorova, -1);
    udaljenosti[pocetni] = 0;
    queue<int> red;
    red.push(pocetni);
    while(!red.empty()) {
        int trenutni = red.front();
        red.pop();
        for(auto el:lista_susjedstva[trenutni])
            if(udaljenosti[el] == -1) {
                udaljenosti[el] = udaljenosti[trenutni] + 1;
                red.push(el);
            }
    }
    for(int i = 0; i < broj_cvorova; i++)
        cout<<i<<": "<<udaljenosti[i]<<endl;
}


//Put

vector<int> Graf::put(int pocetni, int krajnji) {
    vector<pair<int,int>> udaljenosti(broj_cvorova, {-1,-1});
    udaljenosti[pocetni].first = 0;
    udaljenosti[pocetni].second = -2;
    queue<int> red;
    red.push(pocetni);
    while(!red.empty()) {
        int trenutni = red.front();
        red.pop();
        for(auto el:lista_susjedstva[trenutni])
            if(udaljenosti[el].first == -1) {
                udaljenosti[el].first = udaljenosti[trenutni].first + 1;
                red.push(el);
                udaljenosti[el].second = trenutni;
            if(el == krajnji)
                break;
            }

    }
    vector<int> put;
    put.push_back(krajnji);
    int trenutni = krajnji;
    do {
        trenutni = udaljenosti[trenutni].second;
        put.push_back(trenutni);
    } while(trenutni != pocetni);

    reverse(put.begin(),put.end());
    return put;
}


//Topoloski Sort

list<int> Graf :: Topoloski_sort(){
   list<int> rezultat;
   vector<bool> posjecen(broj_cvorova,false) ;
   for(int i=0; i<broj_cvorova;i++)
     if(!posjecen[i])
       TopoloskiRek(i,posjecen,rezultat);
  return rezultat;
 }

void Graf :: TopoloskiRek(int cvor,vector<bool>&posjecen,list<int>&rezultat){
  posjecen[cvor]=true;
  for(auto el : lista_susjedstva[cvor])
      if(!posjecen[el])
        TopoloskiRek(el,posjecen,rezultat);
  rezultat.push_front(cvor);
}


//Komponente Povezanosti

void Graf::DFS2Rek(int cvor, vector<bool> &posjecen, stack<int> &redoslijedZavrsavanja) {
    posjecen[cvor] = true;
    for(auto el: lista_susjedstva[cvor])
        if(!posjecen[el])
            DFS2Rek(el,posjecen,redoslijedZavrsavanja);

    redoslijedZavrsavanja.push(cvor);
}

void Graf::DFS3Rek(int cvor, vector<bool> &posjecen, list<int> &komponenta) {
  posjecen[cvor] = true;
  komponenta.push_back(cvor);
  for(auto el: lista_susjedstva[cvor]) {
        if(!posjecen[el])
            DFS3Rek(el,posjecen,komponenta);
  }
}

list<list<int>> Graf::komponenteJakePovezanosti() {
    stack<int> redoslijedZavrsavanja;
    vector<bool> posjecen(broj_cvorova,false);
    for(int i = 0; i < broj_cvorova; i++)
        if(!posjecen[i])
            DFS2Rek(i,posjecen, redoslijedZavrsavanja);

    Graf GT(broj_cvorova, true);
    for(int i = 0; i < broj_cvorova; i++)
        for(auto el: lista_susjedstva[i])
            GT.dodajGranu(el,i);

    list<list<int>> komponente;
    posjecen = vector<bool> (broj_cvorova, false);
    while(!redoslijedZavrsavanja.empty()) {
        int trenutni = redoslijedZavrsavanja.top();
        redoslijedZavrsavanja.pop();
        if(!posjecen[trenutni]) {
            list<int> komponenta;
            GT.DFS3Rek(trenutni,posjecen,komponenta);
            komponente.push_back(komponenta);
        }
    }
    return komponente;
}

vector<vector<int>> Graf::transitive_closure(){
    vector<vector<int>> T(broj_cvorova, vector<int> (broj_cvorova,{0}));
    for(int i = 0; i < broj_cvorova; i++){
        for(int j = 0; j < broj_cvorova; j++){
            if(i == j){
                T[i][j] = 1;
                continue;
            }
            for(auto el: lista_susjedstva[i]) {
                if(el == j)
                    T[i][j] = 1;
            }
        }
    }
    for(int k = 0; k < broj_cvorova; k++){
        for(int i = 0; i < broj_cvorova; i++){
            for(int j = 0; j < broj_cvorova; j++)
                T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
        }
    }
    return T;
}

vector<vector<int>> Graf::fast_transitive_closure(){
    vector<vector<int>> T(broj_cvorova, vector<int> (broj_cvorova,{0}));
    for(int i = 0; i < broj_cvorova; i++){
        T[i][i] = 1;
        for(auto el:lista_susjedstva[i]){
            if(T[i][el] == 0)
                    T[i][el] = 1;

        }
    }
    return T;
}








