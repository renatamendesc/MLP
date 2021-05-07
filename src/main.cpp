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
  double tempoTotal;
  double custoAcumulado;
  double vertices;
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
      if(j == i + 1){
        custoParcial = matrizSubseq[0][i-1].custoAcumulado + matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]];
        tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]];

        custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j]][solucao[i]];
        tempoParcial = tempoParcial + matrizAdj[solucao[j]][solucao[i]];

        custo = custoParcial + ((dimension-j) * (tempoParcial + matrizAdj[solucao[i]][solucao[j+1]])) + matrizSubseq[j+1][dimension].custoAcumulado;
      }else{
        custoParcial = matrizSubseq[0][i-1].custoAcumulado + matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]];
        tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]];

        custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j]][solucao[i+1]];
        tempoParcial = tempoParcial + matrizAdj[solucao[j]][solucao[i+1]];

        custoParcial = custoParcial + ((j-i-2) * (tempoParcial)) + matrizSubseq[i+1][j-1].custoAcumulado;
        tempoParcial = tempoParcial + matrizSubseq[i+1][j-1].tempoTotal;

        custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j-1]][solucao[i]];
        tempoParcial = tempoParcial + matrizAdj[solucao[j-1]][solucao[i]];

        custo = custoParcial + ((dimension-j) * (tempoParcial + matrizAdj[solucao[i]][solucao[j+1]])) + matrizSubseq[j+1][dimension].custoAcumulado;
      }

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
      custoParcial = matrizSubseq[0][i-1].custoAcumulado + ((j-i+1) * (matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]])) + matrizSubseq[j][i].custoAcumulado;
      tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[j]] + matrizSubseq[j][i].tempoTotal;

      custo = custoParcial + ((dimension-j) * (tempoParcial + matrizAdj[solucao[i]][solucao[j+1]]) + matrizSubseq[j+1][dimension].custoAcumulado);

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
vizinhoInfo reinsertion(vector <int> &solucao, vector <vector <subseqInfo>> &matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  for(int i = 1; i < tam-2; i++){
    for(int j = i + 1; j < tam-1; j++){
      custoParcial = matrizSubseq[0][i-1].custoAcumulado + matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+1]];
      tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+1]];

      custoParcial = custoParcial + ((j-i-1) * (tempoParcial)) + matrizSubseq[i+1][j].custoAcumulado;
      tempoParcial = tempoParcial + matrizSubseq[i+1][j].tempoTotal;

      custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j]][solucao[i]];
      tempoParcial = tempoParcial + matrizAdj[solucao[j]][solucao[i]];

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

      custoParcial = custoParcial + ((i-j) * (tempoParcial + matrizAdj[solucao[i]][solucao[j]])) + matrizSubseq[j][i-1].custoAcumulado;
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
vizinhoInfo oropt2(vector <int> &solucao, vector <vector <subseqInfo>> &matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  for(int i = 1; i < tam-2; i++){
    for(int j = 1; j <= tam-3; j++){
      if(i != j){
        if(i < j){
          custoParcial = matrizSubseq[0][i-1].custoAcumulado + matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+2]];
          tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+2]];

          custoParcial = custoParcial + ((j-i-1) * (tempoParcial)) + matrizSubseq[i+2][j+1].custoAcumulado;
          tempoParcial = tempoParcial + matrizSubseq[i+2][j+1].tempoTotal;

          custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j+1]][solucao[i]];
          tempoParcial = tempoParcial + matrizAdj[solucao[j+1]][solucao[i]];

          custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[i]][solucao[i+1]];
          tempoParcial = tempoParcial + matrizAdj[solucao[i]][solucao[i+1]];

          custo = custoParcial + ((dimension-j-1) * (tempoParcial + matrizAdj[solucao[i+1]][solucao[j+2]])) + matrizSubseq[j+2][dimension].custoAcumulado;
        }else{
          custoParcial = matrizSubseq[0][j-1].custoAcumulado + matrizSubseq[0][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[i]];
          tempoParcial = matrizSubseq[0][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[i]];

          custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[i]][solucao[i+1]];
          tempoParcial = tempoParcial + matrizAdj[solucao[i]][solucao[i+1]];

          custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[i+1]][solucao[j]];
          tempoParcial = tempoParcial + matrizAdj[solucao[i+1]][solucao[j]];

          custoParcial = custoParcial + ((i-j-1) * (tempoParcial)) + matrizSubseq[j][i-1].custoAcumulado;
          tempoParcial = tempoParcial + matrizSubseq[j][i-1].tempoTotal;

          custo = custoParcial + ((dimension-i-1) * (tempoParcial + matrizAdj[solucao[i-1]][solucao[i+2]])) + matrizSubseq[i+2][dimension].custoAcumulado;
        }

        if(custo < melhorVizinho.custoMenor){    
          melhorVizinho.iMenor = i;
          melhorVizinho.jMenor = j;
          melhorVizinho.custoMenor = custo;
	      } 
      }
    }
  }

  return melhorVizinho;
}

// Estrutura de vizinhança or-opt-3:
vizinhoInfo oropt3(vector <int> &solucao, vector <vector <subseqInfo>> &matrizSubseq){
  double custoParcial, custo, tempoParcial;
  int tam = solucao.size();
  vizinhoInfo melhorVizinho;
  melhorVizinho.custoMenor = DBL_MAX;

  for(int i = 1; i < tam-3; i++){
    for(int j = 1; j <= tam-4; j++){
      if(i != j){
        if(i < j){
          custoParcial = matrizSubseq[0][i-1].custoAcumulado + matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+3]];
          tempoParcial = matrizSubseq[0][i-1].tempoTotal + matrizAdj[solucao[i-1]][solucao[i+3]];

          custoParcial = custoParcial + ((j-i-1) * (tempoParcial)) + matrizSubseq[i+3][j+2].custoAcumulado;
          tempoParcial = tempoParcial + matrizSubseq[i+3][j+2].tempoTotal;

          custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[j+2]][solucao[i]];
          tempoParcial = tempoParcial + matrizAdj[solucao[j+2]][solucao[i]];

          custoParcial = custoParcial + ((2) * (tempoParcial)) + matrizSubseq[i][i+2].custoAcumulado;
          tempoParcial = tempoParcial + matrizSubseq[i][i+2].tempoTotal;

          custo = custoParcial + ((dimension-j-2) * (tempoParcial + matrizAdj[solucao[i+2]][solucao[j+3]])) + matrizSubseq[j+3][dimension].custoAcumulado;
        }else{
          custoParcial = matrizSubseq[0][j-1].custoAcumulado + matrizSubseq[0][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[i]];
          tempoParcial = matrizSubseq[0][j-1].tempoTotal + matrizAdj[solucao[j-1]][solucao[i]];

          custoParcial = custoParcial + ((2) * (tempoParcial)) + matrizSubseq[i][i+2].custoAcumulado;
          tempoParcial = tempoParcial + matrizSubseq[i][i+2].tempoTotal;

          custoParcial = custoParcial + tempoParcial + matrizAdj[solucao[i+2]][solucao[j]];
          tempoParcial = tempoParcial + matrizAdj[solucao[i+2]][solucao[j]];

          custoParcial = custoParcial + ((i-j-1) * (tempoParcial)) + matrizSubseq[j][i-1].custoAcumulado;
          tempoParcial = tempoParcial + matrizSubseq[j][i-1].tempoTotal;

          custo = custoParcial + ((dimension-i-2) * (tempoParcial + matrizAdj[solucao[i-1]][solucao[i+3]])) + matrizSubseq[i+3][dimension].custoAcumulado;
        }

        if(custo < melhorVizinho.custoMenor){    
          melhorVizinho.iMenor = i;
          melhorVizinho.jMenor = j;
          melhorVizinho.custoMenor = custo;
	      }
      }
    }
  }

  return melhorVizinho;
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
        matrizSubseq[j][i].tempoTotal = matrizSubseq[i][j].tempoTotal;  
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

// Função com os movimentos de vizinhança:
void RVND(vector <int> &solucao, vector <vector <subseqInfo>> &matrizSubseq){
  vector <int> movimentos = {0, 1, 2, 3, 4};
  vizinhoInfo vizinho;

  while(!movimentos.empty()){
    int escolhido = rand() % movimentos.size();

    // Realiza o movimento:
    if(movimentos[escolhido] == 0){
      vizinho = swap(solucao, matrizSubseq);

      //Realiza o movimento:
      if(vizinho.custoMenor < matrizSubseq[0][dimension].custoAcumulado){

        int aux = solucao[vizinho.iMenor];
	      solucao[vizinho.iMenor] = solucao[vizinho.jMenor];
	      solucao[vizinho.jMenor] = aux;

        // Atualiza a matriz de subsequências com a nova solução:
        atualizaSubseq(matrizSubseq, solucao);
        movimentos = {0, 1, 2, 3, 4};

      }else {
        movimentos.erase(movimentos.begin() + escolhido);
      }

    }else if(movimentos[escolhido] == 1){

      vizinho = reinsertion(solucao, matrizSubseq);

      // Realiza o movimento:
      if(vizinho.custoMenor < matrizSubseq[0][dimension].custoAcumulado){
        vector <int> solucaoInicial = solucao;

        solucao.erase(solucao.begin()+vizinho.iMenor);
        solucao.insert(solucao.begin()+vizinho.jMenor, solucaoInicial[vizinho.iMenor]);

        // Atualiza a matriz de subsequências com a nova solução:
        atualizaSubseq(matrizSubseq, solucao);
        movimentos = {0, 1, 2, 3, 4};

      }else {
        movimentos.erase(movimentos.begin() + escolhido);
      }

    }else if(movimentos[escolhido] == 2){

      vizinho = twoOpt(solucao, matrizSubseq);

      // Realiza o movimento:
      if(vizinho.custoMenor < matrizSubseq[0][dimension].custoAcumulado){
        int aux, k = vizinho.jMenor - vizinho.iMenor;

        if(k % 2 != 0){
          k = k + 1;
        }

        for(int q = 0; q < k/2; q++){
          aux = solucao[vizinho.iMenor+q];
          solucao[vizinho.iMenor+q] = solucao[vizinho.jMenor-q];
          solucao[vizinho.jMenor-q] = aux;
        }

        // Atualiza a matriz de subsequências com a nova solução:
        atualizaSubseq(matrizSubseq, solucao);
        movimentos = {0, 1, 2, 3, 4};

      } else {
        movimentos.erase(movimentos.begin() + escolhido);
      }

    }else if(movimentos[escolhido] == 3){

      vizinho = oropt2(solucao, matrizSubseq);

      // Realiza o movimento:
      if(vizinho.custoMenor < matrizSubseq[0][dimension].custoAcumulado){
        if(vizinho.iMenor < vizinho.jMenor){
          solucao.insert(solucao.begin() + vizinho.jMenor + 2, solucao[vizinho.iMenor]); 
          solucao.insert(solucao.begin() + vizinho.jMenor + 3, solucao[vizinho.iMenor+1]); 
          solucao.erase(solucao.begin() + vizinho.iMenor);
          solucao.erase(solucao.begin() + vizinho.iMenor);
        } else {
          solucao.insert(solucao.begin() + vizinho.jMenor, solucao[vizinho.iMenor]); 
          solucao.insert(solucao.begin() + vizinho.jMenor + 1, solucao[vizinho.iMenor + 2]); 
          solucao.erase(solucao.begin() + vizinho.iMenor + 2);
          solucao.erase(solucao.begin() + vizinho.iMenor + 2);
        }

        // Atualiza a matriz de subsequências com a nova solução:
        atualizaSubseq(matrizSubseq, solucao);
        movimentos = {0, 1, 2, 3, 4};

      } else {
        movimentos.erase(movimentos.begin() + escolhido);
      }   

    }else if(movimentos[escolhido] == 4){

      vizinho = oropt3(solucao, matrizSubseq);

      //Realiza o movimento:
      if(vizinho.custoMenor < matrizSubseq[0][dimension].custoAcumulado){
        if(vizinho.iMenor < vizinho.jMenor){
          solucao.insert(solucao.begin() + vizinho.jMenor + 3, solucao[vizinho.iMenor]);
          solucao.insert(solucao.begin() + vizinho.jMenor + 4, solucao[vizinho.iMenor+1]); 
          solucao.insert(solucao.begin() + vizinho.jMenor + 5, solucao[vizinho.iMenor+2]);
          solucao.erase(solucao.begin() + vizinho.iMenor);
          solucao.erase(solucao.begin() + vizinho.iMenor);
          solucao.erase(solucao.begin() + vizinho.iMenor);
        } else {
          solucao.insert(solucao.begin() + vizinho.jMenor, solucao[vizinho.iMenor]);
          solucao.insert(solucao.begin() + vizinho.jMenor + 1, solucao[vizinho.iMenor + 2]); 
          solucao.insert(solucao.begin() + vizinho.jMenor + 2, solucao[vizinho.iMenor + 4]); 
          solucao.erase(solucao.begin() + vizinho.iMenor + 3);
          solucao.erase(solucao.begin() + vizinho.iMenor + 3);
          solucao.erase(solucao.begin() + vizinho.iMenor + 3);
        }

        // Atualiza a matriz de subsequências com a nova solução:
        atualizaSubseq(matrizSubseq, solucao);
        movimentos = {0, 1, 2, 3, 4};

      } else {
        movimentos.erase(movimentos.begin() + escolhido);
      }      
    }
  }
}

vector <int> pertub(vector <int> &solucaoInicial){
  vector <int> solucao = solucaoInicial;
  int i, j, tam1, tam2, tam = solucao.size();

  // Gera tamanho das subsequencias:
  if(tam < 20){
    tam1 = 2;
		tam2 = 2;
  }else{
    tam1 = rand() % ((tam/10)-(2)+1) + 2;
    tam2 = rand() % ((tam/10)-(2)+1) + 2;
  }

  //Gera posição incial da subsequencia 1:
  i = rand() % ((tam-tam1-1)-(1)+1) + 1;

	j = rand() % ((tam-tam2-1)-(1)+1) + 1;
  while((j > (i - tam2) && j < (i + tam1))){
		j = rand() % ((tam-tam2-1)-(1)+1) + 1;
	}

  if(i < j){
  // Insere primeira subsequencia:
    for(int k = 0; k < tam1; k++){
      solucao.insert(solucao.begin()+j+k, solucaoInicial[i+k]);
    }

    // Apaga primeira subsequencia:
    for(int k = 0; k < tam1; k++){
      solucao.erase(solucao.begin()+i);
    }

    // Apaga segunda subsequencia:
    for(int k = 0; k < tam2; k++){
      solucao.erase(solucao.begin()+j);
    }

    // Insere segunda subsequencia:
    for(int k = 0; k < tam2; k++){
      solucao.insert(solucao.begin()+i+k, solucaoInicial[j+k]);
    }

    }else{
    // Insere segunda subsequencia:
    for(int k = 0; k < tam2; k++){
      solucao.insert(solucao.begin()+i+k, solucaoInicial[j+k]);
    }

    // Apaga segunda subsequencia:
    for(int k = 0; k < tam2; k++){
      solucao.erase(solucao.begin()+j);
    }

    // Apaga primeira subsequencia:
    for(int k = 0; k < tam1; k++){
      solucao.erase(solucao.begin()+i);
    }

    // Insere primeira subsequencia:
    for(int k = 0; k < tam1; k++){
      solucao.insert(solucao.begin()+j+k, solucaoInicial[i+k]);
    }
  }

  return solucao;
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

// Algoritmo principal:
double mlp(int iIls, int v){
  double custo = DBL_MAX, custoAtual, custoFinal = DBL_MAX;
  vector <int> destinos, solucao, solucaoAtual, solucaoFinal;
  vector <vector <subseqInfo>> matrizSubseq(dimension+1, vector <subseqInfo> (dimension+1));

  // Forma vector com todos os vértices (destinos):
  for(int i = 1; i <= v; i++){
    destinos.push_back(i);
  }

  for(int iterMax = 0; iterMax < 10; iterMax++){
    double valorAleatorio = (rand() % 90) / 100.0 + 0.1;

    solucaoAtual = construcao(destinos, valorAleatorio);
    atualizaSubseq(matrizSubseq, solucaoAtual);

    solucao = solucaoAtual;

    int iterIls = 0;
    while(iterIls < iIls){
      RVND(solucaoAtual, matrizSubseq);

      custoAtual = matrizSubseq[0][dimension].custoAcumulado;

      if(custoAtual < custo){
        solucao = solucaoAtual;
        custo = custoAtual;
        iterIls = 0;
      }

      solucaoAtual = pertub(solucao);
      atualizaSubseq(matrizSubseq, solucaoAtual);

      iterIls++;
    }

    if(custo < custoFinal){
      solucaoFinal = solucao;
      custoFinal = custo;
    }
  }

  cout << "Solução: ";
  for(int i = 0; i < solucaoFinal.size(); i++){
    cout << solucaoFinal[i] << " ";
  }

  cout << endl;

  return custoFinal;  
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
