#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include "ch_funct.cpp"
#include "Z2_polynoms.cpp"



using namespace std;

vector<Z2_polynom> find_polynoms(vector<vector<int>>,vector<vector<int>>,vector<vector<int>>,vector<vector<int>>);

vector<Z2_polynom> find_polynoms(vector<vector<int>> lambda_funct,vector<vector<int>> list_max_faces,vector<vector<int>> list_min_non_faces,vector<vector<int>> indexed_pentagon){
    for(auto v:lambda_funct){
        print_vect(v);
    }
    
    int n = lambda_funct[0].size();
    int m = lambda_funct.size();
    vector<int> ref_max_face(list_max_faces[0]);
    vector<int> compl_ref_max_face {indexed_pentagon[0][0], indexed_pentagon[1][0],indexed_pentagon[3][0]};
    vector<vector<int>> monom_X {{1,0,0}};
    vector<vector<int>> monom_Y {{0,1,0}};
    vector<vector<int>> monom_Z {{0,0,1}};
    Z2_polynom X(3,monom_X);
    Z2_polynom Y(3,monom_Y);
    Z2_polynom Z(3,monom_Z);

    vector<Z2_polynom> reference_variables;
    
    for(int k=0;k<m;k++){
        reference_variables.push_back(X);
    }
    reference_variables[compl_ref_max_face[0]] = X;
    reference_variables[compl_ref_max_face[1]] = Y;
    reference_variables[compl_ref_max_face[2]] = Z;

    for(int k=0;k<n;k++){
        Z2_polynom P_k(3);
        if(lambda_funct[compl_ref_max_face[0]][k]==1){
            P_k = P_k + X;
        }
        if(lambda_funct[compl_ref_max_face[1]][k]==1){
            P_k = P_k + Y;
        }
        if(lambda_funct[compl_ref_max_face[2]][k]==1){
            P_k = P_k + Z;
        }
        reference_variables[ref_max_face[k]] = P_k;
    }

    vector<Z2_polynom> I;

    vector<vector<int>> const_monom {{0,0,0}};

    for (auto min_non_face: list_min_non_faces){
        Z2_polynom P(3,const_monom);
        for(auto k:min_non_face){
            P = P * reference_variables[k]; 
        }
        I.push_back(P);
    }
    return(I);
}




int main(){
    vector<int> pentagon1 {1,1,1,1,1};
    vector<vector<int>> pentagon1_indexed = index_pentagon(pentagon1);
    vector<vector<int>> max_faces = find_max_faces(pentagon1_indexed);
    vector<vector<int>> min_non_faces = find_min_non_faces(pentagon1_indexed);
    vector<vector<vector<int>>> list_lambdas = compute_chr_funct(pentagon1);
    vector<Z2_polynom> I = find_polynoms(list_lambdas[0],max_faces,min_non_faces,pentagon1_indexed);
    cout<<I.size()<<'\n';
    for(auto P:I){
        cout<<"new"<<'\n';
        P.display_monoms();
    }
    }







