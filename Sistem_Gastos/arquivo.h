#ifndef ARQUIVO_H
#define ARQUIVO_H
// Estrutura de Pessoa
typedef struct {
    int Id;
    char nome[50];
    int idade;
} Pessoa;

// Estrutura de Transação
typedef struct Transacao {
    int Id_trans;
    char descricao[100];
    float valor;
    char tipo[50];
    struct Transacao *prox;
} Transacao;

// Estrutura para a lista encadeada de cadastro de pessoas
typedef struct Cadastro_Pessoa {
    Pessoa pessoa;
    Transacao *transacoes;
    struct Cadastro_Pessoa *prox;
} Cadastro_Pessoa;

// Funções para manipulação da lista de pessoas
Cadastro_Pessoa* inicializa(void);
Cadastro_Pessoa* cadastrar_pessoa(Cadastro_Pessoa* lista);
Cadastro_Pessoa* deletar_pessoa(Cadastro_Pessoa *lista);
void listar_pessoas(Cadastro_Pessoa* lista);

// Funções para transações
void cadastrar_transacao(Cadastro_Pessoa *lista);
void listar_transacoes(Cadastro_Pessoa *lista);

// funçoes para consultar totais
void consultar_totais(Cadastro_Pessoa *lista);

// Funções do menu
void menu_cadastro_pessoas();
void menu_cadastro_transacoes();
void menu_consultar_totais();

#endif
