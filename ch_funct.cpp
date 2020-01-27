#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


vector<vector<int>> list_3_index(int, int, int);
vector<vector<int>> index_pentagon(vector<int>);
vector<vector<int>> find_max_faces(vector<int>);
vector<vector<int>> find_min_non_faces(vector<int>);





vector<vector<int>> list_3_index(int a, int b, int c){
  vector<vector<int>> list_index;
  for(int i=0; i<a; i++)
    for(int j=0; j<b; j++)
      for(int k=0; k<c; k++)
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

vector<vector<int>> find_max_faces(vector<int> pentagon){
  int m =0;
  for(int k:pentagon)
    m+=k;
  vector<vector<int>> indexed_pentagon = index_pentagon(pentagon);
  vector<vector<int>> maximal_faces;
  for(int k = 0; k<5; k++){
    vector<vector<int>> list_indexes = list_3_index(pentagon[k], pentagon[(k+1)%5], pentagon[(k+3)%5]);
    for(vector<int> indexes : list_indexes){
      vector<int> current_max_face;
      for(int i=0;i<m;i++)
        if(i!=indexed_pentagon[k][indexes[0]] && i!=indexed_pentagon[(k+1)%5][indexes[1]] && i!=indexed_pentagon[(k+3)%5][indexes[2]])
          current_max_face.push_back(i);
      maximal_faces.push_back(current_max_face);
    }
  }
  return maximal_faces;
}

vector<vector<int>> find_min_non_faces(vector<int> pentagon){
  vector<vector<int>> indexed_pentagon= index_pentagon(pentagon);
  vector<vector<int>> list_min_non_faces;
  for(int k=0;k<4;k++){
    vector<int> current_min_non_face(indexed_pentagon[k]);
    current_min_non_face.insert(current_min_non_face.end(),indexed_pentagon[(k + 1) % 5].begin(), indexed_pentagon[(k + 1) % 5].end());
    list_min_non_faces.push_back(current_min_non_face);
  }
  vector<int> current_min_non_face(indexed_pentagon[0]);
  current_min_non_face.insert(current_min_non_face.end(),indexed_pentagon[4].begin(), indexed_pentagon[4].end());
  list_min_non_faces.push_back(current_min_non_face);
  return list_min_non_faces;

}

int main(){
  vector<int> pentagon1 {2,2,2,2,2};
  find_max_faces(pentagon1);
}
