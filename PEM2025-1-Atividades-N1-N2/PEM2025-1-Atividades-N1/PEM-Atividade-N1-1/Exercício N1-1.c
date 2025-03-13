/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programa�ao Estruturada e Modular          *
*          Prof. Ver�ssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Sistema de sele��o para          *
* resid�ncia m�dica que gerencia notas de candidatos     *
* em quatro etapas avaliativas (PE, AC, PP, EB),         *
* calculando m�dias com descarte de notas extremas       *
* e classificando os 15 melhores candidatos.             *
* Data - 10/03/2025                                      *
* Autor: Raphael Masiero Granado; 2040482422023         *
*--------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

int main() {
    // Declara��o de vari�veis e arrays
    char nomes[50][100]; // Array para armazenar nomes de at� 50 candidatos
    float notasPE[50][4]; // 4 notas de Prova Escrita para cada candidato
    float notasAC[50][5]; // 5 notas de An�lise Curricular para cada candidato
    float notasPP[50][10]; // 10 notas de Prova Pr�tica para cada candidato
    float notasEB[50][3]; // 3 notas de Entrevista em Banca para cada candidato

    float notaFinalPE[50]; // Nota final da Prova Escrita para cada candidato
    float notaFinalAC[50]; // Nota final da An�lise Curricular para cada candidato
    float notaFinalPP[50]; // Nota final da Prova Pr�tica para cada candidato
    float notaFinalEB[50]; // Nota final da Entrevista em Banca para cada candidato

    float notaFinal[50]; // Nota final classificat�ria para cada candidato
    int indices[50]; // Array para manter os �ndices originais durante a ordena��o

    int numCandidatos; // N�mero total de candidatos
    int i, j, k; // Vari�veis para loops
    float temp; // Vari�vel tempor�ria para troca na ordena��o
    int tempIndice; // Vari�vel tempor�ria para troca de �ndices

    // Solicitar o n�mero de candidatos (m�ximo 50)
    printf("Digite o numero de candidatos (maximo 50): ");
    scanf("%d", &numCandidatos);

    if (numCandidatos > 50) {
        printf("Numero maximo de candidatos excedido. Limitando a 50.\n");
        numCandidatos = 50;
    }

    // Para cada candidato, coletar nome e notas
    for (i = 0; i < numCandidatos; i++) {
        printf("\n--- Candidato %d ---\n", i + 1);

        // Limpar o buffer de entrada
        while (getchar() != '\n');

        // Coletar nome do candidato
        printf("Nome do candidato: ");
        fgets(nomes[i], 100, stdin);

        // Remover o caractere de nova linha do nome, se presente
        if (nomes[i][strlen(nomes[i]) - 1] == '\n') {
            nomes[i][strlen(nomes[i]) - 1] = '\0';
        }

        // Coletar as 4 notas da Prova Escrita (PE)
        printf("\nNotas da Prova Escrita (PE) - 4 notas de 0 a 10:\n");
        for (j = 0; j < 4; j++) {
            do {
                printf("Nota PE %d: ", j + 1);
                scanf("%f", &notasPE[i][j]);

                if (notasPE[i][j] < 0 || notasPE[i][j] > 10) {
                    printf("Nota invalida. Digite um valor entre 0 e 10.\n");
                }
            } while (notasPE[i][j] < 0 || notasPE[i][j] > 10);
        }

        // Coletar as 5 notas da An�lise Curricular (AC)
        printf("\nNotas da Analise Curricular (AC) - 5 notas de 0 a 10:\n");
        for (j = 0; j < 5; j++) {
            do {
                printf("Nota AC %d: ", j + 1);
                scanf("%f", &notasAC[i][j]);

                if (notasAC[i][j] < 0 || notasAC[i][j] > 10) {
                    printf("Nota invalida. Digite um valor entre 0 e 10.\n");
                }
            } while (notasAC[i][j] < 0 || notasAC[i][j] > 10);
        }

        // Coletar as 10 notas da Prova Pr�tica (PP)
        printf("\nNotas da Prova Pratica (PP) - 10 notas de 0 a 10:\n");
        for (j = 0; j < 10; j++) {
            do {
                printf("Nota PP %d: ", j + 1);
                scanf("%f", &notasPP[i][j]);

                if (notasPP[i][j] < 0 || notasPP[i][j] > 10) {
                    printf("Nota invalida. Digite um valor entre 0 e 10.\n");
                }
            } while (notasPP[i][j] < 0 || notasPP[i][j] > 10);
        }

        // Coletar as 3 notas da Entrevista em Banca (EB)
        printf("\nNotas da Entrevista em Banca (EB) - 3 notas de 0 a 10:\n");
        for (j = 0; j < 3; j++) {
            do {
                printf("Nota EB %d: ", j + 1);
                scanf("%f", &notasEB[i][j]);

                if (notasEB[i][j] < 0 || notasEB[i][j] > 10) {
                    printf("Nota invalida. Digite um valor entre 0 e 10.\n");
                }
            } while (notasEB[i][j] < 0 || notasEB[i][j] > 10);
        }

        // Inicializar os �ndices para ordena��o posterior
        indices[i] = i;
    }

    // Calcular a nota final para cada candidato
    for (i = 0; i < numCandidatos; i++) {
        // Ordenar as notas de PE para encontrar as notas centrais
        for (j = 0; j < 3; j++) {
            for (k = j + 1; k < 4; k++) {
                if (notasPE[i][j] > notasPE[i][k]) {
                    temp = notasPE[i][j];
                    notasPE[i][j] = notasPE[i][k];
                    notasPE[i][k] = temp;
                }
            }
        }

        // Calcular nota final de PE (excluindo a maior e a menor)
        notaFinalPE[i] = (notasPE[i][1] + notasPE[i][2]) / 2.0;

        // Ordenar as notas de AC para encontrar as notas centrais
        for (j = 0; j < 4; j++) {
            for (k = j + 1; k < 5; k++) {
                if (notasAC[i][j] > notasAC[i][k]) {
                    temp = notasAC[i][j];
                    notasAC[i][j] = notasAC[i][k];
                    notasAC[i][k] = temp;
                }
            }
        }

        // Calcular nota final de AC (excluindo a maior e a menor)
        notaFinalAC[i] = (notasAC[i][1] + notasAC[i][2] + notasAC[i][3]) / 3.0;

        // Ordenar as notas de PP para encontrar as notas centrais
        for (j = 0; j < 9; j++) {
            for (k = j + 1; k < 10; k++) {
                if (notasPP[i][j] > notasPP[i][k]) {
                    temp = notasPP[i][j];
                    notasPP[i][j] = notasPP[i][k];
                    notasPP[i][k] = temp;
                }
            }
        }

        // Calcular nota final de PP (excluindo a maior e a menor)
        float somaPP = 0;
        for (j = 1; j < 9; j++) {
            somaPP += notasPP[i][j];
        }
        notaFinalPP[i] = somaPP / 8.0;

        // Ordenar as notas de EB para encontrar a nota central
        for (j = 0; j < 2; j++) {
            for (k = j + 1; k < 3; k++) {
                if (notasEB[i][j] > notasEB[i][k]) {
                    temp = notasEB[i][j];
                    notasEB[i][j] = notasEB[i][k];
                    notasEB[i][k] = temp;
                }
            }
        }

        // Calcular nota final de EB (como s� temos 3 notas, excluindo a maior e a menor, ficamos com 1)
        notaFinalEB[i] = notasEB[i][1];

        // Calcular nota final classificat�ria usando a f�rmula
        notaFinal[i] = (notaFinalPE[i] * 0.3) + (notaFinalAC[i] * 0.1) +
                       (notaFinalPP[i] * 0.4) + (notaFinalEB[i] * 0.2);
    }

    // Ordenar os candidatos por nota final (decrescente)
    for (i = 0; i < numCandidatos - 1; i++) {
        for (j = i + 1; j < numCandidatos; j++) {
            if (notaFinal[indices[i]] < notaFinal[indices[j]]) {
                tempIndice = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndice;
            }
        }
    }

    // Exibir os 15 melhores candidatos ou todos, se houver menos que 15
    int limite = (numCandidatos < 15) ? numCandidatos : 15;

    printf("\n\n=== CLASSIFICACAO FINAL DOS %d MELHORES CANDIDATOS ===\n", limite);
    printf("Posicao | Nome                           | Nota Final\n");
    printf("---------------------------------------------------------\n");

    for (i = 0; i < limite; i++) {
        int idx = indices[i];
        printf("%-8d| %-30s | %.2f\n", i + 1, nomes[idx], notaFinal[idx]);
    }

    printf("\n=== DETALHAMENTO DAS NOTAS DOS %d MELHORES CANDIDATOS ===\n", limite);
    for (i = 0; i < limite; i++) {
        int idx = indices[i];
        printf("\n%d. %s\n", i + 1, nomes[idx]);
        printf("   Prova Escrita (PE): %.2f (peso 0.3)\n", notaFinalPE[idx]);
        printf("   Analise Curricular (AC): %.2f (peso 0.1)\n", notaFinalAC[idx]);
        printf("   Prova Pratica (PP): %.2f (peso 0.4)\n", notaFinalPP[idx]);
        printf("   Entrevista em Banca (EB): %.2f (peso 0.2)\n", notaFinalEB[idx]);
        printf("   NOTA FINAL: %.2f\n", notaFinal[idx]);
    }

    return 0;
}
