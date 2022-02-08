#include "main.h"

/*******************************************************************************
 * Variaveis globais de controle
 ******************************************************************************/
GLfloat angle; // controle o angulo da camera
GLfloat fAspect; // controle o aspecto da camera
bool luz; // controle se a luz esta ligada ou nao
bool orbitaCircular; // controla qual modo de orbita esta sendo usado
int cameraSelecionada; // controla qual camera esta sendo usada
bool ativaRedimensionamento; // controla se existe um redimensionamento para facilitar a visualização no modelo real

/* Desenha os "planetas" satelities (so temos a lua) */
void desenhaPlanetaSatelite(int index) {
    // Declarando as variaveis necessarias para desenhar o planeta separadamente para evitar chamar planetas[index] sempre
    Planeta planeta = planetas[index];

    GLfloat anguloRotacao = planeta.anguloRotacao;

    GLfloat x = 0.0f;
    GLfloat y = planeta.y;
    GLfloat z = planeta.z;

    GLdouble raio = 0.0f;

    GLuint textura = texturas[index].id;

    if (orbitaCircular) {
        x = planeta.xImaginario;
        raio = planeta.raioImaginario;
    } else {
        x = planeta.x;
        raio = planeta.raioReal;
    }

    glBindTexture(GL_TEXTURE_2D, textura);

    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);
    // repare que a matriz anterior ainda esta ativa. Apenas estou multiplicando a matriz de translacao para que a lua fique uma pouco mais distante do planeta
    glTranslatef(x, y, z);

    glRotatef(90, 1.0f, 0.0f, 0.0f);

    solidSphere(raio, FATIAS, PILHAS);
}

/* Desenha cada planeta */
void desenhaPlaneta(int index) {
    // Declarando as variaveis necessarias para desenhar o planeta separadamente para evitar chamar planetas[index] sempre
    Planeta planeta = planetas[index];

    GLfloat anguloRotacao = planeta.anguloRotacao;
    GLfloat anguloTranslacao = planeta.anguloTranslacao;
    GLfloat x = planeta.x;
    GLfloat y = planeta.y;
    GLfloat z = planeta.z;
    GLdouble raio = 0.0f;
    GLdouble semiEixoMaior = planeta.semiEixoMaior;
    GLdouble semiEixoMenor = planeta.semiEixoMenor;
    GLfloat foco = planeta.foco;

    GLuint textura = texturas[index].id;

    if (orbitaCircular) {  // caso seja orbita circular, utilizo os valores imaginarios
        x = planeta.xImaginario;
        raio = planeta.raioImaginario;
    } else { // na orbita eliptica utiliza os valores reais
        x = planeta.x;
        raio = planeta.raioReal;
    }

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, textura);

    if (index != 0) { // não considera o sol

        if (orbitaCircular) {
            glRotatef(anguloTranslacao, 0.0f, 1.0f, 0.0f); // roda em circulo
        }

        if (luz) {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
        } else {
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
        }
    } else {
        // Ao desenhar o sol é necessario desabilitar a luz, pois caso contrario o sol firaca na mesma posicao da luz e apagado
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    // em orbita circular o planeta permance na mesma posicao e apenas rotaciona
    // no caso so sol sempre estara no mesmo local
    if (index == 0 || orbitaCircular) {
        glTranslatef(x, y, z);
    } else if (!orbitaCircular) { // roda em uma orbita eliptica
        glTranslated(-semiEixoMaior * sin(anguloTranslacao) - foco,
                     -semiEixoMenor * cos(anguloTranslacao), 0.0f);
    }

    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);

    if (ativaRedimensionamento && !orbitaCircular) {
        if (index != 0 && index != 6 && index != 7 && index != 5) {
            solidSphere(raio * 2, FATIAS, PILHAS);
        } else {
            solidSphere(raio / 2, FATIAS, PILHAS);
        }
    } else {
        solidSphere(raio, FATIAS, PILHAS);
    }

    if (planeta.hasSatelite) { // se o planeta tiver um satelite (apenas a Terra)
        desenhaPlanetaSatelite(planeta.satelite);
    }

    glPopMatrix();
}

/* Funcao de display do opengl */
void desenha() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    especificaParametrosVisualizacao(); // recarregando a perspectiva da camera

    for (int i = 0; i < PLANETAS; i++) { // para cada planeta, chama a funcao desenhaPlaneta()
        if (!planetas[i].isSatelite) {  // planetas satelites sao desenhadas dentro da funcao que desenha o planeta pai
            desenhaPlaneta(i);
        }
    }

    glTranslatef(0.0f, 0.0f, 0.0f); // retornando a origem do sistema de coordenadas para desenhar a luz

    GLfloat posicaoLuz[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // especifica os parametros de uma luz pontual
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz); // posicao da luz branca

    glutSwapBuffers();
}

/* Atualiza os angulos de rotacao/translacao dos planetas */
void atualizacao() {
    for (int i = 0; i < PLANETAS; i++) {
        atualizaPlaneta(&planetas[i], orbitaCircular);
    }

    especificaParametrosVisualizacao();
    glutPostRedisplay();
    glutTimerFunc(30, atualizacao, 0);
}

/* Inicializa as variaveis globais e a iluminacao/materiais do opengl */
void inicializa() {
    angle = 45.0f;
    luz = true;
    cameraSelecionada = 0;
    orbitaCircular = false;
    ativaRedimensionamento = false;

    tocarMusica();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Propriedades do material
    GLfloat ambiente[4] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat difusa[4] = {0.7f, 0.7f, 0.7f, 0.7f};
    GLfloat especularidade[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat especMaterial = 80.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMaterialf(GL_FRONT, GL_SHININESS, especMaterial);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Iluminação e sombra

    GLfloat luzAmbiente[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat luzDifusa[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat luzEspecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat globalAmbiente[4] = {0.1f, 0.1f, 0.1f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbiente);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    for (int i = 0; i < TEXTURAS; i++) {
        texturas[i].id = carregaTextura(texturas[i].arquivo);
    }
}

/* Responsavel por limpar a matriz de exibicao e iniciar a projecao perspectiva */
void especificaParametrosVisualizacao() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (cameraSelecionada == 0) {

        if (orbitaCircular) {
            gluLookAt(0.0f, 100.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        } else {
            gluLookAt(0.0f, 2.5f, -2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        }

    } else {

        if (orbitaCircular) {
            gluLookAt(0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        } else {
            gluLookAt(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        }

    }
}

/* Mantem a razão de aspecto ao redimensioanr a janela */
void alteraTamanhoJanela(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    fAspect = (GLfloat) w / (GLfloat) h;
    especificaParametrosVisualizacao();
}

/* Gerencia input de mouse */
void gerenciaMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-in
            if (angle >= 10) angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-out
            if (angle <= 130) angle += 5;
        }

    especificaParametrosVisualizacao();
    glutPostRedisplay();
}

/* Troca entre as duas cameras disponiveis */
void mudarCamera() {
    if (cameraSelecionada == 0) {
        cameraSelecionada = 1;
    } else {
        cameraSelecionada = 0;
    }
}

/* Ativa ou desativa a iluminacao */
void toggleLuz() {
    if (luz) {
        glDisable(GL_LIGHTING);
        luz = false;
    } else {
        glEnable(GL_LIGHTING);
        luz = true;
    }
}

/* Ativa ou desativa um aumento/diminuicao artificial do modelo real*/
void redimensionamento() {
    ativaRedimensionamento = !ativaRedimensionamento;
}

/* Alterna entre os modos de orbita */
void toggleOrbita() {
    orbitaCircular = !orbitaCircular;

    if (orbitaCircular) {
        angle = 45;
    } else {
        angle = 20;
    }
}

/* Gerencia input de teclado */
void observadorTeclas(unsigned char key, int x, int y) {
    switch (key) {
        case 99:
            mudarCamera();
            break;
        case 108:
            toggleLuz();
            break;
        case 111:
            toggleOrbita();
            break;
        case 102:
            redimensionamento();
            break;
        default:
            break;
    }

    especificaParametrosVisualizacao();
    glutPostRedisplay();
}

/* Printa no console os comandos da cena */
void comandosDisponiveis() {
    printf("**************************************************************\n");
    printf("Comandos disponiveis:\n");
    printf("\t'c' - Mudar de camera\n");
    printf("\t'l' - Ativar/Desativar iluminacao\n");
    printf("\t'o' - Alternar entre modos de orbita\n");
    printf("\t'f' - Alternar entre modos de redimensionamento\n");
    printf("*************************************************************\n");
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    comandosDisponiveis();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 720);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Sistema Solar");

    glutTimerFunc(30, atualizacao, 0);

    glutDisplayFunc(desenha);
    glutMouseFunc(gerenciaMouse);
    glutKeyboardFunc(observadorTeclas);
    glutReshapeFunc(alteraTamanhoJanela);

    inicializa();
    glutMainLoop();

    return 0;
}
