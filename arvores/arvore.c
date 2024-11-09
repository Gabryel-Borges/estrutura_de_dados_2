#include <stdio.h>
#include <stdlib.h>

typedef struct No { // estrutura do nó
    int id;
    int numCurtidas;
    int numComentarios; 
    struct No* esquerda;
    struct No* direita;
} No;

// declaração das funções
No *criarArvore();
void inserirNoArvore(No*, int, int, int);
No* buscarPorId(No*, int);
void removerNoArvore(No**, int);
void listarOrdemDecrescente(No*);
void atualizaInteracoes(No*, int, char*, char*);

No *criarArvore() { // criar árvore vazia
    No* raiz = malloc(sizeof(No));

    if (raiz != NULL) { // Significa que a alocação foi bem sucedida
        raiz->id = 0; 
        raiz->numCurtidas = 0;
        raiz->numComentarios = 0; 
        raiz->esquerda = raiz->direita = NULL; // inicialmente a raiz não tem filhos nem a direita e nem a esquerda  
    }
    return raiz;
}

void inserirNoArvore(No* raiz, int id, int numCurtidas, int numComentarios) {

    if (raiz->id == 0) { // caso a arvore esteja vazia, este nó será a raiz
        raiz->id = id;
        raiz->numCurtidas = numCurtidas;
        raiz->numComentarios = numComentarios;
    }
    else {
        if ((numCurtidas + numComentarios) < (raiz->numCurtidas + raiz->numComentarios)) { // organiza os nós (direita ou esquerda) conforme o número de interações

            if (raiz->esquerda != NULL) {
                inserirNoArvore(raiz->esquerda, id, numCurtidas, numComentarios); // chamada recursiva
            } else {
                raiz->esquerda = malloc(sizeof(No));
                raiz->esquerda->id = id;
                raiz->esquerda->numCurtidas = numCurtidas;
                raiz->esquerda->numComentarios = numComentarios;
                raiz->esquerda->esquerda = raiz->esquerda->direita = NULL;
            }
        } else {
            if (raiz->direita != NULL) {
                inserirNoArvore(raiz->direita, id, numCurtidas, numComentarios); // chamada recursiva
            } else {
                raiz->direita = malloc(sizeof(No));
                raiz->direita->id = id;
                raiz->direita->numCurtidas = numCurtidas;
                raiz->direita->numComentarios = numComentarios;
                raiz->direita->esquerda = raiz->direita->direita = NULL; // quando o nó for um nó folha
            }
        }
    }
}


// Função para remover um nó da árvore de busca binária
void removerNoArvore(No** raiz, int id) {
    if (*raiz == NULL) {
        printf("A árvore está vazia.\n");
        return;
    }

    // Passo 1: Buscar o nó com o id do usuário para obter o número de interações
    No* noParaRemover = buscarPorId(*raiz, id);
    if (noParaRemover == NULL) {
        printf("Usuário com id %d não encontrado.\n", id);
        return;
    }

    // Obtém o número de interações do nó encontrado
    int interacoes = noParaRemover->numCurtidas + noParaRemover->numComentarios;

    // Função interna para remover o nó pela quantidade de interações
    No* removerPorInteracoes(No* raiz, int interacoes) {
        if (raiz == NULL) 
            return NULL;

        if (interacoes < raiz->numCurtidas + raiz->numComentarios) {
            // Procura na subárvore à esquerda
            raiz->esquerda = removerPorInteracoes(raiz->esquerda, interacoes);
        } else if (interacoes > raiz->numCurtidas + raiz->numComentarios) {
            // Procura na subárvore à direita
            raiz->direita = removerPorInteracoes(raiz->direita, interacoes);
        } else {
            // Nó encontrado - aplicar lógica de remoção
            if (raiz->esquerda == NULL) {
                No* temp = raiz->direita;
                free(raiz);
                return temp;
            } else if (raiz->direita == NULL) {
                No* temp = raiz->esquerda;
                free(raiz);
                return temp;
            }

            // Caso com dois filhos: encontrar o sucessor (menor valor na subárvore direita)
            No* temp = raiz->direita;
            while (temp->esquerda != NULL) {
                temp = temp->esquerda;
            }

            // Substituir dados do nó com os dados do sucessor
            raiz->id = temp->id;
            raiz->numCurtidas = temp->numCurtidas;
            raiz->numComentarios = temp->numComentarios;

            // Remover o sucessor da subárvore direita
            raiz->direita = removerPorInteracoes(raiz->direita, temp->numCurtidas + temp->numComentarios);
        }
        return raiz;
    }

    // Passo 2: Chama a função interna para remover o nó com o número de interações correspondente
    *raiz = removerPorInteracoes(*raiz, interacoes);

    printf("\nUsuario com id %d removido\n\n", id);
}


// Função para listar os nós em ordem decrescente
void listarOrdemDecrescente(No* raiz) {
    if (raiz != NULL) {
        listarOrdemDecrescente(raiz->direita);
        printf("id: %d  interacoes: %d  curtidas: %d  comentarios: %d\n", raiz->id, (raiz->numCurtidas + raiz->numComentarios), raiz->numCurtidas, raiz->numComentarios);
        listarOrdemDecrescente(raiz->esquerda);
    }
}

//Função para encontrar um nó com um id específico
No* buscarPorId(No* raiz, int id) {
    if (raiz == NULL)
        return NULL;  // Se a raiz for NULL, retorna NULL (não encontrado)

    if (raiz->id == id)
        return raiz;  // Se o nó atual tem o id procurado, retorna o nó

    // Busca recursiva na subárvore à esquerda
    No* resultadoEsquerda = buscarPorId(raiz->esquerda, id);
    if (resultadoEsquerda != NULL)
        return resultadoEsquerda;  // Se encontrou na esquerda, retorna o resultado

    // Busca recursiva na subárvore à direita
    return buscarPorId(raiz->direita, id);  // Se não encontrou na esquerda, busca na direita
}

// Atualiza o número de curtidas ou comentários de um certo usuário
void atualizaInteracoes(No* raiz, int id, char* atualizaCurtidas, char* atualizaComentarios) {
    No* n = buscarPorId(raiz, id); // busca o nó que possui o respectivo id

    if (n == NULL) {
        printf("\nUsuario nao encontrado\n\n");
        return;
    }

    switch (atualizaCurtidas[0]) {  // operação "+/-value"
        case '+':
            n->numCurtidas += atoi(&atualizaCurtidas[1]); // converte a string num valor numérico, do 1 caractere em diante, o caractere 0 é a operação
            break;
        case '-':
            n->numCurtidas -= atoi(&atualizaCurtidas[1]);
            break;
        case ' ': // quando não se deseja alterar o valor é só passar um espaço que não será feito nada
            break;
        default:
            printf("\nOperacao falhou\n");
            break;
    }

    switch (atualizaComentarios[0]) {
        case '+':
            n->numComentarios += atoi(&atualizaComentarios[1]);
            break;
        case '-':
            n->numComentarios -= atoi(&atualizaComentarios[1]);
            break;
        case ' ':
            break;
        default:
            printf("\nOperacao falhou\n");
            break;
    }

    printf("\nInteracoes do usuario %d foram atualizadas\n\n", n->id);
}


int main() {
    No *raiz = criarArvore();
        
    inserirNoArvore(raiz, 100, 22, 45);
    inserirNoArvore(raiz, 101, 45, 9);
    inserirNoArvore(raiz, 102, 10, 1);
    inserirNoArvore(raiz, 103, 30, 5);
    inserirNoArvore(raiz, 104, 70, 5);
    inserirNoArvore(raiz, 105, 100, 5);
    inserirNoArvore(raiz, 106, 90, 5);
    inserirNoArvore(raiz, 107, 20, 5);

    listarOrdemDecrescente(raiz);

    No *n = buscarPorId(raiz, 107); // busca por um usuário

    if (n == NULL) {
        printf("\nUsuario nao encontrado\n");
    }
    else {
        printf("\n\nid: %d  interacoes: %d  curtidas: %d  comentarios: %d\n", n->id, (n->numCurtidas + n->numComentarios), n->numCurtidas, n->numComentarios);
    }

    removerNoArvore(&raiz, 101);

    listarOrdemDecrescente(raiz);

    atualizaInteracoes(raiz, 104, " ", "+10");

    listarOrdemDecrescente(raiz);

    return 0;
}
