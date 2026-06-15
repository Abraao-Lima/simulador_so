#ifndef MEMORIA_H
#define MEMORIA_H

// Função que simula o algoritmo FIFO (First-In, First-Out)
// Recebe: vetor de páginas, tamanho do vetor e a quantidade de quadros na RAM
int simular_fifo(int *paginas, int num_paginas, int num_quadros);

// Função que simula o algoritmo LRU (Least Recently Used)
int simular_lru(int *paginas, int num_paginas, int num_quadros);

#endif