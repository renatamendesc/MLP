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
  vector <int> vizinho = solucao;

  // i = inicio da subsequencia
  // j = fim da subsequencia

  // custoAcumulado = matrizSubseq[0][i-1].custoAcumulado + ((j-i+1) * (matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i]])) + matrizSubseq[i][j].custoAcumulado

  for(int i = 1; i < tam; i++){
    for(int j = i+1; j < tam-1; j++){
      int aux, k = j - i;

      if(k % 2 != 0){
        k = k + 1;
      }

      for(int q = 0; q < k/2; q++){
        aux = vizinho[i+q];
        vizinho[i+q] = vizinho[j-q];
        vizinho[j-q] = aux;
      }

      cout << "Vizinho: ";
      for(int q = 0; q < vizinho.size(); q++){
        cout << vizinho[q] << " ";
      }

      cout << endl;

      vizinho = solucao;
    }
  }
}