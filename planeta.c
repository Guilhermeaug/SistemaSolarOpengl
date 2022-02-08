#include "planeta.h"

// a cada iteracao atualiza os angulos de rotacao e translacao
void atualizaPlaneta(Planeta *planeta, bool orbitaCircular) {
    planeta->anguloRotacao += planeta->velocidadeRotacao;
    if (planeta->anguloRotacao > 360.0f)
        planeta->anguloRotacao = 0.0f;

    if (orbitaCircular) {
        planeta->anguloTranslacao += planeta->velocidadeTranslacaoCirculo;
    } else {
        planeta->anguloTranslacao += planeta->velocidadeTranslacaoElipse;
    }

    if (planeta->anguloTranslacao > 360.0f)
        planeta->anguloTranslacao = 0.0f;
}