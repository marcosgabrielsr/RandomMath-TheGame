//Incluindo biblioteca de configurações do projeto
#include "configs.h"

//Mapeando hardware
//- Pinos do display:
#define pinCLK 3
#define pinDIN 4
#define pinDC 5
#define pinCE 6
#define pinRST 7
#define led 2

//- Pinos dos botões
#define pinButtonL 10
#define pinButtonX 9
#define pinButtonR 8

//-- Criando objetos
//- Display Nokia 5110:
Adafruit_PCD8544 display = Adafruit_PCD8544(pinCLK, pinDIN, pinDC, pinCE, pinRST);

//- PushButtons:
PushButton buttonL(pinButtonL, 170);
PushButton buttonX(pinButtonX, 170);
PushButton buttonR(pinButtonR, 170);

//Função para controlar o inicio do jogo
bool start = false;

void setup(){
  //Inicializando comunicação serial 
  Serial.begin(9600);

  //Inicializando display
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(A0));

  //Definindo pino led como saida e o desligando
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop(){
  if(!start)
    //Chamando função que desenha a tela inicial
    initScreen(display, buttonX, &start);
  
  else{
    //Chamando função que desenha a tela do jogo
    gameScreen(display, buttonL, buttonX, buttonR);
    start = false;
  }
}