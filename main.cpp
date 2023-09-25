#include <iostream>
#include "tezinski_graf.h"
#include "graf.h"


using namespace std;

int main(){

    TezinskiGraf G(5,true);
      G.dodajGranu(0,1,3);
      G.dodajGranu(0,2,8);
      G.dodajGranu(0,4,-4);
      G.dodajGranu(1,4,7);
      G.dodajGranu(1,3,1);
      G.dodajGranu(2,1,4);
      G.dodajGranu(4,3,6);
      G.dodajGranu(3,2,-5);
      G.dodajGranu(3,0,2);
/*
    vector<vector<double>> vec;
    vec = G.slow_all_pairs_shortest_paths();
    for(int i = 0; i< vec.size(); i++){
        for(int j = 0; j< vec[i].size(); j++)
            cout<<vec[i][j]<<" ";
        cout<<endl;
    }
    */

    //cout<<"Zadatak 25.1 - 1:"<<endl<<endl;

    /*
    cout<<"SLOW-ALL-PAIRS-SHORTEST-PATHS koraci:"<<endl<<endl;
    vector<vector<double>> v1;
    v1 = G2.slow_all_pairs_shortest_paths();
    cout<<"FASTER-ALL-PAIRS-SHORTEST-PATHS koraci:"<<endl<<endl;
    vector<vector<double>> v2;
    v2 = G2.faster_all_pairs_shortest_paths();
    cout<<"Zadatak 25.1 - 10:"<<endl<<endl;
    cout<<G2.min_length_negative_weight_cycle();


    vector<vector<double>> v3;
    v3 = G.Floyd_Warshall_predecessor();
    for(int i = 0; i< v3.size(); i++){
        for(int j = 0; j< v3[i].size(); j++)
            cout<<v3[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;

    Graf G3(4,true);
      G3.dodajGranu(1,3);
      G3.dodajGranu(1,2);
      G3.dodajGranu(2,1);
      G3.dodajGranu(3,2);
      G3.dodajGranu(3,0);
    vector<vector<int>> v4;
    v4 = G3.fast_transitive_closure();
    for(int i = 0; i< v4.size(); i++){
        for(int j = 0; j< v4[i].size(); j++)
            cout<<v4[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;
    vector<vector<int>> v5;
    v5 = G3.transitive_closure();
    for(int i = 0; i< v5.size(); i++){
        for(int j = 0; j< v5[i].size(); j++)
            cout<<v4[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;
    vector<vector<double>> v6;
    v6 = G.Johnson();
    for(int i = 0; i< v6.size(); i++){
        for(int j = 0; j< v6[i].size(); j++)
            cout<<v6[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;
*/
    TezinskiGraf G4(3,true);
    G4.dodajGranu(0,1,8);
    G4.dodajGranu(1,0,12);
    G4.dodajGranu(0,2,22);
    G4.dodajGranu(2,0,6);
    G4.dodajGranu(1,2,4);

    TezinskiGraf G5(4,true);
    G5.dodajGranu(0,1,-3);
    G5.dodajGranu(0,3,2);
    G5.dodajGranu(1,0,5);
    G5.dodajGranu(1,2,3);
    G5.dodajGranu(2,0,1);
    G5.dodajGranu(3,2,4);
    G5.dodajGranu(3,0,-1);

    TezinskiGraf G2(6,true);
      G2.dodajGranu(0,4,-1);
      G2.dodajGranu(1,0,1);
      G2.dodajGranu(1,3,2);
      G2.dodajGranu(2,1,2);
      G2.dodajGranu(2,5,-8);
      G2.dodajGranu(3,0,-4);
      G2.dodajGranu(3,4,3);
      G2.dodajGranu(4,1,7);
      G2.dodajGranu(5,1,5);
      G2.dodajGranu(5,2,10);
    cout<<"Johnsonov algoritam:\n\n";
    vector<vector<double>> v7;
    v7 = G.Johnson();
    for(int i = 0; i< v7.size(); i++){
        for(int j = 0; j< v7[i].size(); j++)
            cout<<v7[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;

}

