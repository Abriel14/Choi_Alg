#ifndef Z2_POLYNOMS_H
#define Z2_POLYNOMS_H

using namespace std;

class Z2_polynom
{
private:
    vector<vector<int>> monoms;
public:
    int N;
    Z2_polynom(int n);
    Z2_polynom(int n,vector<vector<int>> list_of_monoms);
    void add_monom(vector<int> monom);
    void display_monoms();
    ~Z2_polynom();
    Z2_polynom operator+(const Z2_polynom & P);
    Z2_polynom operator*(const Z2_polynom & P);
    Z2_polynom operator^(const int n);
    void operator=(const Z2_polynom & P);
    bool operator>=(const Z2_polynom & P);
    bool operator<(const Z2_polynom & P);
    bool operator==(const Z2_polynom & P);
    bool is_null();
    vector<int> LT();
    Z2_polynom apply_permutation(vector<vector<int>> P);
    Z2_polynom reduce(vector<Z2_polynom> F);
    Z2_polynom S_pol(Z2_polynom P1, Z2_polynom P2);
    vector<Z2_polynom> Buchberger(vector<Z2_polynom> I);
    vector<Z2_polynom> reduce_GB(vector<Z2_polynom> I);
    
};

#endif