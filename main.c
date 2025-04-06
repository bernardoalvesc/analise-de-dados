#include <stdio.h>
#include "processo.h"

int main() {
    Processo processos[MAX_PROCESSOS];
    int qtd_processos = carregar_processos("processo_043_202409032338 (3).csv", processos);

    if (qtd_processos == 0) {
        printf("Falha ao carregar processos ou arquivo vazio.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Ordenar por ID e salvar em CSV\n");
        printf("2. Ordenar por Data e salvar em CSV\n");
        printf("3. Contar processos por id_classe\n");
        printf("4. Contar id_assunto distintos\n");
        printf("5. Listar processos com múltiplos id_assunto\n");
        printf("6. Mostrar tempo médio de tramitação\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                ordenar_por_id(processos, qtd_processos);
                salvar_csv(processos, qtd_processos, "saida_ordenada_por_id.csv");
                printf("Arquivo salvo como 'saida_ordenada_por_id.csv'.\n");
                break;
            case 2:
                ordenar_por_data(processos, qtd_processos);
                salvar_csv(processos, qtd_processos, "saida_ordenada_por_data.csv");
                printf("Arquivo salvo como 'saida_ordenada_por_data.csv'.\n");
                break;
            case 3:
                contar_por_id_classe(processos, qtd_processos);
                break;
            case 4:
                contar_id_assuntos_distintos(processos, qtd_processos);
                break;
            case 5:
                listar_multiplos_assuntos(processos, qtd_processos);
                break;
            case 6:
                mostrar_dias_em_tramitacao(processos, qtd_processos);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(opcao != 0);

    return 0;
}
