#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include "ch_funct.cpp"
#include "Z2_polynoms.cpp"

using namespace std;

int main(){
    vector<int> pentagon1 {2,2,2,2,2};
    vector<vector<int>> pentagon1_indexed = index_pentagon(pentagon1);
    vector<vector<int>> max_faces = find_max_faces(pentagon1_indexed);
    vector<vector<vector<int>>> list_lambdas = compute_chr_funct(pentagon1);
    // for(auto lambda:list_lambdas){
    //   for(auto v:lambda){
    //     print_vect(v);      
    //   }
    //   cout<<"new"<<'\n';
    // }
    cout<<list_lambdas.size()<<'\n';

    vector<vector<int>> monoms1{{2,0,0},{1,1,0},{0,1,3}};
    vector<vector<int>> monoms2{{1,0,0}};
    vector<vector<int>> empty_monoms;
    cout<<1<<'\n';
    Z2_polynom P1(3,monoms1);
    cout<<2<<'\n';
    Z2_polynom P2(3,monoms2);
    cout<<3<<'\n';
    Z2_polynom P3(3,empty_monoms);
    P3 = P1+P2;
    cout<<4<<'\n';
    Z2_polynom P4(3,empty_monoms);
    P4 = P1 * P2;
    cout<<5<<'\n';
    P1.Z2_polynom::display_monoms();
    cout<<6<<'\n';
    P2.Z2_polynom::display_monoms();
    cout<<7<<'\n';
    P3.Z2_polynom::display_monoms();
    cout<<8<<'\n';
    P4.Z2_polynom::display_monoms();
    cout<<9<<'\n';
    return 0;
    }







