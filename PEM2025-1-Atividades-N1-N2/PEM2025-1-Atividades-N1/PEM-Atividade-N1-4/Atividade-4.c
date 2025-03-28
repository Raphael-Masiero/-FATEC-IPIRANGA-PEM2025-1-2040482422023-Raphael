#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

// Fun��o recursiva para explorar diret�rios
void explorar_diretorio(const char *caminho, int nivel) {
    struct dirent *entrada;
    DIR *diretorio = opendir(caminho);

    if (diretorio == NULL) {
        fprintf(stderr, "Erro ao abrir diret�rio '%s': %s\n", caminho, strerror(errno));
        return;
    }

    while ((entrada = readdir(diretorio)) != NULL) {
        // Ignorar os diret�rios especiais "." e ".."
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        // Imprimir com recuo proporcional ao n�vel de profundidade
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("|- %s\n", entrada->d_name);

        // Construir novo caminho para subdiret�rios
        char novo_caminho[1024];
        if (snprintf(novo_caminho, sizeof(novo_caminho), "%s/%s", caminho, entrada->d_name) >= sizeof(novo_caminho)) {
            fprintf(stderr, "Erro: Caminho muito longo!\n");
            continue;
        }

        // Verificar se � um diret�rio e chamar recursivamente
        if (entrada->d_type == DT_DIR) {
            explorar_diretorio(novo_caminho, nivel + 1);
        }
    }
    closedir(diretorio);
}

int main(int argc, char *argv[]) {
    // Verificar se o caminho foi fornecido corretamente
    if (argc < 2 || argv[1] == NULL) {
        fprintf(stderr, "Erro: Caminho do diret�rio n�o foi fornecido.\n");
        return 1;
    }

    printf("Explorando diret�rio: %s\n", argv[1]);
    explorar_diretorio(argv[1], 0);
    return 0;
}
