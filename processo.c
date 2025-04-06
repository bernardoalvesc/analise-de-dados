#include "processo.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int carregar_processos(const char *nome_arquivo, Processo processos[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[512];
    int i = 0;

    fgets(linha, sizeof(linha), arquivo); // cabeçalho

    while (fgets(linha, sizeof(linha), arquivo) && i < MAX_PROCESSOS) {
        Processo p;
        char *token = strtok(linha, ";");
        int campo = 0;

        while (token) {
            switch (campo) {
                case 0: p.id = atoi(token); break;
                case 1: strcpy(p.numero, token); break;
                case 2: strcpy(p.data_ajuizamento, token); break;
                case 3: p.id_classe = atoi(token); break;
                case 4: {
                    p.qtd_assuntos = 0;
                    char *ptr = strtok(token, ",{}");
                    while (ptr) {
                        p.id_assunto[p.qtd_assuntos++] = atoi(ptr);
                        ptr = strtok(NULL, ",{}");
                    }
                    break;
                }
                case 5: p.ano_eleicao = atoi(token); break;
            }
            token = strtok(NULL, ";");
            campo++;
        }
        processos[i++] = p;
    }

    fclose(arquivo);
    return i;
}

void salvar_csv(Processo *processos, int qtd, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao salvar CSV.\n");
        return;
    }

    fprintf(arquivo, "id;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n");

    for (int i = 0; i < qtd; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;{", processos[i].id, processos[i].numero, processos[i].data_ajuizamento, processos[i].id_classe);
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            fprintf(arquivo, "%d", processos[i].id_assunto[j]);
            if (j < processos[i].qtd_assuntos - 1)
                fprintf(arquivo, ",");
        }
        fprintf(arquivo, "};%d\n", processos[i].ano_eleicao);
    }

    fclose(arquivo);
    printf("CSV salvo em %s\n", nome_arquivo);
}

int comparar_por_id(const void *a, const void *b) {
    Processo *pa = (Processo *)a;
    Processo *pb = (Processo *)b;
    return pa->id - pb->id;
}

void ordenar_por_id(Processo *processos, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (processos[i].id > processos[j].id) {
                Processo tmp = processos[i];
                processos[i] = processos[j];
                processos[j] = tmp;
            }
        }
    }
}

int comparar_datas(const char *d1, const char *d2) {
    struct tm tm1 = {0}, tm2 = {0};
    sscanf(d1, "%d-%d-%d %d:%d:%d",
           &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday,
           &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);
    sscanf(d2, "%d-%d-%d %d:%d:%d",
           &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday,
           &tm2.tm_hour, &tm2.tm_min, &tm2.tm_sec);
    tm1.tm_year -= 1900; tm1.tm_mon -= 1;
    tm2.tm_year -= 1900; tm2.tm_mon -= 1;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    return difftime(t1, t2);
}

void ordenar_por_data(Processo *processos, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (comparar_datas(processos[i].data_ajuizamento, processos[j].data_ajuizamento) > 0) {
                Processo tmp = processos[i];
                processos[i] = processos[j];
                processos[j] = tmp;
            }
        }
    }
}

void contar_por_id_classe(Processo *processos, int qtd) {
    int contagens[1000] = {0};
    for (int i = 0; i < qtd; i++) {
        contagens[processos[i].id_classe]++;
    }

    printf("Contagem de processos por id_classe:\n");
    for (int i = 0; i < 1000; i++) {
        if (contagens[i] > 0) {
            printf("Classe %d: %d processos\n", i, contagens[i]);
        }
    }
}

void contar_id_assuntos_distintos(Processo *processos, int qtd) {
    int assuntos[1000] = {0};
    for (int i = 0; i < qtd; i++) {
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            assuntos[processos[i].id_assunto[j]] = 1;
        }
    }

    int total = 0;
    for (int i = 0; i < 1000; i++) {
        if (assuntos[i]) total++;
    }
    printf("Total de assuntos distintos: %d\n", total);
}

void listar_multiplos_assuntos(Processo *processos, int qtd) {
    printf("Processos com mais de um assunto:\n");
    for (int i = 0; i < qtd; i++) {
        if (processos[i].qtd_assuntos > 1) {
            printf("ID: %d | Número: %s\n", processos[i].id, processos[i].numero);
        }
    }
}

void mostrar_dias_em_tramitacao(Processo *processos, int qtd) {
    time_t agora = time(NULL);

    printf("Dias em tramitação:\n");
    for (int i = 0; i < qtd; i++) {
        struct tm tm1 = {0};
        sscanf(processos[i].data_ajuizamento, "%d-%d-%d %d:%d:%d",
               &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday,
               &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);
        tm1.tm_year -= 1900; tm1.tm_mon -= 1;

        time_t ajuizado = mktime(&tm1);
        double dias = difftime(agora, ajuizado) / (60 * 60 * 24);

        printf("ID: %d | Dias: %.0f\n", processos[i].id, dias);
    }
}
