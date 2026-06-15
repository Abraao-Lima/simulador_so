#ifndef BANQUEIRO_H
#define BANQUEIRO_H

#define MAX_PROCESSOS 5
#define MAX_RECURSOS 3

// Estrutura profissional para encapsular o estado do sistema
typedef struct {
    int alocacao[MAX_PROCESSOS][MAX_RECURSOS];
    int max[MAX_PROCESSOS][MAX_RECURSOS];
    int necessidade[MAX_PROCESSOS][MAX_RECURSOS];
    int disponivel[MAX_RECURSOS];
    int num_processos;
    int num_recursos;
} EstadoSistema;

// Declaração das funções do módulo
void inicializar_sistema(EstadoSistema *estado);
int verificar_estado_seguro(EstadoSistema *estado, int *sequencia_segura);
int requisitar_recursos(EstadoSistema *estado, int processo_id, int *requisicao);

#endif