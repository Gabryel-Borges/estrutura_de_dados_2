/*
O código apresenta uma lista duplamente ligada com operações básicas para inserir, deletar e imprimir.

1 - comente o código.
2 - Modifique a operação de inserção de dados, para que o usuário seja capaz de inserir valores para a lista.
3 - Faça uma operação de buscar por um valor específico, informado pelo usuário, onde o programa deve apresentar se o valor foi encontrado e, em caso afirmativo, exibir detalhes(vizinhos) do nó correspondente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* head = NULL;

void insertFront(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

Node *searchNode(int value, int show) {
    Node *n = head;

    while (n != NULL) {

        if (value == n->data) {

            if (show) { // quando o parâmetro show é igual a 1 as informações de onde foi encontrado o nó são exibidas, caso seja igual a 0 as informações são ocultadas 
                if (n->prev == NULL) // Quando não existe nó a esquerda do nó procurado
                    printf("\n%d foi encontrado na lista entre ... - %d - %d\n", n->data, n->data, n->next->data);

                else if (n->next == NULL) // Quando não existe nó a direita do nó procurado
                    printf("\n%d foi encontrado na lista entre %d - %d - ...\n", n->data, n->prev->data, n->data);

                else // Quando o nó procurado possui vizinho tanto a esquerda, quanto a direita
                    printf("\n%d foi encontrado na lista entre %d - %d - %d\n", n->data, n->prev->data, n->data, n->next->data);
            }
            
            return n; // retorna o endereço do nó para a chamadora
        }

        n = n->next; // vai pro próximo nó da lista
    }
    
    printf("\n%d nao foi encontrado na lista\n", value);
    return NULL;
}

void deleteNode(int value) {
    Node *node = searchNode(value, 0); // procura o nó na lista que possui esse valor

    if (node != NULL) {
        if (node == head)
            head = node->next;
        if (node->next != NULL)
            node->next->prev = node->prev;
        if (node->prev != NULL)
            node->prev->next = node->next;
        free(node);
    }
    
}

void printList() {
    Node* temp = head;

    printf("\n");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int operacao = 1;
    int value;

    // menu para executar as operações sobre a lista
    printf("\n1 - Inserir valor na lista\n");
    printf("2 - Remover valor da lista\n");
    printf("3 - Exibir lista\n");
    printf("4 - Buscar valor na lista\n");
    printf("0 - Sair\n");

    while (operacao != 0) {
        printf("\nDigite a operacao desejada: ");
        scanf("%d", &operacao);

        switch(operacao) {
            case 0:
                printf("\nProcedimento encerrado\n");
                break;
            case 1:
                printf("Digite o valor que deseja inserir: ");
                scanf("%d", &value);
                insertFront(value);
                break;
            case 2:
                printf("Digite o valor que deseja remover: ");
                scanf("%d", &value);
                deleteNode(value);
                break;
            case 3:
                printList();
                break;
            case 4:
                printf("Digite o valor que deseja buscar: ");
                scanf("%d", &value);
                searchNode(value, 1);
                break;
            default:
                printf("\nOperacao inexistente\n");
                break;
        }
    }

    return 0;
}