# Simulador Didatico de Sistemas Operacionais

Este projeto consiste em um sistema modular integrado, desenvolvido em Linguagem C, para a simulação, análise e demonstração prática de algoritmos fundamentais de Sistemas Operacionais. O software aborda dois escopos principais exigidos na atividade acadêmica: o gerenciamento de Memória Virtual através de algoritmos de substituição de páginas e a prevenção de condições de Deadlock por meio do Algoritmo do Banqueiro.

O programa foi projetado para execução direta via terminal (Interface de Linha de Comando - CLI), operando de forma interativa para apresentar os resultados, fluxos de execução e transições de estado das estruturas de dados síncronas.

---

## Funcionalidades Implementadas

### 1. Modulo de Gerenciamento de Memoria Virtual (Tema 01)

- Algoritmo FIFO (First-In, First-Out): Substituição de páginas baseada na ordem cronológica de inserção no vetor de quadros da memória RAM.
- Algoritmo LRU (Least Recently Used): Substituição baseada no mapeamento temporal do último acesso a cada página.
- Mapeamento Comparativo: O programa submete os dois algoritmos a mesma string de referência (composta por 12 elementos) e exibe um relatório comparativo, lado a lado, com o total de faltas de página (page faults) geradas sob a quantidade fixa de 3 quadros estabelecida no código.

### 2. Modulo de Prevencao de Deadlocks (Tema 02)

- Algoritmo do Banqueiro: Validação das condições de segurança do sistema avaliando de forma síncrona matrizes de Alocação Atual, Necessidade Máxima e o Vetor de Recursos Disponíveis.
- Verificação de Estado Seguro: Analisa as estruturas e determina se a configuração inicial é estável, imprimindo de forma síncrona a sequência segura de execução dos processos quando disponível.
- Análise de Requisições Interativas: Permite que o usuário insira o ID de um processo e realize uma solicitação de novos recursos, concedendo ou negando o pedido com base no impacto de segurança gerado no sistema.

---

## Estrutura do Diretorio do Projeto

```text
SIMULADOR_SO/
├── .vscode/               # Scripts de automacao do editor (tasks, launch e propriedades)
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── tasks.json
├── build/                 # Arquivos binarios de objeto intermediarios (.o)
│   ├── banqueiro.o
│   ├── main.o
│   └── memoria.o
├── include/               # Arquivos de cabecalho e assinaturas de funcoes (.h)
│   ├── banqueiro.h
│   └── memoria.h
├── src/                   # Codigos-fonte de implementacao (.c)
│   ├── banqueiro.c
│   ├── main.c
│   └── memoria.c
├── Makefile               # Script de automacao do processo de compilacao modular
└── README.md              # Documentacao principal do repositorio
```

## Requisitos do Ambiente e Compilacao

Para a correta compilação, linkedição dos módulos e execução, certifique-se de possuir em seu ambiente:

### Compilador GCC (GNU Compiler Collection).

### Utilitário GNU Make (ou MinGW32-Make para ambientes Windows configurados via MSYS2).

## Instrucoes de Compilacao

Para efetuar a compilação modular do projeto e gerar o binário executável na raiz, abra o terminal no diretório do projeto e utilize o utilitário adequado ao seu sistema:

## Ambientes Linux / macOS:

```Bash
make
```

## Ambientes Windows (MinGW/MSYS2)

```Bash
mingw32-make
```

## Executando o Simulador

Após o sucesso do processo de compilação, inicie o programa binário gerado na raiz por meio do comando correspondente ao seu ambiente de execução:

## No Linux / macOS:

```Bash
./simulador
```

## No Windows (PowerShell / Prompt de Comando):

```DOS
.\simulador.exe
```

# Identificacao dos Desenvolvedores

Abraão Sousa Lima - 2024009284

Aristides Maia Neto - 2024006747

Adriana de Sousa Viana - 2024006540

João Lucas Viana Almeida - 2024009622

# Informacoes Academicas

Disciplina: Sistemas Operacionais

Contexto: Simuladores Didáticos de Sistemas Operacionais

Repositório Oficial: https://github.com/Abraao-Lima/simulador_so
