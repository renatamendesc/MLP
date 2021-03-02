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
    vector <vector <subseqInfo>> matrizSubseq(7, vector <subseqInfo> (7));
    vector <int> solucao = {1, 2, 3, 4, 5, 6, 1}; // tam = 7


    cout << matrizSubseq[6][5].custoAcumulado << endl; 

    // Atualização do custo acumulado:
    for(int i = 0; i < solucao.size(); i++){
      for(int j = i; j < solucao.size(); j++){ 
        if(i == j){
          matrizSubseq[i][j].tempoTotal = 0;
        }else {
          matrizSubseq[i][j].tempoTotal = matrizSubseq[i][j-1].tempoTotal + 1; 
        }      
      }
    }

    // Atualização do custo acumulado:
    for(int i = 0; i < solucao.size(); i++){
      for(int j = i; j < solucao.size(); j++){ 
        if(i == j){
          matrizSubseq[i][j].custoAcumulado = 0;
        }else {
          matrizSubseq[i][j].custoAcumulado = matrizSubseq[i][j-1].custoAcumulado + matrizSubseq[i][j].tempoTotal;
        }      
      }
    }

    cout << matrizSubseq[1][6].custoAcumulado << endl;

}