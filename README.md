# Minimum Latency Problem (MLP)

O Minimum Latency Problem (MLP), também conhecido como Problema da Mínima Latência, se trata de uma variante do clássiso problema de otimização combinatória, [TSP](https://github.com/renatamendesc/TSP). Esse problema consiste em minimizar a **soma dos tempos** de chegada em **todos** os destinos, encontrando o percuso de menor custo acumulado.

## Meta-heurísticas:

Para casos onde o número de destinos que se deseja visitar é muito grande, faz-se necessário o uso de uma meta-heurística para resolver a situação, que não garante a melhor solução de todas, porém, no geral, retorna soluções satisfatórias. Caso contrário, o computador não é capaz de determinar a resposta ótima em um tempo viável. Sendo assim, na resolução do problema foi utilizado a meta-heurística **GILS-RVND**, que une componentes das heurísticas GRASP *(Greedy Randomized Adaptive Search Procedure)*, ILS *(Iterated Local Search)* e RVND *(Randomized Variable Neighborhood Descent)*.

## Rodando o programa:

Para executar o programa, primeiramente, deve-se abrir o terminal na pasta do projeto e compilar, utilizando o comando `make`. Dessa forma, será gerado o arquivo executável. Por fim, basta digitar:

```./tsp instances/(DIGITE UMA INSTÂNCIA)```

É importante deixar claro que a instância escolhida deve estar presente na pasta [instances](https://github.com/renatamendesc/MLP/tree/main/instances).

**Obs:** Os comandos descritos acima correspondem ao terminal do Linux. Eles podem variar com base no sistema operacional utilizado.

## Resultados:
Uma vez implementado corretamente, soluções ótimas conhecidas são obtidas rapidamente para instâncias com até 107 destinos. Todos os resultados da execução do programa foram registrados na pasta [benchmark](https://github.com/renatamendesc/MLP/blob/main/benchmark/bm_final.txt).
