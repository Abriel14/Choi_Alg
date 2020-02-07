#include <vector>
#include <iostream>
#include "Z2_polynoms.h"
#include "ch_funct.h"
#include <algorithm>
using namespace std;

vector<vector<int>> fusion(vector<vector<int>>,vector<vector<int>>);

vector<vector<int>> fusion(vector<vector<int>> l1,vector<vector<int>> l2){
    int n1 = l1.size();
    int n2 = l2.size();
    vector<vector<int>> result;
    int i1 = 0;
    int i2 = 0;
    while(i1<n1 && i2< n2){
        if(l1[i1]==l2[i2]){
            i1+=1;
            i2+=1;
        }
        if(l1[i1]<l2[i2]){
            result.push_back(l1[i1]);
            i1+=1;
        }
        if(l1[i1]>l2[i2]){
            result.push_back(l2[i2]);
            i2+=1;
        }        
    }
    for(int k1 = i1;k1<n1;k1++)
            result.push_back(l1[k1]);
    for(int k2 = i2;k2<n2;k2++)
        result.push_back(l1[k2]);
    return(result);
}


Z2_polynom::Z2_polynom(int n,vector<vector<int>> list_of_monoms){
    sort(list_of_monoms.begin(),list_of_monoms.end());
    monoms = list_of_monoms;
    N = n;
}

Z2_polynom Z2_polynom::operator+(const Z2_polynom &P){
    this->monoms = fusion(this->monoms,P.monoms);
}

Z2_polynom Z2_polynom::operator+(const Z2_polynom &P){
    
}