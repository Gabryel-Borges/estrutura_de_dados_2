#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma entrega
typedef struct {
    int id;                 // ID único da entrega
    char destino[50];       // endereço de entrega
    float peso;             // peso do pacote
    unsigned int dias;      // estimativa de entrega
} Entrega;

// Estrutura da Tabela Hash
typedef struct {
    Entrega *tabela[TAMANHO_HASH];  // Array de ponteiros para armazenar entregas
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da transação
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para inserir uma entega na tabela hash
void inserir(TabelaHash *tabela, Entrega *Entrega) {
    int indice = funcao_hash(Entrega->id);  // Calcula o índice baseado no ID
    tabela->tabela[indice] = Entrega;  // Insere a entrega na tabela
}

// Função para buscar uma entrega na tabela hash pelo ID
Entrega *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para busca
    return tabela->tabela[indice];  // Retorna a transação encontrada
}

void remover(TabelaHash *tabela, int id) {
    tabela->tabela[funcao_hash(id)] = NULL;
}

void showEntregas(TabelaHash *tabela) {

    for (int i=0; i<TAMANHO_HASH; i++) {
        Entrega *n = tabela->tabela[i];

        if (n != NULL) {
            printf("Entrega encontrada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n",
                n->id, n->destino, n->peso, n->dias);
        }   
    }

    printf("\n\n");
}


int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Criação de algumas transações
    Entrega e1 = {1345, "Goianira", 0.45, 1};
    Entrega e2 = {2299, "Teresina", 5.0, 10};
    Entrega e3 = {8756, "Mossoro", 1.2, 8};
    Entrega e4 = {8290, "Sorocaba", 0.1, 3};
    Entrega e5 = {1001, "Neropolis", 2, 1};

    // Insere as transações na tabela hash
    inserir(&tabela, &e1);
    inserir(&tabela, &e2);
    inserir(&tabela, &e3);
    inserir(&tabela, &e4);
    inserir(&tabela, &e5);

    showEntregas(&tabela);

    
    Entrega *t = buscar(&tabela, 8290);
    if (t != NULL) {
        printf("Entrega procurada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n\n",
               t->id, t->destino, t->peso, t->dias);
    } else {
        printf("Entrega não encontrada.\n");
    }

    remover(&tabela, 8290);

    Entrega *t2 = buscar(&tabela, 8290);
    if (t2 != NULL) {
        printf("Entrega encontrada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n",
               t2->id, t2->destino, t2->peso, t2->dias);
    } else {
        printf("Entrega nao encontrada.\n");
    }

    return 0;
}