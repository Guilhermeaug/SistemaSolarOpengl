#include <gl/glew.h>
#include <gl/freeglut.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "utils.h"
#include "planeta.h"
#include "textura.h"

void especificaParametrosVisualizacao();

void desenha();

void inicializa();

void gerenciaMouse(int button, int state, int x, int y);

void alteraTamanhoJanela(GLsizei w, GLsizei h);

void mudarCamera();

void atualizacao();

void desenhaPlanetaSatelite(int index);

void desenhaPlaneta(int index);

void toggleLuz();

void toggleOrbita();

void redimensionamento();

void observadorTeclas(unsigned char key, int x, int y);

void comandosDisponiveis();

void tocarMusica(); // Função para tocar a música do arquivo c++