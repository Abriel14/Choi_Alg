#ifndef Z2_POLYNOMS_H
#define Z2_POLYNOMS_H

using namespace std;

class Z2_polynom
{
private:
    int N;
    vector<vector<int>> monoms;
public:
    Z2_polynom(int n);
    Z2_polynom(int n,vector<vector<int>> list_of_monoms);
    void display_monoms();
    ~Z2_polynom();
    Z2_polynom operator+(const Z2_polynom & P);
    Z2_polynom operator*(const Z2_polynom & P);
    bool is_null();
};

#endif