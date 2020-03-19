#ifndef CH_FUNCT_H
#define CH_FUNCT_H

#include <vector>

using namespace std;

int sum(vector<int>);
vector<int> sum_v(vector<int>,vector<int>);
bool is_invertible(vector<vector<int>>);
void print_vect(vector<int>);
void list_non_zero_elements(int, vector<int>);
bool is_in(int, vector<int>);
bool vector_is_in(vector<int>,vector<vector<int>>);

vector<vector<int>> list_3_index(vector<int>, vector<int>, vector<int>);
vector<vector<int>> index_pentagon(vector<int>);
vector<vector<int>> find_max_faces(vector<vector<int>>);
vector<vector<int>> find_min_non_faces(vector<vector<int>>);

vector<vector<vector<int>>> compute_chr_funct(vector<int>);


void remove_all_lin_span(vector<vector<int>>&,vector<vector<int>>,vector<int>);




#endif