#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arquivo.h"
#include <math.h>

// deixando ID auto incremnto
int ultimo_id = 1;
int ultimo_id_trans = 2000;

Cadastro_Pessoa* inicializa(void) {
    return NULL;
}

// Função para cadastrar uma nova pessoa
Cadastro_Pessoa* cadastrar_pessoa(Cadastro_Pessoa* lista) {
    Cadastro_Pessoa* novo = (Cadastro_Pessoa*)malloc(sizeof(Cadastro_Pessoa));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return lista;
    }

    novo->pessoa.Id = ultimo_id++;
    getchar(); // Limpa o buffer do teclado

    printf("Nome da pessoa: ");
    fgets(novo->pessoa.nome, 50, stdin);
    novo->pessoa.nome[strcspn(novo->pessoa.nome, "\n")] = 0;

    printf("Idade da pessoa: ");
    scanf("%d", &novo->pessoa.idade);

    novo->transacoes = NULL; // Inicializa a lista de transações como vazia
    novo->prox = lista;

    printf("Pessoa cadastrada com sucesso! ID: %d\n", novo->pessoa.Id);
    return novo;
}

void listar_pessoas(Cadastro_Pessoa* lista) {
    if (lista == NULL) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    printf("\nLista de Pessoas Cadastradas:\n");
    Cadastro_Pessoa* atual = lista;
    while (atual != NULL) {
        printf("ID: %d | Nome: %s | Idade: %d\n", atual->pessoa.Id, atual->pessoa.nome, atual->pessoa.idade);
        atual = atual->prox;
    }
}

Cadastro_Pessoa* deletar_pessoa(Cadastro_Pessoa *lista) {
    int id;
    printf("Digite o ID da pessoa que deseja remover: ");
    scanf("%d", &id);

    Cadastro_Pessoa *atual = lista, *anterior = NULL;

    while (atual != NULL) {
        if (atual->pessoa.Id == id) {
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Pessoa com ID %d removida com sucesso!\n", id);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Pessoa com ID %d nao encontrada!\n", id);
    return lista;
}

// Função para cadastrar uma transação associada a uma pessoa
void cadastrar_transacao(Cadastro_Pessoa *lista) {
    if (lista == NULL) {
        printf("Nenhuma pessoa cadastrada. Cadastre uma pessoa primeiro.\n");
        return;
    }

    int id_pessoa;
    printf("Digite o ID da pessoa para adicionar uma transacao: ");
    scanf("%d", &id_pessoa);

    Cadastro_Pessoa *pessoa = lista;
    while (pessoa != NULL && pessoa->pessoa.Id != id_pessoa) {
        pessoa = pessoa->prox;
    }

    if (pessoa == NULL) {
        printf("Pessoa nao encontrada.\n");
        return;
    }

    Transacao *nova = (Transacao *)malloc(sizeof(Transacao));
    if (nova == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    nova->Id_trans = ultimo_id_trans++; // Atribui o ID da transação e incrementa

    getchar(); // Limpa o buffer do teclado
    printf("Digite a descricao da transacao: ");
    fgets(nova->descricao, 100, stdin);
    nova->descricao[strcspn(nova->descricao, "\n")] = 0; // Remover '\n'

    printf("Digite o valor da transacao: ");
    scanf("%f", &nova->valor);
    getchar(); // Limpar buffer do teclado

    char tipo;

    // Verifica se a pessoa é menor de idade
    if (pessoa->pessoa.idade < 18) {
        tipo = 'D'; // Forçar tipo 'D' para menores de idade
        printf("Como voce eh menor de idade, a transacao sera cadastrada como despesa.\n");
    } else {
        printf("Digite o tipo da transacao (R para receitas / D para despesas): ");
        scanf(" %c", &tipo);
        getchar(); // Limpar buffer do teclado
    }

    tipo = toupper(tipo); // Converter para maiúscula

    if (tipo == 'D') {
        nova->valor = -fabs(nova->valor); // Converter para negativo se for despesa
    } else if (tipo != 'R') {
        printf("Tipo de transacao invalido! Use 'R' para receitas ou 'D' para despesas.\n");
        free(nova);
        return;
    }

    strcpy(nova->tipo, (tipo == 'R') ? "Receita" : "Despesa"); // Armazena o tipo corretamente

    // Inserir na lista de transações da pessoa
    nova->prox = pessoa->transacoes;
    pessoa->transacoes = nova;

    printf("Transacao cadastrada com sucesso!\n");
}

void listar_transacoes(Cadastro_Pessoa *lista) {
    if (lista == NULL) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    Cadastro_Pessoa *pessoa = lista;
    int encontrou_transacao = 0; // Flag para verificar se há transações

    while (pessoa != NULL) {
        Transacao *atual = pessoa->transacoes;
        if (atual == NULL) {
            pessoa = pessoa->prox; // Se não há transações, apenas avança para a próxima pessoa
            continue;
        }

        printf("Transacoes da pessoa %s (ID: %d):\n", pessoa->pessoa.nome, pessoa->pessoa.Id);
        while (atual != NULL) {
            printf("ID: %d | Descricao: %s | Valor: %.2f | Tipo: %s\n", atual->Id_trans, atual->descricao, atual->valor, atual->tipo);
            atual = atual->prox;
            encontrou_transacao = 1; // Marca que encontrou pelo menos uma transação
        }
        pessoa = pessoa->prox; // Avança para a próxima pessoa
        printf("\n"); // Para melhor visualização
    }

    if (!encontrou_transacao) {
        printf("Nenhuma transacao cadastrada para qualquer pessoa.\n");
    }
}


void menu_cadastro_pessoas() {
    printf("\n===== MENU CADASTRO DE PESSOAS =====\n");
    printf("1 - Cadastrar Pessoa\n");
    printf("2 - Listar Pessoas\n");
    printf("3 - Remover Pessoa\n");
    printf("0 - Voltar ao Menu Principal\n");
}

void menu_cadastro_transacoes() {
    printf("\n===== MENU CADASTRO DE TRANSACOES =====\n");
    printf("1 - Cadastrar Transacao\n");
    printf("2 - Listar Transacoes\n");
    printf("0 - Voltar ao Menu Principal\n");
}

void menu_consultar_totais() {
    printf("\n===== MENU CONSULTAR TOTAIS =====\n");
    printf("1 - Consultar Totais\n");
    printf("0 - Voltar ao Menu Principal\n");
}

void consultar_totais(Cadastro_Pessoa *lista) {
    if (lista == NULL) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    float total_geral_receitas = 0.0;
    float total_geral_despesas = 0.0;

    printf("\n===== TOTAL DE RECEITAS, DESPESAS E SALDO POR PESSOA =====\n");

    Cadastro_Pessoa *pessoa_atual = lista;
    while (pessoa_atual != NULL) {
        float total_receitas = 0.0;
        float total_despesas = 0.0;

        Transacao *trans_atual = pessoa_atual->transacoes;
        while (trans_atual != NULL) {
            if (trans_atual->valor >= 0) {
                total_receitas += trans_atual->valor;
                total_geral_receitas += trans_atual->valor;
            } else {
                total_despesas += (-trans_atual->valor); // Despesas são valores negativos
                total_geral_despesas += (-trans_atual->valor);
            }
            trans_atual = trans_atual->prox;
        }

        float saldo = total_receitas - total_despesas;

        printf("\nNome: %s\n", pessoa_atual->pessoa.nome);
        printf("Total de Receitas: %.2f\n", total_receitas);
        printf("Total de Despesas: %.2f\n", total_despesas);
        printf("Saldo: %.2f\n", saldo);

        pessoa_atual = pessoa_atual->prox;
    }

    printf("\n===== RESUMO GERAL =====\n");
    printf("Total Geral de Receitas: %.2f\n", total_geral_receitas);
    printf("Total Geral de Despesas: %.2f\n", total_geral_despesas);
    printf("Saldo Geral: %.2f\n", total_geral_receitas - total_geral_despesas);
}
