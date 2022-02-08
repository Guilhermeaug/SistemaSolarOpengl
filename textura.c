#include "textura.h"

/*Carrega uma textura utilizando SOIL. Disponível no github do professor*/
GLuint carregaTextura(const char* caminho) {
    GLuint idTextura = SOIL_load_OGL_texture(
            caminho,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
    );

    if (idTextura == 0) {
        printf("Erro ao carregar textura: %s\n", SOIL_last_result());
        exit(1);
    }

    return idTextura;
}
