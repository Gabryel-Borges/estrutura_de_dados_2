/*
O código abaixo apresenta a implementação de uma pilha e suas operações básicas.

1 - comente o código
2 - implemente uma função para verificar se a pilha está vazia.
3 - proponha uma função que possa fazer expansão dinâmica quando a capacidade máxima é atingida, em vez de simplesmente negar novas inserções na pilha.
*/

#include <stdio.h>
#include <stdlib.h>

int maxSize = 3;
int topo = -1;

void expandStack(int *pilha) { // redimensiona o tamanho da pilha
    realloc(pilha, ++maxSize * sizeof(int));
}

void push(int *pilha, int elemento) {
    if (topo < maxSize - 1) {
        pilha[++topo] = elemento;
    } else {
        expandStack(pilha); // quando a pilha atinge sua capacidade máxima inicial é chamado a função que redimensiona a pilha para poder caber mais um dado
        pilha[++topo] = elemento; // depois de redimensionada a pilha pode fazer o push do novo dado
    }
}

int pop(int *pilha) {
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo--];
    }
}

int top(int *pilha) {
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo];
    }
}

void imprimir(int *pilha) {
    printf("Conteudo da pilha:\n");
    for (int i = topo; i >= 0; i--) {
        printf("%d ", pilha[i]);
    }
    printf("\n");
}

void checkStack() { // verifica se a pilha está vazia ou não
    if (topo == -1)
        printf("A pilha esta vazia\n");
    else
        printf("A pilha nao esta vazia\n");
}

int main() {
   int *pilha = malloc(maxSize * sizeof(int));

   push(pilha, 10);
   push(pilha, 20);
   push(pilha, 30);

   imprimir(pilha);
   push(pilha, 40);
   imprimir(pilha);
   pop(pilha);
   imprimir(pilha);
   
    return 0;
}