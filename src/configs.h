//Incluindo bibliotecas
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "PushButton.hpp"

//Função que desenha a tela inicial do jogo
void initScreen(Adafruit_PCD8544 &display, PushButton &btnX, bool *start);

//Função que desenha a tela do jogo
void gameScreen(Adafruit_PCD8544 &display, PushButton &btnL, PushButton &btnX, PushButton &btnR);