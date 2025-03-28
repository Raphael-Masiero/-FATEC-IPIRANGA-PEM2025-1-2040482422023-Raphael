/*-------------------------------------------------------*
 * Disciplina: Algoritmos e Estruturas de Dados          *
 *          Prof. Ver�ssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Explora��o Recursiva            *
 * Data: 28/03/2025                                      *
 * Autor: Raphael Masiero                                *
 *--------------------------------------------------------*/
#include <stdio.h>
#include <windows.h>
// Fun��o recursiva para explorar diret�rios e mostrar conte�do hier�rquico
void explorar_sistema_recursivo(const char *pasta_base, int profundidade)
// Conforme aumenta a profundidade, aumentamos o recuo visual na exibi��o
{
    WIN32_FIND_DATA dados_encontrados;
    // WIN32_FIND_DATA armazena atributos e informa��es dos arquivos/pastas encontrados
    HANDLE manipulador;
    // HANDLE � um identificador para objetos de sistema do Windows
    // MAX_PATH define o comprimento m�ximo permitido para caminhos no Windows
    // que corresponde a 260 caracteres
    char padrao_busca[MAX_PATH];
    char pasta_interna[MAX_PATH];
    // snprintf formata strings com seguran�a para evitar estouro de mem�ria
    // Constru�mos o padr�o de busca adicionando coringa (*) ao final do caminho
    snprintf(padrao_busca, MAX_PATH, "%s\\*", pasta_base);
    // Um estouro de buffer ocorre quando tentamos escrever mais dados
    // em um espa�o de mem�ria do que ele comporta, causando comportamentos imprevis�veis
    manipulador = FindFirstFile(padrao_busca, &dados_encontrados);
    if (manipulador != INVALID_HANDLE_VALUE)
    // INVALID_HANDLE_VALUE indica falha na opera��o
    // Se diferente, a opera��o foi bem-sucedida
    {
        do
        {
            // Ignoramos as refer�ncias "." (pasta atual) e ".." (pasta pai)
            if (strcmp(dados_encontrados.cFileName, ".") == 0 || strcmp(dados_encontrados.cFileName, "..") == 0)
            {
                continue;
            }
            // Aplica recuo visual baseado na profundidade da recurs�o
            for (int i = 0; i < profundidade; i++)
            {
                printf("\t");
            }
            // Mostra o nome do item encontrado
            printf("|-- %s", dados_encontrados.cFileName);
            // Verifica o tipo do item atrav�s de seus atributos
            // FILE_ATTRIBUTE_DIRECTORY indica que � uma pasta
            // Operadores bit a bit s�o usados para verificar atributos espec�ficos
            if (dados_encontrados.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf(" [PASTA]\n");
                // Constr�i o caminho completo da subpasta
                snprintf(pasta_interna, MAX_PATH, "%s\\%s", pasta_base, dados_encontrados.cFileName);
                // Chama a fun��o novamente para explorar a subpasta, aumentando o n�vel
                explorar_sistema_recursivo(pasta_interna, profundidade + 1);
            }
            else
            {
                printf(" [ARQUIVO]\n");
            }
        } while (FindNextFile(manipulador, &dados_encontrados)); // continua enquanto houver itens
        // Liberamos o recurso do sistema ap�s o uso
        FindClose(manipulador);
    }
    else
    {
        printf("Falha ao acessar a pasta: %s\n", pasta_base);
    }
}
int main()
{
    char pasta_raiz[MAX_PATH];
    printf("Informe o caminho da pasta inicial: ");
    scanf("%s", pasta_raiz);
    printf("Iniciando exploracao da estrutura em: %s\n", pasta_raiz);
    explorar_sistema_recursivo(pasta_raiz, 0);
    return 0;
}
