#ifndef PROCESSOS_H
#define PROCESSOS_H

#define MAX_PROCESSOS 1000
#define MAX_ASSUNTOS 10

typedef struct {
    int id;
    char numero[64];
    char data_ajuizamento[32];
    int id_classe;
    int id_assunto[MAX_ASSUNTOS];
    int num_assuntos;
    int ano_eleicao;
} Processo;

int ler_processos(const char *nome_arquivo, Processo processos[]);
void ordenar_por_id(Processo v[], int n);
void ordenar_por_data(Processo v[], int n);
void salvar_csv(const char *nome_arquivo, Processo v[], int n);
int contar_por_classe(Processo v[], int n, int id_classe);
int contar_assuntos_unicos(Processo v[], int n);
void listar_multiplos_assuntos(Processo v[], int n);
int dias_em_tramitacao(const char *data);
void mostrar_dias_em_tramitacao(Processo v[], int n);

#endif
