/*
O código abaixo apresenta a implementação de uma lista linear.

Para esse exemplo, faça:
- Implemente funções adicionais como buscar(int elemento) para encontrar a posição de um elemento na lista.
ou 
- Adicione métodos para inverter a lista, encontrar o máximo/mínimo, ou ordenar a lista.
*/

#include <stdio.h>
#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;

void inserir(int elemento) {
    if (tamanho < MAX_SIZE) {
        lista[tamanho++] = elemento;
    } else {
        printf("Lista cheia!\n");
    }
}

void remover(int index) {
    if (index < 0 || index >= tamanho) {
        printf("Índice inválido!\n");
    } else {
        for (int i = index; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1];
        }
        tamanho--;
    }
}

void imprimir() {
    printf("\nElementos da lista:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

void buscar(int elemento) { // busca o elemento na lista e caso encontre imprime sua posição 
    for (int i = 0; i < tamanho; i++) {

        if (lista[i] == elemento) {
            printf("\nElemento encontrado na posicao: %d\n", i);
            break;
        }

        if (i == tamanho-1)
            printf("\nElemento inexistente na lista\n");
    }
}

void inverter() { // inverte como os elementos estão dispostos na lista
    int temp;

    for (int i = 0; i < tamanho/2; i++) {
        temp = lista[i];
        lista[i] = lista[(tamanho-1) - i];
        lista[(tamanho-1) - i] = temp;
    }
}

void max_min() { // obtêm o valor máximo e mínimo da lista
    int max, min;

    max = lista[0];
    min = lista[0];

    for (int i = 1; i < tamanho; i++) {

        if (lista[i] > max)
            max = lista[i];
        else if (lista[i] < min)
            min = lista[i];

    }

    printf("\nminimo: %d  maximo: %d\n", min, max);
}

void ordenar() {
    // para ordenar a lista foi utilizado o algoritmo bubble sort
    int i, j, temp;

    for (i = 0; i < tamanho-1; i++) {
        for (j = 0; j < tamanho-i-1; j++) {

            if (lista[j] > lista[j+1]){

                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

int main() {
    inserir(70);
    inserir(10);
    inserir(110);
    inserir(40);
    inserir(50);
    inserir(60);
    inserir(80);
    imprimir();
    ordenar();
    imprimir();
    inverter();
    imprimir();
    remover(1);
    imprimir();
    max_min();

    return 0;
}