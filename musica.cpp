#include <irrKlang.h>

using namespace irrklang;

#pragma comment(lib, "lib/irrKlang.a")

extern "C" void tocarMusica();

ISoundEngine *SoundEngine = createIrrKlangDevice();

void tocarMusica() {
    SoundEngine->play2D("recursos/star-wars.mp3", true);
}