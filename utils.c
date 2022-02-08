#include "utils.h"

/*Desenha uma esfera utilizando solido glu. Função retirada de um dos exemplos disponíveis no github do professor*/
void solidSphere(GLdouble raio, int fatias, int pilhas) {
    GLUquadric *quadObj = gluNewQuadric();
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, raio, fatias, pilhas);
    gluDeleteQuadric(quadObj);
}