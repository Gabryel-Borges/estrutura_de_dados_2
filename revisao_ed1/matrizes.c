/*
O código abaixo recebe do usuário elementos que são inseridos em uma matriz 3x3, em seguida, imprime a soma de sua diagonal principal.
- faça uma modificação para que seja possível dinamizar o tamanho da matriz (utilizar alocação dinâmica de memória usando malloc)
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int dimensao;
    int i, j, soma = 0;

    printf("Entre com a dimensao dessa matriz quadrada: "); // para existir diagonal principal é preciso que a matriz seja quadrada, logo o n° de linhas deve ser igual ao n° de colunas
    scanf("%d", &dimensao);

    int matriz[dimensao][dimensao]; // cria a matriz com a dimensão fornecida
    
    printf("\nInsira os elementos da matriz %dx%d:\n", dimensao, dimensao);
    for (i = 0; i < dimensao; i++) {
        for (j = 0; j < dimensao; j++) {
            scanf("%d", &matriz[i][j]);
            if (i == j) {
                soma += matriz[i][j];
            }
        }
    }

    printf("Soma dos elementos da diagonal principal: %d\n", soma);
    return 0;
}