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

// Estrutura de vizinhança swap:
vizinhoInfo swap(vector <int> &solucao, vector <vector <subseqInfo>> &matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  for(int i = 1; i < tam-2; i++){
    for(int j = i+1; j < tam-1; j++){
      custoParcial = matrizSubseq[0][i-1].custoAcumualdo + matrizSubseq.[0][i-1]tempoTotal + matrizAdj[solucao[i-1]][solucao[j]];
      tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]];

      custoParcial = custoParcial + (((j-1)-(i+1)) * (tempoParcial + matrizAdj[solucao[j]][solucao[i+1]] + matrizSubseq[i+1][j-1].custoAcumulado));
      tempoParcial = tempoParcial  + matrizSubseq[i+1][j-1].tempoTotal + matrizAdj[solucao[j]][solucao[i+1]];

      custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j-1]][solucao[i]];
      tempoParcial = tempoParcial + matrizAdj[solucao[j-1]][solucao[i]];

      custo = custoParcial + ((dimension-j) * (tempoParcial + matrizAdj[solucao[i]][solucao[j+1]])) + matrizSubseq[j+1][dimension].custoAcumulado;

      if(custo < melhorVizinho.custoMenor){    
        melhorVizinho.iMenor = i;
        melhorVizinho.jMenor = j;
        melhorVizinho.custoMenor = custo;
	    } 
    }
  }

  return melhorVizinho;
}

// Estrutura de vizinhança 2-opt:
vizinhoInfo twoOpt(vector <int> &solucao, vector <vector <subseqInfo>> &matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  for(int i = 1; i < tam; i++){
    for(int j = i+1; j < tam-1; j++){
      custoParcial = matrizSubseq[0][i-1].custoAcumulado + ((j-i+1) * (matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i]])) + matrizSubseq[i][j].custoAcumulado;
      tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i]] + matrizSubseq[i][j].tempoTotal;

      custo = custoParcial + ((j+1) * (tempoParcial + matrizAdj[solucao[j]][solucao[j+1]]) + matrizSubseq[j+1][dimension].custoAcumulado);

      if(custo < melhorVizinho.custoMenor){    
        melhorVizinho.iMenor = i;
        melhorVizinho.jMenor = j;
        melhorVizinho.custoMenor = custo;
	    } 
    }
  }

  return melhorVizinho;
}

// Estrutura de vizinhança reinsertion:
vizinhoInfo reinsertion(vector <int> &solucao, vector <vector <subseqInfo>> & matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  for(int i = 1; i < tam-2; i++){
    for(int j = i + 1; j < tam-1; j++){
      custoParcial = matrizSubseq[0][i-1].custoAcumulado + matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+1]];
      tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+1]];

      custoParcial = custoParcial + ((j-i) * (t1 + matrizAdj[solucao[i+1]][solucao[i+2]])) + matrizSubseq[i+2][j].custoAcumulado + matrizSubseq[i+2][j].tempoTotal + matrizAdj[solucao[j]][solucao[i]];
      tempoParcial = tempoParcial + matrizSubseq[i+1][j].tempoTotal + matrizAdj[solucao[j]][solucao[i]];

      custo = custoParcial + ((dimension-j) * (tempoParcial + matrizAdj[solucao[i]][solucao[j+1]])) + matrizSubseq[j+1][dimension].custoAcumulado;

      if(custo < melhorVizinho.custoMenor){    
        melhorVizinho.iMenor = i;
        melhorVizinho.jMenor = j;
        melhorVizinho.custoMenor = custo;
	    } 
    }
  }

  for(int j = 1; j < tam-2; j++){
    for(int i = j + 1; i < tam-1; i++){
      custoParcial = matrizSubseq[0][j-1].custoAcumulado + matrizSubseq[0][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[i]];
      tempoParcial = matrizSubseq[0][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[i]];

      custoParcial = custoParcial + ((i-j) * (tempoParcial + matrizAdj[solucao[i][solucao[j]])) + matrizSubseq[j][i-1].custoAcumulado;
      tempoParcial = tempoParcial + matrizAdj[solucao[i]][solucao[j]] + matrizSubseq[j][i-1].tempoTotal;

      custo = custoParcial + ((dimension-i) * (tempoParcial + matrizAdj[solucao[i-1]][solucao[i+1]])) + matrizSubseq[i+1][dimension].custoAcumulado;

      if(custo < melhorVizinho.custoMenor){    
        melhorVizinho.iMenor = i;
        melhorVizinho.jMenor = j;
        melhorVizinho.custoMenor = custo;
	    } 
    }
  }

  return melhorVizinho;
}

// Estrutura de vizinhança or-opt-2:
vizinhoInfo oropt2(vector <int> &solucao, vector <vector <subseqInfo>> & matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  
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

  // Forma vetor com todos os vértices (destinos):
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
