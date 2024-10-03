#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma entrega
typedef struct {
    int id;                // ID único da entrega
    char destino[50];     // Destino da entrega
    float peso;          // Peso da entrega
    int ocupada;        // Flag para indicar se o slot está ocupado
} Entrega;

// Estrutura da Tabela Hash
typedef struct {
    Entrega tabela[TAMANHO_HASH];  // Array de entregas
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da entrega
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função hash para duplo hashing
int hash2(int id) {
    return 7 - (id % 7);  // Segunda função hash para duplo hashing
}

// Sondagem linear
int sondagem_linear(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + 1) % TAMANHO_HASH;  // Avança linearmente
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Sondagem quadrática
int sondagem_quadratica(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int i = 1;
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (funcao_hash(id) + i * i) % TAMANHO_HASH;  // Avança quadraticamente
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Duplo hashing
int duplo_hashing(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int step = hash2(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + step) % TAMANHO_HASH;  // Usa duplo hashing
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Função para criar uma nova entrega
Entrega criar_Entrega(int id, const char *destino, float peso) {
    Entrega nova_Entrega;
    nova_Entrega.id = id;
    strcpy(nova_Entrega.destino, destino);
    nova_Entrega.peso = peso;
    nova_Entrega.ocupada = 1;  // Marca o slot como ocupado
    return nova_Entrega;
}

// Função para inserir uma entrega na tabela hash usando sondagem linear
void inserir_linear(TabelaHash *tabela, Entrega Entrega) {
    int indice = funcao_hash(Entrega.id);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = Entrega;
    } else {
        // Se houver colisão, chama a sondagem linear
        int novo_indice = sondagem_linear(tabela, Entrega.id);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = Entrega;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma entrega na tabela hash usando sondagem quadrática
void inserir_quadratica(TabelaHash *tabela, Entrega Entrega) {
    int indice = funcao_hash(Entrega.id);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = Entrega;
    } else {
        // Se houver colisão, chama a sondagem quadrática
        int novo_indice = sondagem_quadratica(tabela, Entrega.id);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = Entrega;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma entrega na tabela hash usando duplo hashing
void inserir_duplo_hashing(TabelaHash *tabela, Entrega Entrega) {
    int indice = funcao_hash(Entrega.id);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = Entrega;
    } else {
        // Se houver colisão, chama o duplo hashing
        int novo_indice = duplo_hashing(tabela, Entrega.id);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = Entrega;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para exibir todas as entregas
void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela->tabela[i].ocupada) {
            printf("Transação ID: %d, Destino: %s, Peso %.2f (Indice: %d)\n",
                   tabela->tabela[i].id, tabela->tabela[i].destino, tabela->tabela[i].peso, i);
        }
    }
}


// Função de busca

Entrega *buscaLinear(int id, TabelaHash *tabela) {
    int indice = funcao_hash(id);
    int tentativas = 0;
    
    while (tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH) {
        indice = (indice + 1) % TAMANHO_HASH;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? &tabela->tabela[indice] : NULL;
};

Entrega *buscaQuadratica(int id, TabelaHash *tabela) {
    int indice = funcao_hash(id);
    int i = 1;
    int tentativas = 0;

    while (tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH) {
        indice = (funcao_hash(id) + i * i) % TAMANHO_HASH;
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? &tabela->tabela[indice] : NULL;
}

Entrega *buscaDuploHash(int id, TabelaHash *tabela) {
    int indice = funcao_hash(id);
    int step = hash2(id);
    int tentativas = 0;

    while (tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH) {
        indice = (indice + step) % TAMANHO_HASH;
        tentativas++;
    }
    
    return (tentativas < TAMANHO_HASH) ? &tabela->tabela[indice] : NULL;
}

// Função de exclusão

void excluiLinear(int id, TabelaHash *tabela) {
    Entrega *excluir = buscaLinear(id, tabela);
    
    if (excluir) {
        excluir->ocupada = 0;
    }
}

void excluiQuadratica(int id, TabelaHash *tabela) {
    Entrega *excluir = buscaQuadratica(id, tabela);
    
    if (excluir) {
        excluir->ocupada = 0;
    }
}

void excluiDuploHash(int id, TabelaHash *tabela) {
    Entrega *excluir = buscaDuploHash(id, tabela);
    
    if (excluir) {
        excluir->ocupada = 0;
    }
}

// Função principal para demonstrar o uso da tabela hash com sondagem
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela_linear = {0};  // Todos os slots começam desocupados

    // Inserir transações na tabela hash usando sondagem linear
    printf("\nInserção com Sondagem Linear:\n");
    inserir_linear(&tabela_linear, criar_Entrega(101, "São Paulo", 21.82));
    inserir_linear(&tabela_linear, criar_Entrega(102, "Rio de Janeiro", 15.50));
    inserir_linear(&tabela_linear, criar_Entrega(103, "Belo Horizonte", 30.75));
    inserir_linear(&tabela_linear, criar_Entrega(104, "Salvador", 22.00));
    inserir_linear(&tabela_linear, criar_Entrega(105, "Porto Alegre", 27.30));
    inserir_linear(&tabela_linear, criar_Entrega(106, "Curitiba", 19.90));
    inserir_linear(&tabela_linear, criar_Entrega(107, "Fortaleza", 35.60));
    inserir_linear(&tabela_linear, criar_Entrega(108, "Brasília", 28.40));
    inserir_linear(&tabela_linear, criar_Entrega(109, "Recife", 18.25));
    inserir_linear(&tabela_linear, criar_Entrega(110, "Manaus", 40.50));
    
    exibir_todas(&tabela_linear);

    // Inserir transações na tabela hash usando sondagem quadrática
    printf("\nInserção com Sondagem Quadrática:\n");
    TabelaHash tabela_quadratica = {0};
    inserir_quadratica(&tabela_quadratica, criar_Entrega(101, "São Paulo", 21.82));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(102, "Rio de Janeiro", 15.50));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(103, "Belo Horizonte", 30.75));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(104, "Salvador", 22.00));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(105, "Porto Alegre", 27.30));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(106, "Curitiba", 19.90));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(107, "Fortaleza", 35.60));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(108, "Brasília", 28.40));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(109, "Recife", 18.25));
    inserir_quadratica(&tabela_quadratica, criar_Entrega(110, "Manaus", 40.50));

    exibir_todas(&tabela_quadratica);

    // Inserir transações na tabela hash usando duplo hashing
    printf("\nInserção com Duplo Hashing:\n");
    TabelaHash tabela_duplo = {0};
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(101, "São Paulo", 21.82));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(102, "Rio de Janeiro", 15.50));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(103, "Belo Horizonte", 30.75));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(104, "Salvador", 22.00));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(105, "Porto Alegre", 27.30));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(106, "Curitiba", 19.90));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(107, "Fortaleza", 35.60));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(108, "Brasília", 28.40));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(109, "Recife", 18.25));
    inserir_duplo_hashing(&tabela_duplo, criar_Entrega(110, "Manaus", 40.50));


    exibir_todas(&tabela_duplo);

    return 0;
}