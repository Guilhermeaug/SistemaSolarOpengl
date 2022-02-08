#include <gl/glew.h>
#include <gl/freeglut.h>
#include <stdbool.h>

#define PLANETAS 10
#define ESCALA 0.000002

typedef struct Planeta {
    char nome[50];
    bool isSatelite;
    bool hasSatelite;
    int satelite;
    GLdouble raioImaginario;
    GLdouble raioReal;
    GLfloat xImaginario;
    GLfloat x, y, z;
    GLfloat anguloRotacao;
    GLfloat velocidadeRotacao;
    GLfloat anguloTranslacao;
    GLfloat velocidadeTranslacaoCirculo;
    GLfloat velocidadeTranslacaoElipse;
    GLfloat semiEixoMaior;
    GLfloat semiEixoMenor;
    GLfloat foco;
} Planeta;

static Planeta planetas[] = {
        {"Sol",      false, false, -1,
                                       5.0f, 696340 * ESCALA *
                                             0.045,           0.0f,  0.0f,      0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f,  0.0f,     0.0f,     0.0f},
        {"Mercurio", false, false, -1, 3.5f, 2440.0 *
                                             ESCALA,          10.0f, 0.39f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.01f, 0.3870f,  0.3788f,  0.0796f},
        {"Venus",    false, false, -1, 3.0f, 6052.0 *
                                             ESCALA,          20.0f, 0.723f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 3.0f, 0.01f, 0.7219f,  0.7219f,  0.0049f},
        {"Terra",    false, true,  9,  2.5f, 6371.0 *
                                             ESCALA,          30.0f, 1.0f,  0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.01f, 1.0027f,  1.0025f,  0.0167f},
        {"Marte",    false, false, -1, 2.0f, 3390 *
                                             ESCALA,          40.0f, 1.524f,  0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.01f, 1.5241f,  1.5173f,  0.1424f},
        {"Jupiter",  false, false, -1, 2.5f, 69911 *
                                             ESCALA,          50.0f, 5.203f,  0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.01f, 5.2073f,  5.2010f,  0.2520f},
        {"Saturno",  false, false, -1, 3.5f, 58232 *
                                             ESCALA,          60.0f, 9.539f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.01f, 9.5590f,  9.5231f,  0.5181f},
        {"Urano",    false, false, -1, 2.0f, 25362 *
                                             ESCALA,          70.0f, 19.18f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.01f, 19.1848f, 19.1645f, 0.9055f},
        {"Netuno",   false, false, -1, 3.5f, 24622 *
                                             ESCALA,          80.0f, 30.06f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 3.0f, 0.01f, 30.0806f, 30.0788f, 0.2587f},
        {"Lua",      true,  false, -1, 1.5f, 1737.0 * ESCALA, 5.0f, 0.99986f /
                                                                     6,         0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 3.0f, 0.01f},
};

void atualizaPlaneta(Planeta *planeta, bool orbitaCircular);