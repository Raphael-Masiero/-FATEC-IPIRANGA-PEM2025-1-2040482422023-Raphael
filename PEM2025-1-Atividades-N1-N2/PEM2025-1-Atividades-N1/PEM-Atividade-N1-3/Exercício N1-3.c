/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Sistema de controle de estoque   *
* para empresa atacadista utilizando matriz 3D para      *
* gerenciar produtos em 3 ruas e 10 gondolas, permitindo *
* estocagem, retirada e visualizacao dos produtos.       *
* Data - 07/03/2024                                      *
* Autor: Raphael Masiero Granado; 2040482422023         *
*--------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_RUAS 3
#define NUM_GONDOLAS 10
#define TAM_CODIGO 10

// Função para converter letra da rua em índice
int ruaParaIndice(char rua) {
    return toupper(rua) - 'A';
}

// Função para converter índice em letra da rua
char indiceParaRua(int indice) {
    return 'A' + indice;
}

// Função para verificar se um produto já existe e onde ele está armazenado
void verificarProduto(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO], char codigo[], int *rua, int *gondola) {
    *rua = -1;
    *gondola = -1;

    for (int i = 0; i < NUM_RUAS; i++) {
        for (int j = 0; j < NUM_GONDOLAS; j++) {
            // Se encontrou o código do produto
            if (strcmp(armazem[i][j][0], codigo) == 0) {
                *rua = i;
                *gondola = j;
                return;
            }
        }
    }
}

// Função para estocar um produto
void estocarProduto(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO]) {
    char codigo[TAM_CODIGO];
    char ruaChar;
    int gondolaNum;
    int quantidade;
    int rua, gondola;

    printf("\n===== ESTOCAR PRODUTO =====\n");
    printf("Digite o código do produto: ");
    scanf("%s", codigo);

    // Verificar se o produto já está cadastrado
    verificarProduto(armazem, codigo, &rua, &gondola);

    if (rua != -1) {
        // Produto já cadastrado, adicionar à quantidade existente
        printf("Produto já cadastrado na gôndola %c%d\n", indiceParaRua(rua), gondola+1);
        printf("Quantidade atual: %s\n", armazem[rua][gondola][1]);
        printf("Digite a quantidade adicional: ");
        scanf("%d", &quantidade);

        int qtdAtual = atoi(armazem[rua][gondola][1]);
        qtdAtual += quantidade;
        sprintf(armazem[rua][gondola][1], "%d", qtdAtual);

        printf("Estoque atualizado com sucesso!\n");
    } else {
        // Novo produto, precisa definir a posição
        printf("Novo produto. Defina a posição de armazenamento.\n");

        do {
            printf("Digite a rua (A, B ou C): ");
            scanf(" %c", &ruaChar);
            rua = ruaParaIndice(ruaChar);

            if (rua < 0 || rua >= NUM_RUAS) {
                printf("Rua inválida! Use A, B ou C.\n");
                continue;
            }

            printf("Digite o número da gôndola (1-10): ");
            scanf("%d", &gondolaNum);
            gondola = gondolaNum - 1; // Ajuste para índice 0-9

            if (gondola < 0 || gondola >= NUM_GONDOLAS) {
                printf("Número de gôndola inválido! Use 1-10.\n");
                continue;
            }

            // Verificar se a posição está ocupada por outro produto
            if (strlen(armazem[rua][gondola][0]) > 0 && strcmp(armazem[rua][gondola][0], codigo) != 0) {
                printf("Esta posição já está ocupada pelo produto %s!\n", armazem[rua][gondola][0]);
                continue;
            }

            break;
        } while (1);

        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);

        // Armazenar o código e a quantidade
        strcpy(armazem[rua][gondola][0], codigo);
        sprintf(armazem[rua][gondola][1], "%d", quantidade);

        printf("Produto %s estocado na gôndola %c%d com sucesso!\n", codigo, indiceParaRua(rua), gondola+1);
    }
}

// Função para retirar um produto
void retirarProduto(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO]) {
    char codigo[TAM_CODIGO];
    int quantidade;
    int rua, gondola;

    printf("\n===== RETIRAR PRODUTO =====\n");
    printf("Digite o código do produto: ");
    scanf("%s", codigo);

    // Verificar se o produto existe
    verificarProduto(armazem, codigo, &rua, &gondola);

    if (rua == -1) {
        printf("Produto não encontrado no estoque!\n");
        return;
    }

    printf("Produto encontrado na gôndola %c%d\n", indiceParaRua(rua), gondola+1);
    printf("Quantidade atual: %s\n", armazem[rua][gondola][1]);

    printf("Digite a quantidade a retirar: ");
    scanf("%d", &quantidade);

    int qtdAtual = atoi(armazem[rua][gondola][1]);

    if (quantidade > qtdAtual) {
        printf("Quantidade insuficiente em estoque!\n");
        return;
    }

    qtdAtual -= quantidade;
    sprintf(armazem[rua][gondola][1], "%d", qtdAtual);

    printf("Retirada realizada com sucesso!\n");

    // Se a quantidade for zero, remover o produto
    if (qtdAtual == 0) {
        printf("Estoque zerado! Removendo produto do cadastro.\n");
        armazem[rua][gondola][0][0] = '\0';
        armazem[rua][gondola][1][0] = '\0';
    }
}

// Função para consultar o estoque
void consultarEstoque(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO]) {
    int opcao;
    char codigo[TAM_CODIGO];
    int rua, gondola;

    printf("\n===== CONSULTAR ESTOQUE =====\n");
    printf("1. Consultar por produto\n");
    printf("2. Consultar todo o estoque\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Digite o código do produto: ");
        scanf("%s", codigo);

        verificarProduto(armazem, codigo, &rua, &gondola);

        if (rua != -1) {
            printf("\nProduto: %s\n", codigo);
            printf("Localização: Gôndola %c%d\n", indiceParaRua(rua), gondola+1);
            printf("Quantidade: %s\n", armazem[rua][gondola][1]);
        } else {
            printf("Produto não encontrado no estoque!\n");
        }
    } else if (opcao == 2) {
        printf("\n===== RELATÓRIO DE ESTOQUE =====\n");
        printf("%-10s | %-10s | %-10s\n", "Produto", "Localização", "Quantidade");
        printf("-------------------------------------\n");

        int produtosEncontrados = 0;

        for (int i = 0; i < NUM_RUAS; i++) {
            for (int j = 0; j < NUM_GONDOLAS; j++) {
                if (strlen(armazem[i][j][0]) > 0) {
                    printf("%-10s | %-10c%-1d | %-10s\n",
                           armazem[i][j][0],
                           indiceParaRua(i),
                           j+1,
                           armazem[i][j][1]);
                    produtosEncontrados++;
                }
            }
        }

        if (produtosEncontrados == 0) {
            printf("Nenhum produto encontrado no estoque!\n");
        }
    } else {
        printf("Opção inválida!\n");
    }
}

int main() {
    // Matriz 3D:
    // [rua][gondola][0 = código / 1 = quantidade][string]
    char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO];
    int opcao;

    // Inicializar matriz com strings vazias
    for (int i = 0; i < NUM_RUAS; i++) {
        for (int j = 0; j < NUM_GONDOLAS; j++) {
            armazem[i][j][0][0] = '\0';  // Código vazio
            armazem[i][j][1][0] = '\0';  // Quantidade vazia
        }
    }

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE ESTOQUE =====\n");
        printf("1. Estocar produto\n");
        printf("2. Retirar produto\n");
        printf("3. Consultar estoque\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                estocarProduto(armazem);
                break;
            case 2:
                retirarProduto(armazem);
                break;
            case 3:
                consultarEstoque(armazem);
                break;
            case 4:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
