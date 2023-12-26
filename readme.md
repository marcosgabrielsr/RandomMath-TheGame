**Autor: Marcos gabriel** <br>
**Data da última atualização:** 26/12/2023

## Descrição
Este projeto é um jogo de resolução de equações matemáticas referente às quatro operações matemáticas básicas. Netes jogo, são geradas expressões matemáticas aleatórias e são disponibilizadas três respostas a qual deve ser escolhida a correta para então ser dada outra expressão e assim por diante.

Acredito que o que pode chamar atenção para este projeto é a barra de tempo onde utilizandos a função `map` do arduino e o `.drawLine` e `.drawRect` da biblioteca `Adafruit_GFX`, é interessante também salientar o quão desafiador pode ser e os benefícios que este jogo pode trazer, como por exemplo, melhora do foco, atenção e racícionio rápido para expressões matemáticas.

Por fim, gostaria de salientar que mais para frente gostaria de aplicar uma nova mecânica mais interessante e mais desafiodora, se tiver algo em mente, por favor faça bifurcações no projeto ou entre em contato comigo, ficarei muito feliz em receber novas ideias para melhorar este projeto.

**OBS:** A IDE para criação do projeto é o PlatformIO e são apenas aceitos números inteiros para as expressões. Exemplo, neste jogo a expressão `(1 * 5) / 7 = 0`.

## Circuito Eletrônico
<img src="https://cdn.discordapp.com/attachments/1153711382336909332/1163203943237689404/image.png?ex=653eb917&is=652c4417&hm=aafb61461d30b2c1abee0a6c10e71c59c9cdcf73e34c3c1c1630b3395ad9d880&" />

## Funcionalidades
Aqui serão explicadas as funções que permitem o funcionamento do jogo.

1. `initScreen`:
Esta função desenha a tela inicial do jogo no display Nokia 5110.
Mostra o título do jogo ("Random Math") e uma mensagem para pressionar o botão "X" para iniciar.
A mensagem "Press (x) to start!" pisca a cada 400 milissegundos.
O estado do botão "X" é verificado para determinar se o jogo deve começar.

2. `navegation`:
Atualiza a posição do cursor de seleção de opção com base nos cliques dos botões esquerdo (btnL) e direito (btnR).
A posição inicial e os cliques dos botões determinam a nova posição do cursor.
A função retorna a nova posição do cursor.

3. `setOperation`:
Recebe dois operandos (x e y) e um operador (op) como entrada.
Realiza a operação matemática correspondente ao operador.
Retorna o resultado da operação.

4. `getResultAndEquation`:
Gera valores aleatórios para operandos (x, y, z) e operadores (op1, op2).
Garante que os operandos não sejam zero.
Calcula o resultado de duas operações consecutivas.
Retorna uma string representando a equação gerada.

5. `drawRectEquation`:
Desenha um retângulo ao redor da equação no display.
Escreve a equação dentro do retângulo.

6. `gameScreen`:
Esta função representa a lógica principal do jogo.
Dentro de um loop, atualiza o display com informações sobre o tempo restante e a equação atual.
Gera uma nova equação quando necessário.
Permite ao jogador escolher entre três opções e verifica se a escolha está correta.
Atualiza continuamente o display até que o tempo se esgote.

## Referências
Caso fique interessado em entender mais sobre a classe de pushbuttons acesse o link https://github.com/marcosgabrielsr/ClassePushButton.

O material de apoio para utilização da biblioteca podem ser encontrados no seguinte link https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display.