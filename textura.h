#include <gl/glew.h>
#include <gl/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#define TEXTURAS 11
#define FATIAS 90
#define PILHAS 45

typedef struct Textura {
    GLuint id;
    char arquivo[50];
} Textura;

static Textura texturas[] = {
        {0, "recursos/sol.jpg"},
        {0, "recursos/mercurio.jpg"},
        {0, "recursos/venus.jpg"},
        {0, "recursos/terra.jpg"},
        {0, "recursos/marte.jpg"},
        {0, "recursos/jupiter.jpg"},
        {0, "recursos/saturno.jpg"},
        {0, "recursos/urano.jpg"},
        {0, "recursos/netuno.jpg"},
        {0, "recursos/lua.jpg"},
        {0, "recursos/nuvens-terra.jpg"},
};

GLuint carregaTextura(const char *caminho);