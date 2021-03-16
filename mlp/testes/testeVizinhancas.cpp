#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cfloat>
#include <algorithm>

using namespace std;

struct subseqInfo{
  double tempoTotal, custoAcumulado, vertices;
};

int main(){
  //vector <vector <subseqInfo>> matrizSubseq(dimension+1, vector <subseqInfo> (dimension+1));
  vector <int> solucaoInicial = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};

  double custoParcial, custo = 0, tempoParcial, tempo = 0;
  int tam = solucaoInicial.size();
  vector <int > solucao = solucaoInicial;
  vector <int > vizinho = solucaoInicial;

  // Or-opt-3:
  for(int i = 1; i < tam-3; i++){
    for(int j = 1; j <= tam-4; j++){
      if(i != j){
        if(i < j){
          solucao.insert(solucao.begin() + j + 3, solucao[i]);
          solucao.insert(solucao.begin() + j + 4, solucao[i+1]); 
          solucao.insert(solucao.begin() + j + 5, solucao[i+2]);
          solucao.erase(solucao.begin() + i);
          solucao.erase(solucao.begin() + i);
          solucao.erase(solucao.begin() + i);
        } else {
          solucao.insert(solucao.begin() + j, solucao[i]);
          solucao.insert(solucao.begin() + j + 1, solucao[i + 2]); 
          solucao.insert(solucao.begin() + j + 2, solucao[i +  4]); 
          solucao.erase(solucao.begin() + i + 3);
          solucao.erase(solucao.begin() + i + 3);
          solucao.erase(solucao.begin() + i + 3);
        }
      }

      printf("Vizinho[%d][%d]: ", i, j);
      for(int l = 0; l < tam; l++){
        printf("%d ", solucao[l]);
      }

      cout << endl;

      solucao = solucaoInicial;
      vizinho = solucaoInicial;
    }
  }
}