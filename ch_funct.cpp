#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>


std::vector<std::vector<int>> list_3_index(int, int, int);
std::vector<int> find_max_faces(std::vector<std::vector<int>>);




std::vector<std::vector<int>> list_3_index(int a, int b, int c){
  std::vector<std::vector<int>> list_index;
  for(int i=0; i<a; i++){
    for(int j=0; i<b; j++){
      for(int k=0; i<c; k++){
        std::vector<int> indexes {i,j,k};
        list_index.push_back(indexes);
        }
      }
    }
    return list_index;
  }


std::vector<std::vector<int>> find_max_faces(std::vector<int> pentagon){

  std::vector<std::vector<int>> indexed_pentagon;
  int index = 0;
  for(int k: pentagon){
    std::vector<int> vertice_range;
    for(int l = index; l<index+k;l++){
      vertice_range.push_back(l);
      std::cout<<l<<' ';
      }
    std::cout<<'\n';
    indexed_pentagon.push_back(vertice_range);
    index = index + k;
  };
  std::cout<<"test";
  std::vector<std::vector<int>> maximal_faces;
  for(int k = 0; k<5; k++){
    std::vector<std::vector<int>> list_indexes = list_3_index(pentagon[k], pentagon[(k+1)%5], pentagon[(k+3)%5]);
    for(std::vector<int> indexes : list_indexes){
      std::cout<<indexes[0]<<' '<<indexes[1]<<' '<<indexes[2];
    }
  }
  return maximal_faces;
}


int main(){
  std::vector<int> pentagon1 {2,2,2,2,2};
  find_max_faces(pentagon1);
}
