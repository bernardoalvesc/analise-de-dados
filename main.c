#include <stdio.h>
#include <stdlib.h>
#include "processos.h"

int main() {
    Processo processos[MAX_PROCESSOS];
    int qtd_processos = ler_processos("dados.csv", processos);

    if (qtd_processos <= 0) {
        printf("Erro ao ler os processos.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\n==MENU DE OPCOES==:\n");
        printf("1. Ordenar por ID (crescente)\n");
        printf("2. Ordenar por data de ajuizamento (decrescente)\n");
        printf("3. Contar processos por id_classe\n");
        printf("4. Contar id_assuntos unicos\n");
        printf("5. Listar processos com mais de um assunto\n");
        printf("6. Mostrar dias em tramitacao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                ordenar_por_id(processos, qtd_processos);
                salvar_csv("saidaordenadaid.csv", processos, qtd_processos);
                printf("Arquivo 'saidaordenadaid.csv' gerado.\n");
                break;
            case 2:
                ordenar_por_data(processos, qtd_processos);
                salvar_csv("saidaordenadadata.csv", processos, qtd_processos);
                printf("Arquivo 'saidaordenadadata.csv' gerado.\n");
                break;
            case 3: {
                int id_classe;
                printf("Digite o id_classe para buscar: ");
                scanf("%d", &id_classe);
                int count = contar_por_classe(processos, qtd_processos, id_classe);
                printf("Processos com id_classe %d: %d\n", id_classe, count);
                break;
            }
            case 4: {
                int total = contar_assuntos_unicos(processos, qtd_processos);
                printf("Total de id_assuntos diferentes: %d\n", total);
                break;
            }
            case 5:
                listar_multiplos_assuntos(processos, qtd_processos);
                break;
            case 6:
                mostrar_dias_em_tramitacao(processos, qtd_processos);
                break;
            case 0:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
