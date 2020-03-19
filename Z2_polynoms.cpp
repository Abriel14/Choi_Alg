#include <vector>
#include <iostream>
#include "Z2_polynoms.hpp"
#include <algorithm>

using namespace std;

vector<vector<int>> fusion(vector<vector<int>>,vector<vector<int>>);

vector<vector<int>> fusion(vector<vector<int>> l1,vector<vector<int>> l2){
    int n1 = l1.size();
    int n2 = l2.size();
    vector<vector<int>> result;
    int i1 = 0;
    int i2 = 0;
    while(i1<n1 && i2<n2){     
        if(l1[i1]==l2[i2]){
            i1+=1;
            i2+=1;
        }
        else{ if(l1[i1]<l2[i2]){
            result.push_back(l1[i1]);
            i1+=1;
        }
        else{
        if(l2[i2]<l1[i1]){
            result.push_back(l2[i2]);
            i2+=1;
        }
        }
        }
    }
    for(int k1 = i1;k1<n1;k1++)
        result.push_back(l1[k1]);
    for(int k2 = i2;k2<n2;k2++)
        result.push_back(l2[k2]);
    return(result);
}


Z2_polynom::Z2_polynom(int n,vector<vector<int>> list_of_monoms){
    sort(list_of_monoms.begin(),list_of_monoms.end());
    monoms = list_of_monoms;
    N = n;

}
Z2_polynom::Z2_polynom(int n){
    N = n;
    vector<vector<int>> m;
    monoms = m;
}
bool Z2_polynom::is_null(){
    return (this->monoms.size()==0);
}

Z2_polynom Z2_polynom::operator+(const Z2_polynom &P){
    vector<vector<int>> add_result;
    add_result = fusion(this->monoms,P.monoms);
    Z2_polynom result(this->N,add_result);
    return result;
}


Z2_polynom Z2_polynom::operator*(const Z2_polynom &P){
    vector<vector<int>> mult_result;
    int n = this->N;
    Z2_polynom result(n,mult_result);
    for(vector<int> monom: this->monoms){
        vector<vector<int>> list_multiplied_monoms;
        for(vector<int> monom_to_multiply:P.monoms){
            vector<int> multiplied_monom;
            for(int k=0;k<n;k++){
                multiplied_monom.push_back(monom[k]+monom_to_multiply[k]);
            }
            list_multiplied_monoms.push_back(multiplied_monom);
        }
        Z2_polynom multiplied_polynom(n,list_multiplied_monoms);
        result = result + multiplied_polynom;
    }
    return result;
}
Z2_polynom::~Z2_polynom(){
}



void Z2_polynom::display_monoms(){
    for(vector<int> monom: this->monoms){
        cout<<'{';
        for(int k:monom){
            cout<<k<<',';
        }
        cout<<'}'<<'\n';
    }

}