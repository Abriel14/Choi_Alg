#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include "ch_funct.hpp"

using namespace std;

int thread_nbr = 8;
vector<vector<bool>> S;


void print_vect(vector<int> v){
  for(int x:v){
    cout<<x<<',';
    }
  cout<<'\n';
}

void list_non_zero_elements(int i, vector<bool> element){
  if(i==element.size()){
    if(sum(element)){
      S.push_back(element);
    }
  }
  else{
    vector<bool> element1(element), element2(element);
    element1[i] = true;
    list_non_zero_elements(i+1, element1);
    list_non_zero_elements(i+1, element2);
  }
}

int sum(vector<bool> v){
  bool summand = false;
  for(int k : v)
    summand = summand || k;
  return summand;
}

vector<bool> sum_v(vector<bool> v1,vector<bool> v2){
  vector<bool> sum_vector;
  for(int k=0; k<v1.size();k++)
    sum_vector.push_back(v1[k] ^ v2[k]);
  return sum_vector;
}

bool is_in(int x, vector<int> v){
  for(auto k:v){
    if(k==x)
      return true;
    }
  return false;
}

vector<vector<int>> list_3_index(vector<int> a,vector<int> b, vector<int> c){
  vector<vector<int>> list_index;
  for(int i:a)
    for(int j:b)
      for(int k:c)
        list_index.push_back(vector<int> {i,j,k});
  return list_index;
}
vector<vector<int>> index_pentagon(vector<int> pentagon){
  vector<vector<int>> indexed_pentagon;
  int index = 0;
  for(int k: pentagon){
    vector<int> vertice_range;
    for(int l = index; l<index+k;l++){
      vertice_range.push_back(l);
    }
    indexed_pentagon.push_back(vertice_range);
    index = index + k;
  }
  return indexed_pentagon;
}
vector<vector<int>> find_max_faces(vector<vector<int>> indexed_pentagon){
  int m=indexed_pentagon[4].back()+1;
  vector<vector<int>> max_faces;
  for(int k = 0; k<5; k++){
    vector<vector<int>> list_indexes = list_3_index(indexed_pentagon[k], indexed_pentagon[(k+1)%5], indexed_pentagon[(k+3)%5]);
    for(vector<int> indexes : list_indexes){
      vector<int> current_max_face;
      for(int i=0;i<m;i++){
        if(i!=indexes[0] && i!=indexes[1] && i!=indexes[2])
          current_max_face.push_back(i);
        }
      max_faces.push_back(current_max_face);
    }
  }
  return max_faces;
}

vector<vector<int>> find_min_non_faces(vector<vector<int>> indexed_pentagon){
  vector<vector<int>> min_non_faces;
  for(int k=0;k<4;k++){
    vector<int> current_min_non_face(indexed_pentagon[k]);
    current_min_non_face.insert(current_min_non_face.end(),indexed_pentagon[(k + 1) % 5].begin(), indexed_pentagon[(k + 1) % 5].end());
    min_non_faces.push_back(current_min_non_face);
  }
  vector<int> current_min_non_face(indexed_pentagon[0]);
  current_min_non_face.insert(current_min_non_face.end(),indexed_pentagon[4].begin(), indexed_pentagon[4].end());
  min_non_faces.push_back(current_min_non_face);
  return min_non_faces;
}

void remove_all_lin_span(vector<vector<bool>>& T,vector<vector<bool>> list_vectors, vector<bool> lin_span){
  //Given a list of vectors, this function erases from this list every Z2 linear spans of it.
  if(list_vectors.size()==0){
    int n = (T).size();
    for(int k = 0;k<n;k++){
      if((T)[k]==lin_span){
        (T).erase((T).begin()+k);
        break;
      }
    }
  }
  else
  {
    vector<bool> v(list_vectors.back());
    list_vectors.pop_back();
    remove_all_lin_span(T,list_vectors,lin_span);
    remove_all_lin_span(T,list_vectors,sum_v(v,lin_span));
  }
}

vector<vector<vector<bool>>> compute_chr_funct(vector<int> pentagon){

  vector<vector<int>> indexed_pentagon = index_pentagon(pentagon);
  vector<vector<int>> min_non_faces = find_min_non_faces(indexed_pentagon);
  vector<vector<int>> max_faces = find_max_faces(indexed_pentagon);

  vector<vector<vector<bool>>> list_lambdas;

  int m=indexed_pentagon[4].back()+1;//the number of vertices
  int n = m-3;//dimension of the polytope

  //creation of the null vector
  vector<bool> null_v;
  null_v.assign(n,false);
  list_non_zero_elements(0,null_v);

  //the reference maximal face (we put the canonical basis in the rows of the characterisic function)
  vector<int> ref_max_face = max_faces[0];
  vector<int> compl_ref_max_face {indexed_pentagon[0][0], indexed_pentagon[1][0],indexed_pentagon[3][0]};

  //We create the template for the characteristic function
  vector<vector<bool>> lambda_template;
  lambda_template.assign(m,null_v);
  for(int k=0; k<n;k++){
    lambda_template[ref_max_face[k]][k] = 1;
    }
  
  vector<vector<bool>> lambda(lambda_template);
  vector<vector<vector<bool>>> list_S;//list of all the possibilities for the three vectors
  for(auto k:compl_ref_max_face){
    vector<vector<bool>> S_cp(S);
    list_S.push_back(S_cp);
  }
  int i = 0;

  while(i!=-1){
    for(vector<int> max_face : max_faces){
      //if the treatin index is in the max face
      if(is_in(compl_ref_max_face[i], max_face)){
        bool others_are_not = true;
        //we test if the afterward other indexes are not there
        for (int j = i+1;j<3;j++){
          if(is_in(compl_ref_max_face[j], max_face)){
            others_are_not = false;
            }
          }
        //if they are not in the max face then the conditions are satisfied
        if(others_are_not){
          //we create the list of the vectors we will remove the span in the list list_S[i]
          vector<vector<bool>> list_vectors;
          for(int k:max_face){
            //if the index is not the one of the treating vector (it must be linearly independant from the ones in the max face which contains it),
            if(k!=compl_ref_max_face[i]){
              vector<bool> vect_to_add(lambda[k]);
              list_vectors.push_back(vect_to_add);
              }
            }
          //We remove from the list list_S[i] all the span of the list_vectors
          remove_all_lin_span(list_S[i],list_vectors,null_v);
          }
        }
      }
    while(list_S[i].size()!=0){
      //We put the last vector of the list in the current lambda function at the index i
      lambda[compl_ref_max_face[i]] = list_S[i].back();
      list_S[i].pop_back();
      //if it is the last possible vector to add, it means we just should fill lambda with the working vectors
      if(i==2){
        vector<vector<bool>> lambda_ins(lambda);
        list_lambdas.push_back(lambda_ins);
        cout<<list_lambdas.size()<<'\n';
        }
      //otherwise, we must analyze the next vector possible according to the one we put just before
      else{
        i=i+1;
        break;
        }
      }
    //if we emptied the list of vectors, it means we should replace it with a new one and come back to the last vector treated  
    if(list_S[i].size()==0){
      list_S[i] = S;
      i=i-1;
      
      }
    }
  return list_lambdas;
  }
  


