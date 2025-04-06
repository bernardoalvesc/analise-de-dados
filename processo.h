#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>

#define MAX_PROCESSOS 1000 // <-- Adicione essa linha

typedef struct {
    int id;
    char numero[30];
    char data_ajuizamento[25];
    int id_classe;
    int id_assunto[10];
    int qtd_assuntos;
    int ano_eleicao;
} Processo;

int carregar_processos(const char *nome_arquivo, Processo processos[]);
void salvar_csv(Processo *processos, int qtd, const char *nome_arquivo);
void ordenar_por_id(Processo *processos, int qtd);
void ordenar_por_data(Processo *processos, int qtd);
void contar_por_id_classe(Processo *processos, int qtd);
void contar_id_assuntos_distintos(Processo *processos, int qtd);
void listar_multiplos_assuntos(Processo *processos, int qtd);
void mostrar_dias_em_tramitacao(Processo *processos, int qtd);

#endif
