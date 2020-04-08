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
vector<vector<vector<int>>> enumerate_GL3();
bool compare_to_GB(vector<Z2_polynom>,vector<Z2_polynom>);

vector<Z2_polynom> find_polynoms(vector<vector<int>> lambda_funct,vector<vector<int>> list_max_faces,vector<vector<int>> list_min_non_faces,vector<vector<int>> indexed_pentagon){

    int n = lambda_funct[0].size();
    int m = lambda_funct.size();
    vector<int> ref_max_face(list_max_faces[0]);
    vector<int> compl_ref_max_face {indexed_pentagon[0][0], indexed_pentagon[1][0],indexed_pentagon[3][0]};
    Z2_polynom X(3,{{1,0,0}});
    Z2_polynom Y(3,{{0,1,0}});
    Z2_polynom Z(3,{{0,0,1}});

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

vector<vector<vector<int>>> enumerate_GL3(){
    vector<vector<int>> E {{0,0,1},{0,1,0},{1,0,0},{0,1,1},{1,0,1},{1,1,0},{1,1,1}};
    vector<vector<vector<int>>> GL3;
    for(int i= 0;i<7;i++){
        for(int j = 0;j<7;j++){
            if (i!=j){
                vector<int> sum;
                for(int r=0;r<3;r++) sum.push_back((E[i][r]+E[j][r])%2);
                for(int k=0;k<7;k++){
                    if (k != i && k!=j){
                        if(E[k]!=sum) GL3.push_back(vector<vector<int>> {E[i],E[j],E[k]});
                    }
                }
            }
        }
    }
    return GL3;
}

vector<vector<vector<int>>> GL3 = enumerate_GL3();



bool compare_to_GB(vector<Z2_polynom> I, vector<Z2_polynom> red_GB){
    // compares an ideal with a reduce groebner basis
    for(auto A:GL3){
        vector<Z2_polynom> modified_I;
        for(auto f:I){
            modified_I.push_back(f.apply_permutation(A));
        }
        vector<Z2_polynom> GB_I = Buchberger(modified_I);
        vector<Z2_polynom> red_Gb_I = reduce_GB(GB_I);
        int n1 = red_GB.size();
        int n2 = red_Gb_I.size();
        if(n1==n2){
            bool are_equal = true;
            for(int k = 0;k<n1;k++){
                if(! (red_Gb_I[k]==red_GB[k])){
                    are_equal = false;
                    break;
                }
            }
            if(are_equal) return true;
        }

    }
    return false;
}

vector<vector<int>> list_pentagon {{2,2,2,2,2}};


int main(){
    // vector<vector<int>> indexed_pentagon = index_pentagon({3,1,1,1,1});
    // vector<vector<int>> max_faces = find_max_faces(indexed_pentagon);
    // vector<vector<int>> min_non_faces = find_min_non_faces(indexed_pentagon);
    // vector<vector<vector<int>>> list_lambdas = compute_chr_funct({3,1,1,1,1});
    // vector<Z2_polynom> I = find_polynoms(list_lambdas[0],max_faces,min_non_faces,indexed_pentagon);
    // vector<Z2_polynom> GB = Buchberger(I);

    // vector<Z2_polynom> GB_red = reduce_GB(GB);
    // for(auto f:GB_red){
    //     cout<<"new"<<'\n';
    //     f.display_monoms();
    // }


    for(auto pentagon: list_pentagon){
        vector<vector<int>> indexed_pentagon = index_pentagon(pentagon);
        vector<vector<int>> max_faces = find_max_faces(indexed_pentagon);
        vector<vector<int>> min_non_faces = find_min_non_faces(indexed_pentagon);
        vector<vector<vector<int>>> list_lambdas = compute_chr_funct(pentagon);
        vector<vector<int>> cohomology_classes {{0}};
        vector<vector<vector<Z2_polynom>>> cohomology_classes_GB;
        cohomology_classes_GB.push_back({});
        vector<Z2_polynom> I = find_polynoms(list_lambdas[0],max_faces,min_non_faces,indexed_pentagon);
        for(auto A:GL3){
            vector<Z2_polynom> modified_I;
            for(auto f:I){
                modified_I.push_back(f.apply_permutation(A));
            }
            vector<Z2_polynom> GB_I = Buchberger(modified_I);
            vector<Z2_polynom> red_Gb_I = reduce_GB(GB_I);
            cohomology_classes_GB[0].push_back(red_Gb_I);
        }
        for(int k = 1;k<list_lambdas.size();k++){
            cout<<k<<'\n';
            vector<Z2_polynom> I = find_polynoms(list_lambdas[k],max_faces,min_non_faces,indexed_pentagon);
            vector<Z2_polynom> GB_I = Buchberger(I);
            vector<Z2_polynom> red_GB_I = reduce_GB(GB_I);
            int n1 = red_GB_I.size();
            bool is_cohomolog = false;
            for(int l=0;l<cohomology_classes_GB.size();l++){
                for(int m=0;m<cohomology_classes_GB[l].size();m++){
                    vector<Z2_polynom> red_GB_comp = cohomology_classes_GB[l][m];
                    int n2 = red_GB_comp.size();
                    if(n1==n2){
                        bool GB_are_equal = true;
                        for(int r=0;r<n1;r++){
                            if(!(red_GB_I[r] == red_GB_comp[r])){
                                GB_are_equal = false;
                                break;
                            }
                        }
                        if(GB_are_equal){
                            cohomology_classes[l].push_back(k);
                            is_cohomolog = true;
                            break;
                        }
                    }
                }
                if(is_cohomolog) break;
            }
            if(! is_cohomolog){
                cohomology_classes.push_back(vector<int> {k});
                cohomology_classes_GB.push_back({});
                for(auto A:GL3){
                    vector<Z2_polynom> modified_I;
                    for(auto f:I){
                        modified_I.push_back(f.apply_permutation(A));
                    }
                    vector<Z2_polynom> GB_I = Buchberger(modified_I);
                    vector<Z2_polynom> red_Gb_I = reduce_GB(GB_I);
                    cohomology_classes_GB[cohomology_classes_GB.size()-1].push_back(red_Gb_I);
                }
            }
        }
        for(auto cohomology_class:cohomology_classes){
            cout<<"new"<<'\n';
            print_vect(cohomology_class);
        }
    }
}







