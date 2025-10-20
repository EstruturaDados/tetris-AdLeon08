/*******************************************************
 * Desafio Tetris Stack - Controle de Peças com Estruturas de Dados NÍVEL MESTRE
 * Aluno: Aderlon Barbosa Pessoa
 * Matéria: Estrutura de Dados
 *
 * Descrição:
 * Integração avançada entre fila circular e pilha de reserva.
 * Permite trocar, desfazer e inverter peças, simulando
 * estratégias complexas de Tetris.
 *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ===== Definição da struct Peça =====
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

// ===== Fila circular (5 peças) =====
#define TAM_FILA 5
typedef struct {
    Peca fila[TAM_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

// ===== Pilha de reserva (3 peças) =====
#define TAM_PILHA 3
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;

// ===== Histórico para desfazer última jogada =====
typedef struct {
    Peca ultimaJogada;
    int jogadaFeita; // 0 = não, 1 = sim
} Historico;

// ===== Função que gera uma nova peça aleatória =====
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I','O','T','L'};
    int indice = rand() % 4;
    p.nome = tipos[indice];
    p.id = id;
    return p;
}

// ===== Inicialização =====
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

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

void inicializarHistorico(Historico *h) {
    h->jogadaFeita = 0;
}

// ===== Mostrar fila e pilha =====
void mostrarFila(Fila f) {
    printf("\nFila atual:\n");
    if(f.qtd == 0) { printf("Fila vazia!\n"); return; }
    int i = f.frente;
    for(int c = 0; c < f.qtd; c++) {
        printf("Pos %d: Peça %c | ID %d\n", c+1, f.fila[i].nome, f.fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
}

void mostrarPilha(Pilha p) {
    printf("\nPilha de reserva:\n");
    if(p.topo == -1) { printf("Pilha vazia!\n"); return; }
    for(int i = p.topo; i >= 0; i--) {
        printf("Pos %d: Peça %c | ID %d\n", i+1, p.pilha[i].nome, p.pilha[i].id);
    }
}

// ===== Jogar peça =====
void jogarPeca(Fila *f, Historico *h) {
    if(f->qtd == 0) { printf("Fila vazia!\n"); return; }
    Peca p = f->fila[f->frente];
    printf("Você jogou a peça: %c | ID %d\n", p.nome, p.id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    h->ultimaJogada = p;
    h->jogadaFeita = 1;
}

// ===== Inserir peça automática =====
void inserirPeca(Fila *f, int id) {
    if(f->qtd == TAM_FILA) { printf("Fila cheia!\n"); return; }
    f->fila[f->tras] = gerarPeca(id);
    f->tras = (f->tras + 1) % TAM_FILA;
    f->qtd++;
}

// ===== Reservar peça (push) =====
void reservarPeca(Fila *f, Pilha *p) {
    if(p->topo == TAM_PILHA - 1) { printf("Pilha cheia!\n"); return; }
    if(f->qtd == 0) { printf("Fila vazia!\n"); return; }
    p->topo++;
    p->pilha[p->topo] = f->fila[f->frente];
    printf("Peça reservada: %c | ID %d\n", f->fila[f->frente].nome, f->fila[f->frente].id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
}

// ===== Usar peça reservada (pop) =====
void usarPecaReservada(Pilha *p) {
    if(p->topo == -1) { printf("Pilha vazia!\n"); return; }
    Peca peca = p->pilha[p->topo];
    printf("Você usou a peça reservada: %c | ID %d\n", peca.nome, peca.id);
    p->topo--;
}

// ===== Trocar peça do topo da pilha com a frente da fila =====
void trocarTopoFila(Fila *f, Pilha *p) {
    if(f->qtd == 0 || p->topo == -1) { printf("Não é possível trocar!\n"); return; }
    Peca temp = f->fila[f->frente];
    f->fila[f->frente] = p->pilha[p->topo];
    p->pilha[p->topo] = temp;
    printf("Peça do topo da pilha trocada com a frente da fila.\n");
}

// ===== Desfazer última jogada =====
void desfazerJogada(Fila *f, Historico *h) {
    if(h->jogadaFeita == 0) { printf("Nenhuma jogada para desfazer!\n"); return; }
    f->frente = (f->frente - 1 + TAM_FILA) % TAM_FILA;
    f->fila[f->frente] = h->ultimaJogada;
    f->qtd++;
    printf("Última jogada desfeita: %c | ID %d\n", h->ultimaJogada.nome, h->ultimaJogada.id);
    h->jogadaFeita = 0;
}

// ===== Inverter fila com pilha =====
void inverterFilaPilha(Fila *f, Pilha *p) {
    int i, j;
    // Inverte fila
    for(i = 0; i < f->qtd/2; i++) {
        int idx1 = (f->frente + i) % TAM_FILA;
        int idx2 = (f->frente + f->qtd - 1 - i) % TAM_FILA;
        Peca temp = f->fila[idx1];
        f->fila[idx1] = f->fila[idx2];
        f->fila[idx2] = temp;
    }
    // Inverte pilha
    for(i = 0, j = p->topo; i < j; i++, j--) {
        Peca temp = p->pilha[i];
        p->pilha[i] = p->pilha[j];
        p->pilha[j] = temp;
    }
    printf("Fila e pilha invertidas.\n");
}

// ===== Função principal =====
int main() {
    Fila fila;
    Pilha pilha;
    Historico hist;
    int idAtual = TAM_FILA + 1;
    int opcao;

    srand(time(NULL));
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    inicializarHistorico(&hist);

    printf("=== Bem-vindo ao Tetris Stack - Nível Mestre ===\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar topo da pilha com frente da fila\n");
        printf("5 - Desfazer última jogada\n");
        printf("6 - Inverter fila com pilha\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                jogarPeca(&fila, &hist);
                inserirPeca(&fila, idAtual++);
                break;
            case 2:
                reservarPeca(&fila, &pilha);
                inserirPeca(&fila, idAtual++);
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 4:
                trocarTopoFila(&fila, &pilha);
                break;
            case 5:
                desfazerJogada(&fila, &hist);
                break;
            case 6:
                inverterFilaPilha(&fila, &pilha);
                break;
            case 0:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

        // Mostrar estado após cada ação
        mostrarFila(fila);
        mostrarPilha(pilha);

    } while(opcao != 0);

    return 0;
}

