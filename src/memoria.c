#include <stdio.h>
#include <stdbool.h>
#include "memoria.h"

int simular_fifo(int *paginas, int num_paginas, int num_quadros) {
    int quadros[num_quadros];
    int faltas_pagina = 0;
    int indice_substituicao = 0;

    // Inicializa todos os quadros da RAM como vazios (-1)
    for (int i = 0; i < num_quadros; i++) {
        quadros[i] = -1;
    }

    printf("\n--- SIMULACAO FIFO ---\n");

    // Percorre cada página requisitada pelo sistema
    for (int i = 0; i < num_paginas; i++) {
        int pagina_atual = paginas[i];
        bool encontrada = false;

        // Verifica se a página já está em algum quadro da RAM
        for (int j = 0; j < num_quadros; j++) {
            if (quadros[j] == pagina_atual) {
                encontrada = true;
                break;
            }
        }

        // Se NÃO encontrou, ocorreu um Page Fault (Falta de Página)
        if (!encontrada) {
            quadros[indice_substituicao] = pagina_atual;
            // Move o índice para o próximo elemento (Fila Circular)
            indice_substituicao = (indice_substituicao + 1) % num_quadros;
            faltas_pagina++;
            
            printf("Pagina %d -> [FALTA DE PAGINA] Estado da RAM: ", pagina_atual);
        } else {
            printf("Pagina %d -> [HIT - JA NA RAM]  Estado da RAM: ", pagina_atual);
        }

        // Exibe o estado atual da memória para o usuário ver o passo a passo
        for (int j = 0; j < num_quadros; j++) {
            if (quadros[j] == -1) printf("[ ] ");
            else printf("[%d] ", quadros[j]);
        }
        printf("\n");
    }

    return faltas_pagina;
}
int simular_lru(int *paginas, int num_paginas, int num_quadros) {
    int quadros[num_quadros];
    int tempos[num_quadros]; // Rastreia quando cada página foi usada pela última vez
    int faltas_pagina = 0;

    // Inicializa a RAM e o rastreador de tempo
    for (int i = 0; i < num_quadros; i++) {
        quadros[i] = -1;
        tempos[i] = 0;
    }

    printf("\n--- SIMULACAO LRU ---\n");

    for (int i = 0; i < num_paginas; i++) {
        int pagina_atual = paginas[i];
        bool encontrada = false;

        // Verifica se a página já está na RAM (HIT)
        for (int j = 0; j < num_quadros; j++) {
            if (quadros[j] == pagina_atual) {
                encontrada = true;
                tempos[j] = i; // Atualiza o "tempo" de uso recente desta página
                break;
            }
        }

        // Se NÃO encontrou (Page Fault)
        if (!encontrada) {
            int indice_substituicao = 0;

            // Procura por um quadro vazio primeiro
            bool espaco_livre = false;
            for (int j = 0; j < num_quadros; j++) {
                if (quadros[j] == -1) {
                    indice_substituicao = j;
                    espaco_livre = true;
                    break;
                }
            }

            // Se a memória estiver cheia, escolhe a página que ficou mais tempo sem ser usada
            if (!espaco_livre) {
                int menor_tempo = tempos[0];
                for (int j = 1; j < num_quadros; j++) {
                    if (tempos[j] < menor_tempo) {
                        menor_tempo = tempos[j];
                        indice_substituicao = j;
                    }
                }
            }

            // Substitui a página e atualiza o tempo
            quadros[indice_substituicao] = pagina_atual;
            tempos[indice_substituicao] = i;
            faltas_pagina++;

            printf("Pagina %d -> [FALTA DE PAGINA] Estado da RAM: ", pagina_atual);
        } else {
            printf("Pagina %d -> [HIT - JA NA RAM]  Estado da RAM: ", pagina_atual);
        }

        // Exibe o mapa visual da memória
        for (int j = 0; j < num_quadros; j++) {
            if (quadros[j] == -1) printf("[ ] ");
            else printf("[%d] ", quadros[j]);
        }
        printf("\n");
    }

    return faltas_pagina;
}