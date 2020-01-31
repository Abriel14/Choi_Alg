#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int sum(vector<int>);
void print_vect(vector<int>);


vector<vector<int>> list_3_index(vector<int>, vector<int>, vector<int>);
vector<vector<int>> index_pentagon(vector<int>);
vector<vector<int>> find_max_faces(vector<vector<int>>);
vector<vector<int>> find_min_non_faces(vector<vector<int>>);

vector<int> sum_v(vector<int>,vector<int>);
bool is_invertible(vector<vector<int>>);

vector<vector<vector<int>>> compute_chr_funct(vector<int>);
void list_non_zero_elements(int, vector<int>);
vector<vector<int>> S;

bool is_invertible(vector<vector<int>> A){
  vector<vector<int>> B(A);
  int m = B.size();
  cout<<m<<'\n';
  for(int k=0;k<m;k++){
    int i0=0;
    bool singular_mat = true;
    for(int i=k;i<m;i++){
      if(B[i][k]!=0){
        singular_mat = false;
        i0=i;
      }
    }
    if(singular_mat)
      return false;
    vector<int> v_temp(B[k]);
    B[k] = B[i0];
    B[i0] = v_temp;
    for(int i = k+1;k<m;k++){
      if(B[i][k]==1){
        for(int j = k+1;j<m;j++){
          B[i][j] = (B[i][j] + B[k][j])%2;
        }
      }
      B[i][k]=0;
    }
  }
  for(auto v: B){
    print_vect(v);
  }
  int diag_sum = 0;
  for(int k=0;k<m;k++)
    diag_sum+=B[k][k];
  return (diag_sum == B.size());
}

bool is_in(int, vector<int>);


void print_vect(vector<int> v){
  for(int x:v){
    cout<<x<<',';
    }
  cout<<'\n';
}


void list_non_zero_elements(int i, vector<int> element){
  if(i==element.size()){
    if(sum(element)!=0){
      S.push_back(element);
    }
  }
  else{
    vector<int> element1(element), element2(element);
    element1[i] +=1;
    list_non_zero_elements(i+1, element1);
    list_non_zero_elements(i+1, element2);
  }
}

int sum(vector<int> v){
  int summand = 0;
  for(int k : v)
    summand += k;
  return summand;
}

vector<int> sum_v(vector<int> v1,vector<int> v2){
  vector<int> sum_vector;
  for(int k=0; k<v1.size();k++)
    sum_vector.push_back((v1[k] + v2[k])%2);
  return sum_vector;
}

bool is_in(int x, vector<int> v){
  for(int k:v){
    if(k=x)
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


vector<vector<vector<int>>> compute_chr_funct(vector<int> pentagon){
  vector<vector<int>> indexed_pentagon = index_pentagon(pentagon);
  vector<vector<int>> min_non_faces = find_min_non_faces(indexed_pentagon);
  vector<vector<int>> max_faces = find_max_faces(indexed_pentagon);
  vector<vector<vector<int>>> list_lambdas;
  int m=indexed_pentagon[4].back()+1;
  int n = m-3;
  vector<int> null_v;
  null_v.assign(n,0);
  list_non_zero_elements(0,null_v);
  vector<int> ref_max_face = max_faces[0];
  vector<int> compl_ref_max_face {indexed_pentagon[0][0], indexed_pentagon[1][0],indexed_pentagon[3][0]};
  vector<vector<int>> lambda_template;
  lambda_template.assign(m,null_v);
  for(int k=0; k<n;k++){
    lambda_template[ref_max_face[k]][k] = 1;
    }
  int i = 0;
  list_non_zero_elements(0, null_v);
  vector<vector<int>> lambda(lambda_template);
  /* For every vectors in Z2, we test if the lambda function lambda_test verifies the condition*/
  for(auto v1:S){
    for(auto v2:S){
      for(auto v3:S){
        //initialize the lambda_test
        vector<vector<int>> lambda_test(lambda_template);
        lambda_test[ref_max_face[0]] = v1;
        lambda_test[ref_max_face[1]] = v2;
        lambda_test[ref_max_face[2]] = v3;
        /*We test here all maximal faces and see if the restricted rows are linearly independant*/
        bool respects_def = true;
        for(auto max_face:max_faces){
          vector<vector<int>> M_test;
          for(int index: max_face){
            M_test.push_back(lambda_test[index]);
          }
          if(!is_invertible(M_test)){
            respects_def = false;
            break;
          }
          else
          {
            list_lambdas.push_back(lambda_test);
          }
        }
      }
    }
  }
  return list_lambdas;
  // while(i!=-1){
  //   vector<vector<int>> S_i(S);
  //   for(vector<int> max_face : max_faces){
  //     if(is_in(compl_ref_max_face[i], max_face)){
  //       bool others_are_not = true;
  //       for (int j = i+1;j<3;j++){
  //         if(! is_in(compl_ref_max_face[j], max_face))
  //           others_are_not = false;
  //         }
  //       if(others_are_not){
  //         vector<int> sum_vector(null_v);
  //         for(int l=0;l<max_face.size();l++){
  //           sum_vector = sum_v(sum_vector,lambda[max_face[l]]);
  //         }
  //         for(int S_index=0;S_index<S_i.size()/(S_i[0].size());S_index++){
  //           cout<<S_index<<'\n';
  //           if(S_i[S_index]==sum_vector){              
  //             S_i.erase(S_i.begin()+S_index);
  //             }
  //           }
  //         }
  //       }
  //     }
  //   while(S_i.size()!=0){
  //     lambda[compl_ref_max_face[i]] = S_i.back();
  //     S_i.pop_back();
  //     if(i==2){
  //       vector<vector<int>> lambda_ins(lambda);
  //       bool is_already_here = false;
  //       for(auto lambda_test:list_lambdas){
  //         if(lambda_test==lambda_ins)
  //           is_already_here = true;
  //       }
  //       if(! is_already_here)
  //         list_lambdas.push_back(lambda_ins);
  //       }
  //     else{
  //       i=i+1;
  //       break;
  //       }
  //     }
  //   if(S_i.size()==0)
  //     i=i-1;
  //   }
  }


int main(){
  vector<int> v1 {1,0,0};
  vector<int> v2 {0,1,0};
  vector<int> v3 {0,0,1};
  vector<vector<int>> M;
  M.push_back(v1);
  M.push_back(v2);
  M.push_back(v3);
  if(is_invertible(M))
    cout<<"coucou"<<'\n';
  // vector<int> pentagon1 {1,1,1,1,1};
  // vector<vector<int>> pentagon1_indexed = index_pentagon(pentagon1);
  // vector<vector<int>> max_faces = find_max_faces(pentagon1_indexed);

  // vector<vector<vector<int>>> list_lambdas = compute_chr_funct(pentagon1);
  // cout<<list_lambdas.size()<<'\n';
}
