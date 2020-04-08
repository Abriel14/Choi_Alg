#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
using namespace std;

int low(vector<int>);

vector<int> fusion(vector<int>,vector<int>);

void reduction_block(vector<vector<int>>);

void reduction_blocks(vector<vector<vector<int>>>);

vector<int> compute_Betti_nbrs(vector<vector<vector<int>>>);

int low(vector<int> v){
    if(v.size()==0) return 0;
    else return v[v.size()-1];
}

vector<int> fusion(vector<int> v1,vector<int> v2){
    // ordered fusion of two ordered lists
    int j1 = 0;
    int j2 = 0;
    int n1 = v1.size();
    int n2 = v2.size();
    vector<int> res;
    while(j1<n1 && j2<n2){
        if (v1[j1] == v2[j2]){
            j1+=1;
            j2+=1;
        }
        else{
            if(v1[j1]<v2[j2]){
                res.push_back(v1[j1]);
                j1+=1;
            }
            else{
                res.push_back(v2[j2]);
                j2+=1;
            }
        }
    }
    if(j1==n1){
        while(j2<n2){
            res.push_back(v2[j2]);
            j2+=1;
        }
    }
    else{
        while(j1<n1){
            res.push_back(v1[j1]);
            j1+=1;
        }
    }
    return res;
}

void reduction_block(vector<vector<int>> block){
    vector<int> list_low_elements;
    for(int j=0;j<block.size();j++)
        list_low_elements.push_back(low(block[j]));
    for(int j=0;j<block.size();j++){
        bool exists = true;
        while(list_low_elements[j]!=0 && exists){
            exists = false;
            int j0 = 0;
            while(j0<j && !exists){
                if(list_low_elements[j0] == list_low_elements[j]){
                    exists = true;
                    block[j] = fusion(block[j],block[j0]);
                    list_low_elements[j] = low(block[j]);
                }
                else j0+=1;
            }
        }
    }
}

void reduction_blocks(vector<vector<vector<int>>>blocks){
    for(int k=0;k<blocks.size();k++){
        reduction_block(blocks[k]);
    }
}

vector<int> compute_Betti_nbrs(vector<vector<vector<int>>> D){
    int dimension = D.size();
    reduction_blocks(D);
    vector<int> kernel_dim;
    vector<int> image_dim;
    for(int d = 0;d<dimension+1;d++){
        if(d==0) kernel_dim.push_back(D[d].size());
        else{
            if(d==dimension) image_dim.push_back(0);
            else{
                kernel_dim.push_back(0);
                image_dim.push_back(0);
                for(int i = 0; i<D[d].size();i++){
                    if(low(D[d][i])==0) kernel_dim[kernel_dim.size()-1] +=1;
                    else image_dim[image_dim.size()-1] +=1;
                    }
                }
            }
        }
    vector<int> list_Betti;
    for(int d = 0;d<kernel_dim.size();d++){
        list_Betti.push_back(kernel_dim[d]-image_dim[d]);
        cout<<list_Betti[d]<<'\n';
    }
    return list_Betti;
}

int main(){
    vector<vector<vector<int>>> K {{{},{},{}},{{0,1},{0,2},{1,2}},{{0,1,2}}};
    vector<int> Betti = compute_Betti_nbrs(K);
}