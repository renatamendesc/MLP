#include "readData.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cfloat>
#include <algorithm>

using namespace std;

double ** matrizAdj; 
int dimension; 

struct insercaoInfo{
  int noInserido;
  int deslocado; 
  double custo;
};

struct vizinhoInfo{
  int iMenor;
  int jMenor;
  double custoMenor;
};

struct subseqInfo{
  double tempoTotal, custoAcumulado, vertices;
};


// Função de comparação utilizada para ordenar o vetor na construção:
bool comparacao(insercaoInfo a, insercaoInfo b){
  return a.custo < b.custo;
}

vizinhoInfo twoOpt(vector <int> &solucao){
  double custo;
  int tam = solucao.size();

}

// Função referente à etapa da construção:
vector <int> construcao(vector <int> listaCandidatos, double valorAleatorio){
  vector <int> solucaoInicial;

  // Insere depósito na solução:
  solucaoInicial.push_back(listaCandidatos[0]);
  solucaoInicial.push_back(listaCandidatos[0]);

  // Apaga da lista de candidatos:
  listaCandidatos.erase(listaCandidatos.begin());

  // Escolhe 3 vertices aleatoriamente:
  for(int i = 0; i < 3; i++){
    int j = rand() % listaCandidatos.size();
    solucaoInicial.insert(solucaoInicial.begin()+1, listaCandidatos[j]); 
    listaCandidatos.erase(listaCandidatos.begin()+j);
  }

  while(!listaCandidatos.empty()){
    vector <insercaoInfo> custoInsercao((solucaoInicial.size()-1) * listaCandidatos.size());
    for(int j = 0, l = 1, q = 0; j < solucaoInicial.size()-1; j++, l++){
      for(auto k : listaCandidatos){
        custoInsercao[q].custo = matrizAdj[solucaoInicial[j]][k] + matrizAdj[solucaoInicial[l]][k] - matrizAdj[solucaoInicial[j]][solucaoInicial[l]];
        custoInsercao[q].noInserido = k;
        custoInsercao[q].deslocado = j;
        q++;
      }
    }

    // Ordena os custos de insercao em ordem crescente:
    sort(custoInsercao.begin(), custoInsercao.end(), comparacao);

    // Gera quantidade de elementos iniciais a serem escolhidos aleatoriamente no percurso:
    int elementos = valorAleatorio * custoInsercao.size();
    int i = rand() % elementos;

    // Insere vertice escolhido no percuso:
    solucaoInicial.insert(solucaoInicial.begin() + (custoInsercao[i].deslocado + 1), custoInsercao[i].noInserido);

    // Apaga da lista de candidatos o vertice que foi inserido:
    for(int j = 0; j < listaCandidatos.size(); j++){
      if(listaCandidatos[j] == custoInsercao[i].noInserido)
        listaCandidatos.erase(listaCandidatos.begin()+j);
    }
  }
  return solucaoInicial;
}

// Função que atualiza valores do custo acumulado e tempo total:
void atualizaSubseq(vector <vector <subseqInfo>> &matrizSubseq, vector <int> &solucao){
  int tam = solucao.size();

  // Atualização do tempo total:
  for(int i = 0; i < tam; i++){
    for(int j = i; j < tam; j++){
      if(i == j){
        matrizSubseq[i][j].tempoTotal = 0;
      }else {
        matrizSubseq[i][j].tempoTotal = matrizSubseq[i][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[j]]; 
      }
    }
  }

  // Atualização do custo acumulado:
  for(int i = 0; i < tam; i++){
    for(int j = i; j < tam; j++){ 
      if(i == j){
        matrizSubseq[i][j].custoAcumulado = 0;
      }else {
        matrizSubseq[i][j].custoAcumulado = matrizSubseq[i][j-1].custoAcumulado + matrizSubseq[i][j].tempoTotal;
      }      
    }
  }
}

// Algoritmo principal:
double mlp(int iIls, int v){
  vector <int> destinos;
  vector <int> solucao;
  vector <vector <subseqInfo>> matrizSubseq(dimension+1, vector <subseqInfo> (dimension+1));

  for(int i = 1; i <= v; i++){
    destinos.push_back(i);
  }

  for(int iterMax = 0; iterMax < 1; iterMax++){
    double valorAleatorio = (rand() % 90) / 100.0 + 0.1;

    solucao = construcao(destinos, valorAleatorio);
    atualizaSubseq(matrizSubseq, solucao);

    vector <int> solucaoAtual = solucao;

    int iterIls = 0;
    while(iterIls < iIls){

    }
  } 

  
}

int main(int argc, char** argv) {
  // Inicio da contagem do tempo:  
  clock_t inicio = clock();
    
  readData(argc, argv, &dimension, &matrizAdj);
  srand(time(NULL));

  int iIls;
    
  if(dimension >= 150){
    iIls = dimension/2;
  } else {
    iIls = dimension;
  }

  double custoAcumuladoFinal = mlp(iIls, dimension);

  // Fim da contagem do tempo:
  clock_t fim = clock();
  double tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

  cout << "Custo acumulado: " << custoAcumuladoFinal << endl;
  cout << "Tempo: " << tempo << endl;
    
  return 0;
}
