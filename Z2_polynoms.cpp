#include <vector>
#include <iostream>
#include "Z2_polynoms.hpp"
#include <algorithm>

using namespace std;




vector<vector<int>> fusion(vector<vector<int>>,vector<vector<int>>);

bool mon_order(vector<int>,vector<int>);

bool mon_order(vector<int> mon1,vector<int> mon2){
    int a,b;
    for(int k:mon1){
        a+=k;
    }
    for(int k:mon2){
        b+=k;
    }
    if(a>b){
        return true;
    }
    else{
        int k=mon1.size()-1;
        while( k>=0 && (mon1[k] - mon2[k]==0)){
            k+=1;
        }
        return (mon1[k] - mon2[k] < 0);
        }
    }


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
        else{if(mon_order(l1[i1],l2[i2])){
            result.push_back(l1[i1]);
            i1+=1;
        }
        else{if(mon_order(l2[i2],l1[i1])){
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
    sort(list_of_monoms.begin(),list_of_monoms.end(),mon_order);
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

void Z2_polynom::operator=(const Z2_polynom & P){
    this->monoms = P.monoms;
}

bool Z2_polynom::operator>=(const Z2_polynom & P){
    int n1 = this->monoms.size();
    int n2 = P.monoms.size();
    for(int k=0;k<min(n1,n2);k++){
        if(mon_order(this->monoms[k],P.monoms[k]))
            return true;
        if(mon_order(P.monoms[k],this->monoms[k]))
            return false;
    }
    return n1>=n2;
}

bool Z2_polynom::operator<(const Z2_polynom & P){
    return !(*this >= P);
}

bool Z2_polynom::operator==(const Z2_polynom & P){
    return this->N == P.N && this->monoms == P.monoms; 
}


Z2_polynom::~Z2_polynom(){
}

void Z2_polynom::add_monom(vector<int> monom){
    this->monoms.push_back(monom);
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

vector<int> Z2_polynom::LT(){
    return this->monoms[0];
}

Z2_polynom Z2_polynom::reduce(vector<Z2_polynom> F){
    N = this->N;
    Z2_polynom p(N);
    p = *this;
    Z2_polynom r(N);

    Z2_polynom q(3);
    Z2_polynom f0(3);

    while(! p.is_null()){
        bool div = false;
        for(auto f:F){
            vector<int> LT_p = p.LT();
            vector<int> LT_f = f.LT();
            vector<int> monom_q;
            bool test = true;
            // we test if LT(p) is dividible by LT(f)
            for(int k=0;k<N;k++){
                if(LT_p[k]<LT_f[k]){
                    test = false;
                }
                monom_q.push_back(LT_p[k]-LT_f[k]);
            }
            if(test){
                q.add_monom(monom_q);
                f0 = f;
                div = true;
                break;
            }
        }
        if(div){
            p = p + q*f0;
        }
        else{
            Z2_polynom pol_LT_p(3);
            pol_LT_p.add_monom(p.LT());
            p = p + pol_LT_p;
            r = r + pol_LT_p;
        }
    }
    return r;

}

Z2_polynom S_pol(Z2_polynom P1, Z2_polynom P2){
    const int N = P1.N;
    vector<int> LT1 = P1.LT();
    vector<int> LT2 = P2.LT();
    vector<int> PPCM;
    vector<int> monom_Q1;
    vector<int> monom_Q2;
    // We create the two polynoms we will multiply P1 and P2 with
    for(int k = 0;k<N;k++){
        PPCM.push_back(max(LT1[k],LT2[k]));
        monom_Q1.push_back(PPCM[k] - LT1[k]);
        monom_Q2.push_back(PPCM[k] - LT2[k]);
    }
    Z2_polynom Q1(N);
    Z2_polynom Q2(N);
    Q1.add_monom(monom_Q1);
    Q2.add_monom(monom_Q2);
    Z2_polynom S(N);
    S = Q1*P1 + Q2*P2;
    return S;    
}

vector<Z2_polynom> Buchberger(vector<Z2_polynom> I){
    vector<Z2_polynom> E_0 = I;
    vector<Z2_polynom> E_1;
    bool is_grob_basis=false;
    while(!is_grob_basis){
        vector<Z2_polynom> E_1;
        int n = E_0.size();
        is_grob_basis = true;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                Z2_polynom S = S_pol(E_0[i],E_0[j]);
                Z2_polynom S_red = S.reduce(E_0);
                if(! S_red.is_null()){
                    is_grob_basis = false;
                    bool is_in = false;
                    for (auto g:E_1)
                        if(g==S_red) is_in == true;                    
                    if(! is_in) E_1.push_back(S_red);
                }
            }
        }
        if(! is_grob_basis){
            for(auto f:E_1)
                E_0.push_back(f);            
        }
    }
    return E_0;
}

vector<Z2_polynom> reduce_GB(vector<Z2_polynom> I){
    return(I);
}
