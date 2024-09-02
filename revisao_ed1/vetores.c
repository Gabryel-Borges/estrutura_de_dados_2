/*
O código abaixo realiza a impressão do vetor na ordem inversa.
1 - comente o código
2 - faça uma modificação para que seja possível inserir um vetor de n elementos.
*/


#include <stdio.h>

int main() {
    int vetor[6] = {0, 1, 2, 3, 4, 5};
    int i, temp, size;

    size = sizeof(vetor)/sizeof(vetor[0]); // obtêm  o tamanho do vetor
    
    for (i = 0; i < size/2; i++) {
        temp = vetor[i];
        vetor[i] = vetor[(size-1) - i];
        vetor[(size-1) - i] = temp;
    }

    printf("Vetor invertido:\n");
    for (i = 0; i < size; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}