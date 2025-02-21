#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

int main() {

    Cadastro_Pessoa *lista = NULL; // Inicializa a lista vazia
    int opcao, escolha;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Cadastro de Pessoas\n");
        printf("2 - Cadastro de Transacoes\n");
        printf("3 - Consulta de Totais\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                do {
                    menu_cadastro_pessoas();
                    printf("Escolha uma opcao: ");
                    scanf("%d", &escolha);

                    switch (escolha) {
                        case 1:
                            lista = cadastrar_pessoa(lista);
                            break;
                        case 2:
                            listar_pessoas(lista);
                            break;
                        case 3:
                            lista = deletar_pessoa(lista);
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao inválida! Tente novamente.\n");
                    }
                } while (escolha != 0);
                break;

            case 2:
                do {
                    menu_cadastro_transacoes();
                    printf("Escolha uma opcao: ");
                    scanf("%d", &escolha);

                    switch (escolha) {
                        case 1:
                            cadastrar_transacao(lista);
                            break;
                        case 2:
                            listar_transacoes(lista);
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao inválida! Tente novamente.\n");
                    }
                } while (escolha != 0);
                break;

            case 3:
                do {
                    menu_consultar_totais();
                    printf("Escolha uma opcao: ");
                    scanf("%d", &escolha);

                    switch (escolha) {
                        case 1:
                            consultar_totais(lista);
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao inválida! Tente novamente.\n");
                    }
                } while (escolha != 0);
                break;

            case 4:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
