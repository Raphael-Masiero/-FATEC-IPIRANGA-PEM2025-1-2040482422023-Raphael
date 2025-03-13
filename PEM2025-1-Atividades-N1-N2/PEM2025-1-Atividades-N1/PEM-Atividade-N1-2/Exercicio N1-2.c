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

#define MAX_RUAS 3
#define MAX_GONDOLAS 10
#define MAX_PRODUTOS 100
#define MAX_CODIGO 10

int main() {
    // Matriz tridimensional para armazenar informações do armazém
    // [rua][gondola][0] = quantidade de produtos na gôndola
    // [rua][gondola][1] = flag se gôndola está ocupada (0 = livre, 1 = ocupada)
    int armazem[MAX_RUAS][MAX_GONDOLAS][2];

    // Matriz para armazenar códigos de produtos e suas localizações
    // [i][0] = índice da rua (0 = A, 1 = B, 2 = C)
    // [i][1] = índice da gôndola (0-9)
    // [i][2] = flag se posição está usada (0 = não usado, 1 = usado)
    int produtos[MAX_PRODUTOS][3];

    // Array para armazenar os códigos dos produtos
    char codigos[MAX_PRODUTOS][MAX_CODIGO];

    // Variáveis para entrada e controle
    char codigo_produto[MAX_CODIGO];
    char rua;
    int gondola, quantidade;
    int opcao, i, j, k, encontrado, indice_produto;

    // Inicializar armazém
    for (i = 0; i < MAX_RUAS; i++) {
        for (j = 0; j < MAX_GONDOLAS; j++) {
            armazem[i][j][0] = 0;      // Quantidade zero
            armazem[i][j][1] = 0;      // Gôndola livre
        }
    }

    // Inicializar produtos
    for (i = 0; i < MAX_PRODUTOS; i++) {
        produtos[i][0] = -1;           // Rua inválida
        produtos[i][1] = -1;           // Gôndola inválida
        produtos[i][2] = 0;            // Não usado
        codigos[i][0] = '\0';          // String vazia
    }

    // Menu principal
    do {
        printf("\n\n==== SISTEMA DE GERENCIAMENTO DE ARMAZEM ====\n");
        printf("1. Estocagem de Produto\n");
        printf("2. Retirada de Produto\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Estocagem de Produto
                printf("\n--- ESTOCAGEM DE PRODUTO ---\n");
                printf("Digite o codigo do produto: ");
                scanf("%s", codigo_produto);
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                // Verificar se o produto já existe
                encontrado = 0;
                indice_produto = -1;

                for (i = 0; i < MAX_PRODUTOS && !encontrado; i++) {
                    if (produtos[i][2] == 1 && strcmp(codigos[i], codigo_produto) == 0) {
                        encontrado = 1;
                        indice_produto = i;
                    }
                }

                if (encontrado) {
                    // Produto já existe, atualizar quantidade na gôndola existente
                    int rua_idx = produtos[indice_produto][0];
                    int gondola_idx = produtos[indice_produto][1];

                    armazem[rua_idx][gondola_idx][0] += quantidade;

                    printf("Produto %s adicionado na gondola %c%d. Quantidade atual: %d\n",
                           codigo_produto,
                           'A' + rua_idx,
                           gondola_idx + 1,
                           armazem[rua_idx][gondola_idx][0]);
                } else {
                    // Produto novo, precisa de uma nova gôndola
                    printf("Produto novo. Digite a rua (A, B ou C): ");
                    scanf(" %c", &rua);
                    printf("Digite o numero da gondola (1-10): ");
                    scanf("%d", &gondola);

                    // Converter rua e gôndola para índices (0-based)
                    int rua_idx = rua - 'A';
                    int gondola_idx = gondola - 1;

                    // Verificar se índices são válidos
                    if (rua_idx < 0 || rua_idx >= MAX_RUAS || gondola_idx < 0 || gondola_idx >= MAX_GONDOLAS) {
                        printf("Rua ou gondola invalida!\n");
                        break;
                    }

                    // Verificar se a gôndola já está ocupada por outro produto
                    if (armazem[rua_idx][gondola_idx][1] == 1) {
                        printf("Esta gondola ja esta ocupada por outro produto!\n");
                        break;
                    }

                    // Encontrar um slot livre no array de produtos
                    indice_produto = -1;
                    for (i = 0; i < MAX_PRODUTOS && indice_produto == -1; i++) {
                        if (produtos[i][2] == 0) {
                            indice_produto = i;
                        }
                    }

                    if (indice_produto == -1) {
                        printf("Limite de produtos atingido!\n");
                        break;
                    }

                    // Registrar o novo produto
                    strcpy(codigos[indice_produto], codigo_produto);
                    produtos[indice_produto][0] = rua_idx;
                    produtos[indice_produto][1] = gondola_idx;
                    produtos[indice_produto][2] = 1;

                    // Atualizar a gôndola
                    armazem[rua_idx][gondola_idx][0] = quantidade;
                    armazem[rua_idx][gondola_idx][1] = 1;  // Marcar como ocupada

                    printf("Produto %s registrado na gondola %c%d com quantidade %d\n",
                           codigo_produto, rua, gondola, quantidade);
                }
                break;

            case 2: // Retirada de Produto
                printf("\n--- RETIRADA DE PRODUTO ---\n");
                printf("Digite o codigo do produto: ");
                scanf("%s", codigo_produto);
                printf("Digite a quantidade a retirar: ");
                scanf("%d", &quantidade);

                // Verificar se o produto existe
                encontrado = 0;
                indice_produto = -1;

                for (i = 0; i < MAX_PRODUTOS && !encontrado; i++) {
                    if (produtos[i][2] == 1 && strcmp(codigos[i], codigo_produto) == 0) {
                        encontrado = 1;
                        indice_produto = i;
                    }
                }

                if (!encontrado) {
                    printf("Produto %s nao encontrado no armazem!\n", codigo_produto);
                    break;
                }

                // Produto encontrado, verificar quantidade disponível
                int rua_idx = produtos[indice_produto][0];
                int gondola_idx = produtos[indice_produto][1];

                if (armazem[rua_idx][gondola_idx][0] < quantidade) {
                    printf("Quantidade insuficiente! Disponivel: %d\n", armazem[rua_idx][gondola_idx][0]);
                    break;
                }

                // Retirar a quantidade solicitada
                armazem[rua_idx][gondola_idx][0] -= quantidade;

                printf("Retirada realizada com sucesso. Nova quantidade: %d\n",
                       armazem[rua_idx][gondola_idx][0]);

                // Se a quantidade chegou a zero, podemos liberar a gôndola
                if (armazem[rua_idx][gondola_idx][0] == 0) {
                    armazem[rua_idx][gondola_idx][1] = 0;  // Marcar como livre
                    produtos[indice_produto][2] = 0;       // Marcar como não usado
                    printf("Gondola %c%d liberada.\n", 'A' + rua_idx, gondola_idx + 1);
                }
                break;

            case 3: // Sair
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}
