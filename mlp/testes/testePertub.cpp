#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cfloat>
#include <algorithm>

using namespace std;

int main(){
    clock_t inicio = clock();

    srand(time(NULL));

    vector <int> solucao = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 1};
    vector <int> solucaoInicial = solucao;
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
        // Insere primeira subsequencia:
        for(int k = 0; k < tam2; k++){
            solucao.insert(solucao.begin()+i+k, solucaoInicial[j+k]);
        }

        // Apaga primeira subsequencia:
        for(int k = 0; k < tam2; k++){
            solucao.erase(solucao.begin()+j);
        }

        // Apaga segunda subsequencia:
        for(int k = 0; k < tam1; k++){
            solucao.erase(solucao.begin()+i);
        }

        // Insere segunda subsequencia:
        for(int k = 0; k < tam1; k++){
            solucao.insert(solucao.begin()+j+k, solucaoInicial[i+k]);
        }
    }

    clock_t fim = clock();
    double tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    cout << "Tempo: " << tempo << endl;

    return 0;
}