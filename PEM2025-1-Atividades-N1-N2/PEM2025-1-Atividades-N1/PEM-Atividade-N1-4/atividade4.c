/*-------------------------------------------------------*
 * Disciplina: Programa��o Estruturada e Modular         *
 *          Prof. Ver�ssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Recursividade                   *
 * Data: 26/03/2025                                      *
 * Autor: Raphael Masiero                                 *
 *--------------------------------------------------------*/

#include <stdio.h>              // Biblioteca padr�o de entrada e sa�da (ex: printf, scanf)
#include <windows.h>            // Biblioteca da API do Windows, usada para manipular arquivos e pastas

#define LIMITE_RECURSAO 10      // Define um limite para a profundidade da recurs�o (evita loops infinitos)

// Fun��o recursiva para listar arquivos e pastas
void listar_pasta(const char *caminho, int nivel) {
    // Impede que a recurs�o v� al�m do limite
    if (nivel >= LIMITE_RECURSAO) {
        return;
    }

    WIN32_FIND_DATA item;             // Estrutura que vai conter dados sobre arquivos/encontrados
    HANDLE hBusca;                    // Handle (ponteiro) para o processo de busca
    char caminho_busca[MAX_PATH];     // Armazena o caminho de busca (ex: "C:\\pasta\\*")
    char proximo_caminho[MAX_PATH];   // Armazena o caminho de uma subpasta encontrada

    sprintf(caminho_busca, "%s\\*", caminho); // Cria o caminho com curinga (para listar tudo da pasta)
    hBusca = FindFirstFile(caminho_busca, &item); // Inicia a busca de arquivos

    // Se a busca falhar, mostra erro e retorna
    if (hBusca == INVALID_HANDLE_VALUE) {
        printf("Erro ao acessar: %s\n", caminho);
        return;
    }

    // Loop para listar todos os arquivos/pastas encontrados
    do {
        // Ignora os diret�rios especiais "." (pasta atual) e ".." (pasta anterior)
        if (strcmp(item.cFileName, ".") == 0 || strcmp(item.cFileName, "..") == 0) continue;

        // Indenta de acordo com o n�vel atual da recurs�o, para mostrar hierarquia
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("|-- %s\n", item.cFileName); // Mostra o nome do item

        // Se for uma pasta (e n�o for um atalho simb�lico)
        if ((item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            !(item.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
            // Cria o novo caminho completo da subpasta
            sprintf(proximo_caminho, "%s\\%s", caminho, item.cFileName);
            // Chama a fun��o recursivamente para explorar a subpasta
            listar_pasta(proximo_caminho, nivel + 1);
        }

    } while (FindNextFile(hBusca, &item) != 0); // Continua listando at� acabar os itens

    FindClose(hBusca); // Fecha o handle da busca (boa pr�tica)
}

int main() {
    char caminho[MAX_PATH]; // Vari�vel para armazenar o caminho digitado pelo usu�rio

    printf("Digite o caminho da pasta: "); // Solicita ao usu�rio a pasta a ser listada
    scanf("%s", caminho); // L� o caminho digitado

    listar_pasta(caminho, 0); // Chama a fun��o de listagem com o n�vel inicial 0

    return 0; // Fim do programa
}
