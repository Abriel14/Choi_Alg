#ifndef Z2_POLYNOM_H
#define Z2_POLYNOM_H

#include <vector>
#include <iostream>
using namespace std;

class Z2_polynom
{
private:
    int N;
public:
    vector<vector<int>> monoms;
    Z2_polynom(int N);
    Z2_polynom(int N,vector<vector<int>> monoms);
    ~Z2_polynom();
    Z2_polynom operator+(const Z2_polynom & P);
    Z2_polynom operator*(const Z2_polynom & P);
};




#endif