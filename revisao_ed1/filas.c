/*
O código abaixo apresenta a implementação de uma fila e suas operações básicas.

1 - comente o código
2 - implemente uma função para contar o número de elementos na fila.
3 - implemente uma função para limpar todos os elementos da fila, liberando memória apropriadamente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Falha na alocacao de memoria para a fila.\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Falha na alocacao de memoria para o novo no.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) { 
        q->front = q->rear = newNode;
    } else { 
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if (q->front == NULL) { 
        printf("Fila esta vazia.\n");
        return -1;
    }
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("A fila esta vazia.\n");
        return;
    }
    Node* temp = q->front;
    printf("Elementos da fila: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int countQueue(Queue *queue) { // conta a quantidade de elementos na fila
    int count = 0;
    Node *n = queue->front;

    while (n != NULL) {
        count++;
        n = n->next;
    }

    return count;
}

void freeQueue(Queue *queue) { // esvazia toda a fila
    int size = countQueue(queue);

    for (int i = 0; i < size; i++) {
        dequeue(queue);
    }

    printf("\nTodos os elementos da fila foram apagados\n");
}

int main() {
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);

    printf("\nsize: %d", countQueue(q));

    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);

    printf("\nsize: %d", countQueue(q));

    freeQueue(q);
    printQueue(q);

    return 0;
}