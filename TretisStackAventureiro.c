/*******************************************************
 * Desafio Tetris Stack - Controle de Peças com Estruturas de Dados NÍVEL AVENTUREIRO
 * Aluno: Aderlon Barbosa Pessoa
 * Matéria: Estrutura de Dados
 *
 * Descrição:
 * Expansão do sistema Novato. Adiciona pilha de reserva
 * de peças para guardar e usar posteriormente.
 *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ===== Definição da struct Peça =====
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

// ===== Definição da fila circular (5 peças) =====
#define TAM_FILA 5
typedef struct {
    Peca fila[TAM_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

// ===== Definição da pilha de reserva (3 peças) =====
#define TAM_PILHA 3
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo; // Índice do topo
} Pilha;

// ===== Função que gera uma nova peça aleatória =====
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I','O','T','L'};
    int indice = rand() % 4;
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

// ===== Inicializa a pilha =====
void inicializarPilha(Pilha *p) {
    p->topo = -1; // Pilha vazia
}

// ===== Mostra a fila =====
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

// ===== Mostra a pilha =====
void mostrarPilha(Pilha p) {
    printf("\nPilha de reserva:\n");
    if(p.topo == -1) {
        printf("Pilha vazia!\n");
        return;
    }
    for(int i = p.topo; i >= 0; i--) {
        printf("Pos %d: Peça %c | ID %d\n", i+1, p.pilha[i].nome, p.pilha[i].id);
    }
}

// ===== Remove a peça da frente da fila (jogar) =====
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

// ===== Insere nova peça no final da fila =====
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

// ===== Push: reserva a peça da frente na pilha =====
void reservarPeca(Fila *f, Pilha *p) {
    if(p->topo == TAM_PILHA - 1) {
        printf("Pilha cheia! Não pode reservar mais peças.\n");
        return;
    }
    if(f->qtd == 0) {
        printf("Fila vazia! Não há peça para reservar.\n");
        return;
    }
    p->topo++;
    p->pilha[p->topo] = f->fila[f->frente];
    printf("Peça reservada: %c | ID %d\n", f->fila[f->frente].nome, f->fila[f->frente].id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
}

// ===== Pop: usar a peça reservada =====
void usarPecaReservada(Pilha *p) {
    if(p->topo == -1) {
        printf("Pilha vazia! Não há peça para usar.\n");
        return;
    }
    Peca peca = p->pilha[p->topo];
    printf("Você usou a peça reservada: %c | ID %d\n", peca.nome, peca.id);
    p->topo--;
}

// ===== Função principal =====
int main() {
    Fila fila;
    Pilha pilha;
    int idAtual = TAM_FILA + 1;
    int opcao;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    printf("=== Bem-vindo ao Tetris Stack - Nível Aventureiro ===\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                jogarPeca(&fila);
                inserirPeca(&fila, idAtual);
                idAtual++;
                break;
            case 2:
                reservarPeca(&fila, &pilha);
                inserirPeca(&fila, idAtual);
                idAtual++;
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 0:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        // Mostrar fila e pilha após cada ação
        mostrarFila(fila);
        mostrarPilha(pilha);

    } while(opcao != 0);

    return 0;
}

