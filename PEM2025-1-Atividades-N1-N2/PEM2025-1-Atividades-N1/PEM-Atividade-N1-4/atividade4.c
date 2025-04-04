/*-------------------------------------------------------*
 * Disciplina: Programação Estruturada e Modular         *
 *          Prof. Veríssimo                              *
 *--------------------------------------------------------*
 * Objetivo do Programa: Recursividade                   *
 * Data: 26/03/2025                                      *
 * Autor: Raphael Masiero                                 *
 *--------------------------------------------------------*/

#include <stdio.h>              // Biblioteca padrão de entrada e saída (ex: printf, scanf)
#include <windows.h>            // Biblioteca da API do Windows, usada para manipular arquivos e pastas

#define LIMITE_RECURSAO 10      // Define um limite para a profundidade da recursão (evita loops infinitos)

// Função recursiva para listar arquivos e pastas
void listar_pasta(const char *caminho, int nivel) {
    // Impede que a recursão vá além do limite
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
        // Ignora os diretórios especiais "." (pasta atual) e ".." (pasta anterior)
        if (strcmp(item.cFileName, ".") == 0 || strcmp(item.cFileName, "..") == 0) continue;

        // Indenta de acordo com o nível atual da recursão, para mostrar hierarquia
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("|-- %s\n", item.cFileName); // Mostra o nome do item

        // Se for uma pasta (e não for um atalho simbólico)
        if ((item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            !(item.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
            // Cria o novo caminho completo da subpasta
            sprintf(proximo_caminho, "%s\\%s", caminho, item.cFileName);
            // Chama a função recursivamente para explorar a subpasta
            listar_pasta(proximo_caminho, nivel + 1);
        }

    } while (FindNextFile(hBusca, &item) != 0); // Continua listando até acabar os itens

    FindClose(hBusca); // Fecha o handle da busca (boa prática)
}

int main() {
    char caminho[MAX_PATH]; // Variável para armazenar o caminho digitado pelo usuário

    printf("Digite o caminho da pasta: "); // Solicita ao usuário a pasta a ser listada
    scanf("%s", caminho); // Lê o caminho digitado

    listar_pasta(caminho, 0); // Chama a função de listagem com o nível inicial 0

    return 0; // Fim do programa
}
