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
  vector <int> solucao = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};

  double custoParcial, custo = 0, tempoParcial, tempo = 0;
  int tam = solucao.size();
  vector <int > solucaoInicial = solucao;
  vector <int > vizinho = solucao;


  for(int i = 1; i < tam-2; i++){
    for(int j = i + 1; j < tam-1; j++){

      solucaoInicial.erase(solucaoInicial.begin()+i);
      solucaoInicial.insert(solucaoInicial.begin()+j, vizinho[i]);

      printf("Vizinho[%d][%d]: ", i, j);
      for(int l = 0; l < tam; l++){
        printf("%d ", solucaoInicial[l]);
      }
      cout << endl;

      solucaoInicial = solucao;
      vizinho = solucao;
    }
  }

  cout << endl;

  for(int j = 1; j < tam-2; j++){
    for(int i = j + 1; i < tam-1; i++){

      solucaoInicial.erase(solucaoInicial.begin()+i);
      solucaoInicial.insert(solucaoInicial.begin()+j, vizinho[i]);

      printf("Vizinho[%d][%d]: ", i, j);
      for(int l = 0; l < tam; l++){
        printf("%d ", solucaoInicial[l]);
      }
      cout << endl;

      solucaoInicial = solucao;
      vizinho = solucao;
    }
  }

}