#include <stdio.h>
#include "memoria.h"
#include "banqueiro.h"

void gerenciar_modulo_memoria() {
    int sequencia_paginas[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_paginas = sizeof(sequencia_paginas) / sizeof(sequencia_paginas[0]);
    int num_quadros = 3;

    int total_faltas_fifo = simular_fifo(sequencia_paginas, num_paginas, num_quadros);
    int total_faltas_lru = simular_lru(sequencia_paginas, num_paginas, num_quadros);

    printf("\n=========================================\n");
    printf("       RESULTADO FINAL COMPARATIVO       \n");
    printf("=========================================\n");
    printf(" Algoritmo | Total de Faltas de Pagina\n");
    printf("-----------|-----------------------------\n");
    printf("   FIFO    | %d\n", total_faltas_fifo);
    printf("   LRU     | %d\n", total_faltas_lru);
    printf("=========================================\n");
}

void gerenciar_modulo_banqueiro() {
    EstadoSistema sistema;
    inicializar_sistema(&sistema);

    int opcao;
    printf("\n--- SIMULADOR ALGORITMO DO BANQUEIRO ---\n");
    printf("1. Verificar se o estado inicial e seguro\n");
    printf("2. Fazer uma requisicao de recursos\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) return;

    if (opcao == 1) {
        int seq[MAX_PROCESSOS];
        if (verificar_estado_seguro(&sistema, seq)) {
            printf("\n[RESULTADO] O estado inicial e SEGURO!\nSequencia segura: ");
            for(int i = 0; i < sistema.num_processos; i++) printf("P%d ", seq[i]);
            printf("\n");
        } else {
            printf("\n[ALERTA] O estado inicial ja esta INSEGURO!\n");
        }
    } 
    else if (opcao == 2) {
        int pid;
        int req[MAX_RECURSOS];
        printf("\nDigite o ID do processo requisitante (0 a %d): ", sistema.num_processos - 1);
        if (scanf("%d", &pid) != 1) return;
        
        printf("Digite a quantidade requisitada para cada um dos %d recursos (separados por espaco): ", sistema.num_recursos);
        for(int i = 0; i < sistema.num_recursos; i++) {
            if (scanf("%d", &req[i]) != 1) return;
        }

        requisitar_recursos(&sistema, pid, req);
    }
}

int main() {
    int escolha;

    printf("=============================================\n");
    printf("  SIMULADOR DIDATICO DE SISTEMAS OPERACIONAIS \n");
    printf("=============================================\n");
    printf("1. Modulo 1: Substituicao de Paginas (Memoria)\n");
    printf("2. Modulo 2: Algoritmo do Banqueiro (Deadlocks)\n");
    printf("Escolha qual simulador deseja rodar: ");
    
    if (scanf("%d", &escolha) != 1) return 1;

    switch(escolha) {
        case 1:
            gerenciar_modulo_memoria();
            break;
        case 2:
            gerenciar_modulo_banqueiro();
            break;
        default:
            printf("Opcao invalida. Encerrando programa.\n");
    }

    return 0;
}