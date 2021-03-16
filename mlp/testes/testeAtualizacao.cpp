#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cfloat>
#include <algorithm>

using namespace std;

struct subseqInfo{
  double tempoTotal;
  double custoAcumulado;
  double vertices;
};

int main(){
    vector <vector <subseqInfo>> matrizSubseq(dimension+1, vector <subseqInfo> (dimension+1));
    int tam = solucao.size();

    // solucao = {1, 2, 3, 4, 5, 6, 1}

    // Atualização do tempo total:
    for(int i = 0; i < tam; i++){
        for(int j = i; j < tam; j++){
            if(i == j){
                matrizSubseq[i][j].tempoTotal = 0;
            }else{
                matrizSubseq[i][j].tempoTotal = matrizSubseq[i][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[j]];
                matrizSubseq[j][i].tempoTotal = matrizSubseq[i][j].tempoTotal; 
            }
        }
    }

    // Atualização do custo acumulado:
    for(int i = 0; i < tam; i++){
        for(int j = i; j < tam; j++){ 
            if(i == j){
                matrizSubseq[i][j].custoAcumulado = 0;
            }else{
                matrizSubseq[i][j].custoAcumulado = matrizSubseq[i][j-1].custoAcumulado + matrizSubseq[i][j].tempoTotal;
            }      
        }
    }

    for(int i = tam-1; i >= 0; i--){
        for(int j = i; j >= 0; j--){ 
            if(i == j){
                matrizSubseq[i][j].custoAcumulado = 0;
            }else{
                matrizSubseq[i][j].custoAcumulado = matrizSubseq[i][j+1].custoAcumulado + matrizSubseq[i][j].tempoTotal;
            }      
        }
    }
}