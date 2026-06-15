#include <stdio.h>
#include <stdbool.h>
#include "banqueiro.h"

// Inicializa o sistema com um cenário clássico de teste (Mocado para facilitar o relatório)
void inicializar_sistema(EstadoSistema *estado) {
    estado->num_processos = 5;
    estado->num_recursos = 3;

    // Recursos atualmente disponíveis na instância do SO [A, B, C]
    estado->disponivel[0] = 3; estado->disponivel[1] = 3; estado->disponivel[2] = 2;

    // Matriz de Alocação Atual (O que cada processo já tem)
    int aloc[5][3] = {
        {0, 1, 0},  // P0
        {2, 0, 0},  // P1
        {3, 0, 2},  // P2
        {2, 1, 1},  // P3
        {0, 0, 2}   // P4
    };

    // Matriz Máxima (O máximo que cada um vai precisar para terminar)
    int maximo[5][3] = {
        {7, 5, 3},  // P0
        {3, 2, 2},  // P1
        {9, 0, 2},  // P2
        {2, 2, 2},  // P3
        {4, 3, 3}   // P4
    };

    // Copia os dados para a estrutura e calcula a Matriz de Necessidade (Max - Alocacao)
    for (int i = 0; i < estado->num_processos; i++) {
        for (int j = 0; j < estado->num_recursos; j++) {
            estado->alocacao[i][j] = aloc[i][j];
            estado->max[i][j] = maximo[i][j];
            estado->necessidade[i][j] = maximo[i][j] - aloc[i][j];
        }
    }
}

// O cerne do algoritmo: Verifica se o estado atual é seguro e acha a sequência
int verificar_estado_seguro(EstadoSistema *estado, int *sequencia_segura) {
    int trabalho[MAX_RECURSOS];
    bool terminou[MAX_PROCESSOS] = {false};
    int p_count = 0;

    // trabalho = disponível
    for (int i = 0; i < estado->num_recursos; i++) {
        trabalho[i] = estado->disponivel[i];
    }

    // Tenta encontrar uma ordem de execução vazia de deadlocks
    while (p_count < estado->num_processos) {
        bool encontrou_processo_viavel = false;

        for (int p = 0; p < estado->num_processos; p++) {
            if (!terminou[p]) {
                // Verifica se a necessidade atual do processo p cabe no vetor trabalho
                bool pode_executar = true;
                for (int r = 0; r < estado->num_recursos; r++) {
                    if (estado->necessidade[p][r] > trabalho[r]) {
                        pode_executar = false;
                        break;
                    }
                }

                // Se puder executar, o processo "termina" e devolve seus recursos acumulados
                if (pode_executar) {
                    for (int r = 0; r < estado->num_recursos; r++) {
                        trabalho[r] += estado->alocacao[p][r];
                    }
                    sequencia_segura[p_count++] = p;
                    terminou[p] = true;
                    encontrou_processo_viavel = true;
                }
            }
        }

        // Se passou por todos e nenhum pôde executar, estamos em um estado Inseguro (Deadlock)
        if (!encontrou_processo_viavel) {
            return 0; // Inseguro
        }
    }

    return 1; // Seguro
}

// Processa uma requisição de recursos feita por um processo específico
int requisitar_recursos(EstadoSistema *estado, int processo_id, int *requisicao) {
    // 1. Validação: A requisição não pode ser maior do que o processo disse que precisaria
    for (int r = 0; r < estado->num_recursos; r++) {
        if (requisicao[r] > estado->necessidade[processo_id][r]) {
            printf("[ERRO] Processo excedeu sua necessidade maxima declarada!\n");
            return -1;
        }
    }

    // 2. Validação: Se não houver recursos suficientes agora, o processo deve esperar
    for (int r = 0; r < estado->num_recursos; r++) {
        if (requisicao[r] > estado->disponivel[r]) {
            printf("[NEGADO] Recursos indisponiveis no momento. O processo P%d deve esperar.\n", processo_id);
            return 0;
        }
    }

    // 3. Simulação: Finge que concede os recursos alterando o estado temporariamente
    for (int r = 0; r < estado->num_recursos; r++) {
        estado->disponivel[r] -= requisicao[r];
        estado->alocacao[processo_id][r] += requisicao[r];
        estado->necessidade[processo_id][r] -= requisicao[r];
    }

    // 4. Avaliação de Segurança
    int sequencia_segura[MAX_PROCESSOS];
    if (verificar_estado_seguro(estado, sequencia_segura)) {
        printf("[CONCEDIDO] O estado continua SEGURO. Recursos alocados para P%d.\n", processo_id);
        printf("Sequencia segura de execucao: ");
        for (int i = 0; i < estado->num_processos; i++) {
            printf("P%d ", sequencia_segura[i]);
        }
        printf("\n");
        return 1; // Sucesso
    } else {
        printf("[NEGADO] Conceder esses recursos deixaria o estado INSEGURO (Risco de Deadlock). Desfazendo alteracao...\n");
        // Desfaz a simulação (Rollback)
        for (int r = 0; r < estado->num_recursos; r++) {
            estado->disponivel[r] += requisicao[r];
            estado->alocacao[processo_id][r] -= requisicao[r];
            estado->necessidade[processo_id][r] += requisicao[r];
        }
        return 0; // Falha por insegurança
    }
}