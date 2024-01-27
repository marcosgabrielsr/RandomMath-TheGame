//Incluindo biblioteca de configurações do projeto
#include "configs.h"

//Função que desenha a tela inicial do jogo
void initScreen(Adafruit_PCD8544 &display, PushButton &btnX, bool *start){
    //Variável para controle de tempo do intervalo de aparaição da mensagem de start
    static bool print = true;
    static unsigned long t = 0;

    //Limpando display
    display.clearDisplay();

    //Desenhando retângulo
    display.drawRect(0, 0, 84, 48, BLACK);

    //Configurando texto
    display.setCursor(8, 5);
    display.setTextColor(BLACK);
    display.setTextSize(2);

    //Imprimindo título do jogo
    display.print("Random");

    display.setCursor(18, 18);
    display.print("Math");

    //Verifica se se passou um intervalo de x milisegundos
    if((millis() - t) >= 400){
        print = !print;
        t = millis();
    }
    
    //Escrevendo a mensagem
    display.setCursor(3, 37);
    display.setTextSize(1);
    (print) ? display.println("(x) to start!") : display.println();

    //Verifica o clique do botão para iniciar o jogo
    if(btnX.clickButton())
        *start = !(*start);

    //Atualizando display
    display.display();
}

//Função que recebe a posição atual do cursor de seleção de opção e atualiza de acordo
//com os cliques dos botões
int8_t navegation(PushButton &btnL, PushButton &btnR, int8_t pos){
    //Pega a posição inicial
    int p = pos;

    //Verifica se a posição atual não é a última da direita e se o btnR foi clicado
    if(p < 2 && btnR.clickButton())
        p += 1;
    
    //Verifica se a posição atual não é a última da esquerda e se o btnL foi clicado
    else if(p > 0 && btnL.clickButton())
        p -= 1;
    
    return p;
}

//Função que executa uma operação com os valores passados por parâmetros e retorna o resultado
int setOperation(int8_t op, int x, int y){
    switch (op){
        case 0: return x + y;
        case 1: return x - y;
        case 2: return x * y;
        case 3: return x / y;

        default: return 0;
    }
}

//Função que gera os valores e as operações
String getResultAndEquation(int *result){
    //Declarando variáveis
    int x = 0, y = 0, z = 0;
    int8_t op1 = random(0, 4), op2 = random(0, 4);
    char simbols[4] = {'+', '-', 'x', '/'};

    //Para evitar que exista algum valor que possua zero
    while(x == 0 || y == 0 || z == 0){
        x = random(0, 11);
        y = random(0, 11);
        z = random(0, 11);
    }

    *result = setOperation(op1, x, y);
    *result = setOperation(op2, *result, z);

    return "(" + String(x) + simbols[op1] + String(y) + ") " + simbols[op2] + " " + String(z);
}

//Função que desenha o retângulo com a equação
void drawRectEquation(Adafruit_PCD8544 &display, String equation){
    //Desenhando retângulo caixa e escrevendo expressão matemática
    display.drawRect(5, 2, 77, 12, BLACK);
    
    //Configurando posição, tamanho e cor do texto
    display.setCursor(7, 5);
    display.setTextColor(BLACK);
    display.setTextSize(1);

    //Escrevendo equação
    display.println(equation);
}

//Função que desenha a tela do jogo
void gameScreen(Adafruit_PCD8544 &display, PushButton &btnL, PushButton &btnX, PushButton &btnR){
    //Variáveis para controle de tempo
    unsigned long t = millis();
    int result, pontos = 0;
    int8_t y0, pos = 0, values[3];
    bool right = true;
    String equation = " ";

    while(right){
        //Limpando display
        display.clearDisplay();

        //Desenhando barra de tempo
        display.drawRect(0, 2, 3, 44, BLACK);

        //Atualizando a barra de tempo
        y0 = map((millis() - t), 0, 90000, 3, 44);

        //Verifica se a barra de tempo não chegou ao fim
        if(y0 < 44)
            //Desenha a linha para o tempo
            display.drawLine(1, y0, 1, 44, BLACK);
        else
            right = false;

        //Armazenando resultado e a expressão matemática
        if(equation == " "){
            //Código para evitar que haja resultados maiores que 100
            do{
                equation = getResultAndEquation(&result);
            } while(result > 100);

            //Código para impedir que haja duas opções com o resultado correto
            int8_t i = 0;
            while(i < 3){
                values[i] = random(-10, 11);

                if(values[i] != result)
                    i++;
            }

            //Escolhe uma posição aleatória do vetor values para receber o resultado
            values[random(0, 3)] = result;
        }

        //Desenhando o retângulo que cerca a equação e a equação
        drawRectEquation(display, equation);

        //Escrevendo os pontos
        display.setCursor(5, 22);
        display.print("pontos:");
        display.println(pontos);

        //Atualizando a posição do cursor
        pos = navegation(btnL, btnR, pos);

        //Desenhando botões com as determinadas posições
        int xR = 5, xL = 10;
        for(int i = 0; i < 3; i++){
            
            //Setnaod cursor para escrita das opções
            display.setCursor(xL, 37);

           //Verificando se o item a ser desenhado corresponde à posição do cursor 
            if(pos == i){
                display.fillRoundRect(xR, 34, 24, 12, 2, BLACK);
                display.setTextColor(WHITE);
                
            }else{
                display.drawRoundRect(xR, 34, 24, 12, 2, BLACK);
                display.setTextColor(BLACK);
            }

            //Setando tamanho da fonte
            display.setTextSize(1);

            //Verifica se o número tem apenas uma casa e se ele não tem o sinal negativo
            if(values[i] < 10 && values[i] >= 0)
                    display.print("0");
                
            display.println(values[i]);

            //Altera a posição x dos retângulos e dos valores das opções
            xR += 26;
            xL += 26;
        }

        //Verifica se o jogador apertou o buttonX na opção que tinha o resultado correto
        if(btnX.clickButton() && values[pos] == result){
            equation = " ";
            pontos += 1;
        }

        //Atualizando display
        display.display();
    }
}