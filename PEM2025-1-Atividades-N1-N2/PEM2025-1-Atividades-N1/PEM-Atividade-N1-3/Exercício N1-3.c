/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programa�ao Estruturada e Modular          *
*          Prof. Ver�ssimo                               *
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

// Fun��o para converter letra da rua em �ndice
int ruaParaIndice(char rua) {
    return toupper(rua) - 'A';
}

// Fun��o para converter �ndice em letra da rua
char indiceParaRua(int indice) {
    return 'A' + indice;
}

// Fun��o para verificar se um produto j� existe e onde ele est� armazenado
void verificarProduto(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO], char codigo[], int *rua, int *gondola) {
    *rua = -1;
    *gondola = -1;

    for (int i = 0; i < NUM_RUAS; i++) {
        for (int j = 0; j < NUM_GONDOLAS; j++) {
            // Se encontrou o c�digo do produto
            if (strcmp(armazem[i][j][0], codigo) == 0) {
                *rua = i;
                *gondola = j;
                return;
            }
        }
    }
}

// Fun��o para estocar um produto
void estocarProduto(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO]) {
    char codigo[TAM_CODIGO];
    char ruaChar;
    int gondolaNum;
    int quantidade;
    int rua, gondola;

    printf("\n===== ESTOCAR PRODUTO =====\n");
    printf("Digite o c�digo do produto: ");
    scanf("%s", codigo);

    // Verificar se o produto j� est� cadastrado
    verificarProduto(armazem, codigo, &rua, &gondola);

    if (rua != -1) {
        // Produto j� cadastrado, adicionar � quantidade existente
        printf("Produto j� cadastrado na g�ndola %c%d\n", indiceParaRua(rua), gondola+1);
        printf("Quantidade atual: %s\n", armazem[rua][gondola][1]);
        printf("Digite a quantidade adicional: ");
        scanf("%d", &quantidade);

        int qtdAtual = atoi(armazem[rua][gondola][1]);
        qtdAtual += quantidade;
        sprintf(armazem[rua][gondola][1], "%d", qtdAtual);

        printf("Estoque atualizado com sucesso!\n");
    } else {
        // Novo produto, precisa definir a posi��o
        printf("Novo produto. Defina a posi��o de armazenamento.\n");

        do {
            printf("Digite a rua (A, B ou C): ");
            scanf(" %c", &ruaChar);
            rua = ruaParaIndice(ruaChar);

            if (rua < 0 || rua >= NUM_RUAS) {
                printf("Rua inv�lida! Use A, B ou C.\n");
                continue;
            }

            printf("Digite o n�mero da g�ndola (1-10): ");
            scanf("%d", &gondolaNum);
            gondola = gondolaNum - 1; // Ajuste para �ndice 0-9

            if (gondola < 0 || gondola >= NUM_GONDOLAS) {
                printf("N�mero de g�ndola inv�lido! Use 1-10.\n");
                continue;
            }

            // Verificar se a posi��o est� ocupada por outro produto
            if (strlen(armazem[rua][gondola][0]) > 0 && strcmp(armazem[rua][gondola][0], codigo) != 0) {
                printf("Esta posi��o j� est� ocupada pelo produto %s!\n", armazem[rua][gondola][0]);
                continue;
            }

            break;
        } while (1);

        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);

        // Armazenar o c�digo e a quantidade
        strcpy(armazem[rua][gondola][0], codigo);
        sprintf(armazem[rua][gondola][1], "%d", quantidade);

        printf("Produto %s estocado na g�ndola %c%d com sucesso!\n", codigo, indiceParaRua(rua), gondola+1);
    }
}

// Fun��o para retirar um produto
void retirarProduto(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO]) {
    char codigo[TAM_CODIGO];
    int quantidade;
    int rua, gondola;

    printf("\n===== RETIRAR PRODUTO =====\n");
    printf("Digite o c�digo do produto: ");
    scanf("%s", codigo);

    // Verificar se o produto existe
    verificarProduto(armazem, codigo, &rua, &gondola);

    if (rua == -1) {
        printf("Produto n�o encontrado no estoque!\n");
        return;
    }

    printf("Produto encontrado na g�ndola %c%d\n", indiceParaRua(rua), gondola+1);
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

// Fun��o para consultar o estoque
void consultarEstoque(char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO]) {
    int opcao;
    char codigo[TAM_CODIGO];
    int rua, gondola;

    printf("\n===== CONSULTAR ESTOQUE =====\n");
    printf("1. Consultar por produto\n");
    printf("2. Consultar todo o estoque\n");
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Digite o c�digo do produto: ");
        scanf("%s", codigo);

        verificarProduto(armazem, codigo, &rua, &gondola);

        if (rua != -1) {
            printf("\nProduto: %s\n", codigo);
            printf("Localiza��o: G�ndola %c%d\n", indiceParaRua(rua), gondola+1);
            printf("Quantidade: %s\n", armazem[rua][gondola][1]);
        } else {
            printf("Produto n�o encontrado no estoque!\n");
        }
    } else if (opcao == 2) {
        printf("\n===== RELAT�RIO DE ESTOQUE =====\n");
        printf("%-10s | %-10s | %-10s\n", "Produto", "Localiza��o", "Quantidade");
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
        printf("Op��o inv�lida!\n");
    }
}

int main() {
    // Matriz 3D:
    // [rua][gondola][0 = c�digo / 1 = quantidade][string]
    char armazem[NUM_RUAS][NUM_GONDOLAS][2][TAM_CODIGO];
    int opcao;

    // Inicializar matriz com strings vazias
    for (int i = 0; i < NUM_RUAS; i++) {
        for (int j = 0; j < NUM_GONDOLAS; j++) {
            armazem[i][j][0][0] = '\0';  // C�digo vazio
            armazem[i][j][1][0] = '\0';  // Quantidade vazia
        }
    }

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE ESTOQUE =====\n");
        printf("1. Estocar produto\n");
        printf("2. Retirar produto\n");
        printf("3. Consultar estoque\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
