/*******************************************************
 * Desafio Tetris Stack - Controle de Peças com Estruturas de Dados NÍVEL NOVATO
 * Aluno: Aderlon Barbosa Pessoa
 * Matéria: Estrutura de Dados
 *
 * Descrição:
 * Controle de peças futuras do Tetris usando fila circular.
 * O programa permite visualizar a fila, jogar a peça da frente
 * e inserir uma nova peça automaticamente.
 * Foco: structs, arrays e modularização.
 *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ===== Definição da struct Peça =====
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

// ===== Definição da fila circular =====
#define TAM_FILA 5 // Tamanho fixo da fila

typedef struct {
    Peca fila[TAM_FILA]; // Array de peças
    int frente;          // Índice da frente da fila
    int tras;            // Índice do final da fila
    int qtd;             // Quantidade de elementos na fila
} Fila;

// ===== Função que gera uma nova peça aleatória =====
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I','O','T','L'};
    int indice = rand() % 4; // Escolhe tipo aleatório
    p.nome = tipos[indice];
    p.id = id;
    return p;
}

// ===== Inicializa a fila com 5 peças =====
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->qtd = 0;
    for(int i = 0; i < TAM_FILA; i++) {
        f->fila[f->tras] = gerarPeca(i+1);
        f->tras = (f->tras + 1) % TAM_FILA;
        f->qtd++;
    }
}

// ===== Mostra todas as peças da fila =====
void mostrarFila(Fila f) {
    printf("\nFila atual:\n");
    if(f.qtd == 0) {
        printf("Fila vazia!\n");
        return;
    }
    int i = f.frente;
    for(int c = 0; c < f.qtd; c++) {
        printf("Pos %d: Peça %c | ID %d\n", c+1, f.fila[i].nome, f.fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
}

// ===== Remove a peça da frente (jogar) =====
void jogarPeca(Fila *f) {
    if(f->qtd == 0) {
        printf("Fila vazia! Não tem peça para jogar.\n");
        return;
    }
    Peca p = f->fila[f->frente];
    printf("Você jogou a peça: %c | ID %d\n", p.nome, p.id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
}

// ===== Insere uma nova peça no final da fila =====
void inserirPeca(Fila *f, int id) {
    if(f->qtd == TAM_FILA) {
        printf("Fila cheia! Não pode inserir nova peça agora.\n");
        return;
    }
    f->fila[f->tras] = gerarPeca(id);
    printf("Nova peça inserida: %c | ID %d\n", f->fila[f->tras].nome, f->fila[f->tras].id);
    f->tras = (f->tras + 1) % TAM_FILA;
    f->qtd++;
}

// ===== Função principal =====
int main() {
    Fila fila;
    int idAtual = TAM_FILA + 1; // Próximo ID para nova peça
    int opcao;

    srand(time(NULL)); // Inicializa gerador de números aleatórios

    inicializarFila(&fila);

    printf("=== Bem-vindo ao Tetris Stack - Nível Novato ===\n");

    do {
        // Menu principal
        printf("\nMenu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Inserir nova peça\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, idAtual);
                idAtual++;
                break;
            case 3:
                mostrarFila(fila);
                break;
            case 0:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

