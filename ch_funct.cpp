#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int sum(vector<int>);


vector<vector<int>> list_3_index(vector<int>, vector<int>, vector<int>);
vector<vector<int>> index_pentagon(vector<int>);
vector<vector<int>> find_max_faces(vector<vector<int>>);
vector<vector<int>> find_min_non_faces(vector<vector<int>>);

vector<int> sum_v(vector<int>,vector<int>);

vector<vector<vector<int>>> compute_chr_funct(vector<int>);
void list_non_zero_elements(int, vector<int>);
vector<vector<int>> S;

bool is_in(int, vector<int>);



void list_non_zero_elements(int i, vector<int> element){
  if(i==element.size() && sum(element)!=0){
    S.push_back(element);
  }
  else{
    vector<int> element1 = element;
    element1[i] +=1;
    list_non_zero_elements(i+1, element1);
    vector<int> element2 = element;
    list_non_zero_elements(i+1, element2);
  }
}

int sum(vector<int> v){
  int summand =0;
  for(int k : v)
    summand += k;
  return summand;
}

vector<int> sum_v(vector<int> v1,vector<int> v2){
  vector<int> sum_vector;
  for(int k; k<v1.size();k++)
    sum_vector.push_back(v1[k] + v2[k]);
  return sum_vector;
}

bool is_in(int x, vector<int> v){
  for(int k:v)
    if(k=x)
      return true;
  return false;
}

vector<vector<int>> list_3_index(vector<int> a, vector<int> b, vector<int> c){
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
    cout<<'\n';
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
      for(int i=0;i<m;i++)
        if(i!=indexed_pentagon[k][indexes[0]] && i!=indexed_pentagon[(k+1)%5][indexes[1]] && i!=indexed_pentagon[(k+3)%5][indexes[2]])
          current_max_face.push_back(i);
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
  int n = m+3;
  vector<int> null_v;
  for(int k=0;k<n;k++);
    null_v.push_back(0);
  list_non_zero_elements(0,null_v);
  int N = S.size();
  vector<int> ref_max_face = max_faces[0];
  vector<int> compl_ref_max_face {indexed_pentagon[0][0], indexed_pentagon[1][0],indexed_pentagon[3][0]};
  vector<vector<int>> lambda_template;
  for(int j; j<m; j++){
    vector<int> null_v_cp = null_v;
    lambda_template.push_back(null_v_cp);
  }
  for(int k; k<n;k++)
    lambda_template[ref_max_face[k]][k] = 1;
  int i = 0;
  vector<vector<int>> lambda = lambda_template;
  list_non_zero_elements(0, null_v);
  while(i!=-1){
    vector<vector<int>> S_i = S;
    for(vector<int> max_face : max_faces){
      if(is_in(compl_ref_max_face[0], max_face)){
        bool others_are_not = true;
        for (int j = i+1;j<3;j++)
          if(! is_in(compl_ref_max_face[j], max_face))
            others_are_not = false;
        if(others_are_not){
          vector<int> sum_vector;
          for(int k;k<max_face.size();k++)
            sum_vector = sum_v(sum_vector,lambda[max_face[k]]);      
          for(int S_index;S_index<S_i.size();S_index++){
            if(S_i[S_index]==sum_vector){
              S_i.erase(S_i.begin()+S_index);
              }
            }
          }
        }
      }
    while(S_i.size()!=0){
      lambda[compl_ref_max_face[i]] = S_i.back();
      S_i.pop_back();
      if(i==2)
        list_lambdas.push_back(lambda);
      else{
        i=i+1;
        break;
        }
      }
    i=i-1;
    }
    return list_lambdas;
  }



int main(){
  vector<int> pentagon1 {2,2,2,2,2};
  vector<vector<vector<int>>> list_lambdas = compute_chr_funct(pentagon1);
  cout<<list_lambdas.size()<<'\n';
}
