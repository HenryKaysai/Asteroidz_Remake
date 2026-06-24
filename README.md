# ASTEROIDZ REMAKE

### Trabalho final - INF01202 - Algoritmos e Programação

### Autores: Henrique Macedo Frandoloso e Paulo Rangel Schreiner

## Como jogar

#### Controles do jogo:
W: Acelera a nave
A, D: Rotaciona a imagem para a esquerda / direita
Espaço: Dispara um projétil
Esc: Retorna ao menu

Para jogar, basta incluir na pasta /fases arquivos seguindo o formato nivel_X.txt, onde X é um número inteiro. 
O conteúdo deve seguir o formato:
```
N, 400, 300, 0, 0
A, 100, 100, 2, 2
A, 800, 200, -1, 3
A, 300, 700, 3, -1
```

Onde N representa a N e A um asteróide e as colunas representam, respectivamente,
a coordenada X, a coordenada Y, a velocidade X e a velocidade Y. 

Assim, o jogo carregará essas fases e gerará consecutivamente.
Você tem 3 vidas. Cada vez que um asteroide colide com sua nave, você perde uma vida.
Você pode destruir asteroides atirando neles.

Se você completar as fases sem perder as 3 vidas, você vence!
Se perder as três vidas, é Game Over. 
Sua pontuação é calculada com base nos asteroides que você destroi e nas vidas que você perde.
Há também um bônus de pontuação em caso de vitória dentro do tempo ideal. 
Esse tempo ideal é de 2 segundos vezes a quantidade de asteróides. 

Em qualquer momento do jogo, você pode salvar seu progresso pausando, indo em Save e selecionando um slot.
No futuro, para carregar essa save, escolha Load no Main menu e selecione o slot correspondente. 

## Estrutura do código

O projeto está organizado da seguinte forma:

```
saves/   # contém as saves dos 8 slots (em arquivos .bin) e também o ranking (best_score.bin)
sound/   # contém os arquivos .wav de som
sprites/ # contém os sprites (arquivos .png)
include/ # contém as bibliotecas externas utilizadas (como raylib)
fases/   # como dito anteriormente, contém os arquivos .txt das fases
main     # arquivo binário executável para linux (gerado após compilação)
main.c   # arquivo orquestrador do programa. contém o loop principal 
functions.c  # contém todas definicoes de funcoes
prototypes.h # arquivo header que contém todas structs, constantes e protótipos
sound.c      # arquivo auxiliar com o carregamento do som
textures.c   # arquivo auxiliar com o carregamento das texturas (sprites)
```
