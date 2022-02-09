# Sistema Solar

## Integrantes
* Diogo Emanuel Antunes Santos (20213002091)
* Guilherme Augusto de Oliveira (20213006564)
* Luiz Eduardo Leroy Souza (20213002126)
* Mateus Ribeiro Ferraz (20213001530)
* Victor Samuel Levindo Mont'Mor (20213005191)

## Instruções para compilação/execução
Foram utilizadas as seguintes bibliotecas para o desenvolvimento do projeto:
* Freeglut (versão pré-compilada para mingw)
* Glew
* SOIL
* Irrklang versão 1.5.0 para reproduzir sons

É necessário ter um compilador que suporte a linguagem C++ e que suporte a biblioteca Freeglut.
Lembre-se de manter os arquivos .dll no seu diretório de compilação, além dos includes necessários para cada biblioteca
ou o arquivo .lib dos mesmos no diretorio do compilador.

Em relação à biblioteca irrklang, deixarei a dll do mesmo no diretório do projeto, com a pasta include e o arquivo .lib.
Garanta que o compilador esteja linkado com a biblioteca irrklang.

Por fim, lembre-se de manter a pasta recursos no diretorio do executável. O projeto foi desenvolvido utilizando o software Clion.
O mesmo usa o arquivo CMakeLists.txt. Desse modo, caso utilize tal ‘software’ ou outro que use o arquivo cmake, será mais fácil a configuração.

Para compilar o programa:
```c++ -std=c++11 main.c musica.cpp planeta.c textura.c utils.c -o main -lSOIL -lfreeglut -lopengl32 -g```  

## Lista de itens adicionais implementados

Além da cena base, o projeto conta com os seguintes extras:

* **Satélite natural** a cena conta com um satelite natural ao redor da Terra;
* **Orbitas não circulares** a cena conta com uma forma de órbita não circular que pode ser ativada/desativada;
* **Reshape** quando a tela é redimensionada, a razao entre o tamanho da tela e o tamanho da imagem é mantida;
* **Música** a cena conta com a música tema do Star Wars
* **Fidedignidade** existe um modo de fidedignidade, em que a distância dos planetas em relação ao sol
é dada em unidades astrônomicas e o raio dos planetas é dado em km. É possível desativar esse modulo.

## Desenvolvimento
Pontos importantes:
* o programa conta com variaveis globais para ajustar opções da cena
* algumas funções de utilidade foram implementadas utilizando como base o código disponível no github do professor
* o sistema de luz e câmera também foi baseado em um módulo disponível como exemplo

No arquivo planeta.h está definida uma struct Planeta, que contém variaveis uteis para a criação do sistema solar e para
a escolha do modo de visualização. Existem variaveis para indicar se o planeta possui satelite e indicar qual planeta é seu satelite.
Também existem dois tipos de variaveis, as imaginárias e as reais.
As variaveis imaginária não são valores reais do sistema solar, mas são boas escolhas
para facilitar a visualização da cena. As variaveis reais estão baseadas em dados concretos disponíveis nas referências.

Ao utilizar os valores reais da galáxia, os planetas ficavam com valores muito grandes.
Assim, foi necessário utilizar uma escala para diminuir tais valores. O sol precisou ser diminuido ainda mais, tendo em vista seu raio imenso.

Para calcular as orbitas elipticas foram utilizadas equações paramétricas disponibilizadas nas referências.
Trata-se de um estudo publicado em um jornal de ciência da India. Todos os valores estão disponibilizados no documento, como
as equações para x e y, além dos valores dos semi-eixos e dos focos.

## Fontes
Para a criação do sistema solar, foram utilizadas as seguintes referências:
* [Mathematically Describing Planetary Orbits in Two Dimensions](https://www.hilarispublisher.com/open-access/mathematically-describing-planetary-orbits-in-two-dimensions-2168-9679-1000414.pdf)
* [Lista de objetos do Sistema Solar por tamanho](https://pt.wikipedia.org/wiki/Lista_de_objetos_do_Sistema_Solar_por_tamanho)
* [Aula 29: OpenGL Legacy - Posicionando a Fonte de Luz(Light Position )](https://www.youtube.com/watch?v=Za4ghaBaCec)
* [Aula Prática 6 (Visualização 3D em OpenGL)](https://www.inf.pucrs.br/~manssour/CG/pratica6/index.html)
* [Audio](https://learnopengl.com/In-Practice/2D-Game/Audio)
* [How to mix C and C++](https://isocpp.org/wiki/faq/mixing-c-and-cpp)


