#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma entrega da transportadora
typedef struct Entrega {
    int id;               // ID único da entrega
    char destino[50];     // endereço de entrega
    float peso;           // peso do pacote
    struct Entrega *proximo; // Ponteiro para a próxima entrega (lista ligada)
} Entrega;

// Estrutura da Tabela Hash
typedef struct {
    Entrega *tabela[TAMANHO_HASH];  // Array de ponteiros para o início da lista ligada
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da entrega
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para criar uma nova entrega
Entrega *criar_Entrega(int id, const char *destino, float peso) {
    Entrega *nova_Entrega = (Entrega *)malloc(sizeof(Entrega));

    if (nova_Entrega == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    nova_Entrega->id = id;
    strcpy(nova_Entrega->destino, destino);
    nova_Entrega->peso = peso;
    nova_Entrega->proximo = NULL;
    return nova_Entrega;
}

// Função para inserir uma entrega na tabela hash (usando listas ligadas para colisões)
void inserir(TabelaHash *tabela, Entrega *Entrega) {
    int indice = funcao_hash(Entrega->id);  // Calcula o índice baseado no ID
    Entrega->proximo = tabela->tabela[indice];  // Insere no início da lista ligada
    tabela->tabela[indice] = Entrega;
}

// Função para exibir todas as entregas
void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Entrega *atual = tabela->tabela[i];
        while (atual != NULL) {
            printf("ID: %d, Destino: %s, Peso: %.2f (Indice: %d)\n",
                    atual->id, atual->destino, atual->peso, i);
            atual = atual->proximo;  // Avança para a próxima Entrega
        }
    }
}

// Função para buscar uma entrega na tabela hash pelo ID
Entrega *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para busca
    Entrega *atual = tabela->tabela[indice];
    
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;  // Retorna a entrega se encontrada
        }
        atual = atual->proximo;  // Vai para a próxima entregada na lista ligada
    }
    return NULL;  // Retorna NULL se não for encontrada
}

// Função para excluir uma entrega na tabela hash pelo ID
void excluir(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para exclusão
    Entrega *atual = tabela->tabela[indice];
    Entrega *anterior = NULL;

    while (atual != NULL) {
        if (atual->id == id) {
            // Se o elemento a ser removido for o primeiro da lista
            if (anterior == NULL) {
                tabela->tabela[indice] = atual->proximo;  // Remove o primeiro elemento
            } else {
                anterior->proximo = atual->proximo;  // Remove o elemento no meio ou fim
            }
            free(atual);  // Libera a memória da entrega
            printf("Transação com ID %d foi excluída.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Entrega com ID %d não encontrada para exclusão.\n", id);
}

// Função para contar o número total de elementos (entregas) na tabela hash
int contar_elementos(TabelaHash *tabela) {
    int total = 0;

    // Percorre todas as posições da tabela hash
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Entrega *atual = tabela->tabela[i];

        // Percorre a lista ligada em cada posição
        while (atual != NULL) {
            total++;  // Incrementa o contador para cada entrega encontrada
            atual = atual->proximo;  // Vai para o próximo elemento na lista
        }
    }

    return total;
}


// Função para inserir 20 entregas predefinidas na tabela hash
void inserir_dados_predefinidos(TabelaHash *tabela) {
    // Inserindo entregas diretamente
    inserir(tabela, criar_Entrega(100, "São Paulo", 2000.0));  
    inserir(tabela, criar_Entrega(101, "Rio de Janeiro", 1500.0));  
    inserir(tabela, criar_Entrega(102, "Belo Horizonte", 1200.0));  
    inserir(tabela, criar_Entrega(103, "Miami", 18.0));  
    inserir(tabela, criar_Entrega(104, "Brasília", 1700.0));  
    inserir(tabela, criar_Entrega(105, "Porto Alegre", 1300.0));  
    inserir(tabela, criar_Entrega(106, "Curitiba", 1600.0));  
    inserir(tabela, criar_Entrega(107, "Manaus", 1900.0));  
    inserir(tabela, criar_Entrega(108, "Recife", 1400.0));  
    inserir(tabela, criar_Entrega(109, "Florianópolis", 1100.0));  
    inserir(tabela, criar_Entrega(110, "Fortaleza", 1500.0));  
    inserir(tabela, criar_Entrega(111, "Natal", 1400.0));  
    inserir(tabela, criar_Entrega(112, "Campinas", 1600.0));  
    inserir(tabela, criar_Entrega(113, "Goiânia", 1550.0));  
    inserir(tabela, criar_Entrega(114, "Maceió", 1300.0));  
    inserir(tabela, criar_Entrega(115, "Aracaju", 1450.0));  
    inserir(tabela, criar_Entrega(116, "João Pessoa", 1100.0));  
    inserir(tabela, criar_Entrega(117, "Teresina", 1250.0));  
    inserir(tabela, criar_Entrega(118, "Cuiabá", 1350.0));  
    inserir(tabela, criar_Entrega(119, "Londrina", 950.0));  
    inserir(tabela, criar_Entrega(120, "São Luís", 1550.0)); 
    

    printf("Entregas foram inseridas com sucesso.\n");
}


// Função principal para demonstrar o uso da tabela hash com entregas
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Inserir os dados predefinidos na tabela hash
    inserir_dados_predefinidos(&tabela);
    
    // Exibir todas as entregas inseridas
    printf("\nTodas as entregas inseridas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);

    
    // Busca por uma entrega especifica
    printf("\nBuscar uma Entrega:\n");
    Entrega *t = buscar(&tabela, 102);
    if (t != NULL) {
        printf("Entrega encontrada ID: %d, Destino: %s, Peso: %.2f\n",
                t->id, t->destino, t->peso);
    } else {
        printf("Entrega não encontrada.\n");
    }
    
    
    // Excluir as transações selecionadas
    printf("\nEntrega excluida:\n");
    excluir(&tabela, 119);
    
    // Exibir todas as entregas inseridas
    printf("\nTodas as entregas inseridas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);
    

    return 0;
}



