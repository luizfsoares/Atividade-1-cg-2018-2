### Atividade-1-cg-2018-2
Rasterização de pontos e linhas.

### Trabalho realizado pelos alunos:

Augusto Henrique O. dos Anjos - Matrícula: 20170009919
Luiz Felipe Soares Cardoso - Matrícula: 20170000717

##Introdução

O trabalho realizado consiste na criação 3 funções que se baseiam no esquema de rasterização de pontos e linhas. A rasterização de linhas faz uso do Algoritmo de Bresenham que é mais eficiente em relação ao de DDA, pois otimiza o código e gera um custo menor de processamento, tendo em vista que se livra do uso de operações de arredondamento e com ponto flutuante.

##Implementação do código

Antes de tudo, foi necessário criar uma estrutura contendo as informações para cada cor utilizada, criando os campos para cada componente RGBA e em seguida a inicialização de cada cor, como será mostrado a seguir:

```c++
typedef struct {  
  unsigned char red; 
	unsigned char green; 
	unsigned char blue; 
	unsigned char alpha; 
}color;

color red = {255,0,0,255};
color green = {0,255,0,255};
color blue = {0,0,255,255};
```

##Função PutPixel

Não é possível acessar e modificar diretamente a memória de vídeo, entaõ aqui foi usdo uma simulação feita pelo 'FBptr'. Para ativar um pixel na tela simulada, foi-se criado uma função PutPixel que recebe como parâmetros, os componentes X e Y da posição do pixel que deseja ser ativado e uma cor. Primeiramente é feito a checagem para saber se a posição é válida, ou seja, se está dentro do tamanho da tela criada. Posteriormente, é calculado o 'Offset' que é o deslocamento em x e em y e em seguida atribui os valores aos campos da estrutura.

```c++
void PutPixel(int x, int y, color cores){

    if((x>=0) && (x<=512) && (y >=0) && (y <= 512)){
    
      int Offset = 4*x + 4*y* IMAGE_WIDTH;
	    FBptr[Offset + 0]= cores.red; 
	    FBptr[Offset + 1]= cores.green;
	    FBptr[Offset + 2]= cores.blue;
	    FBptr[Offset + 3]= cores.alpha;}
	
	else{
	    return;
	}	
}
```

FOTOOOOOOOOOOOOOOOOOOOOOO


##Função DrawLine

Esta função recebe as componentes X e Y de uma posição inicial e uma posição final, assim como as cores que serão interpolarizadas.

Os pontos inicial e final tratam de limitar a rasterização da linha que é feita com base no Algoritimo de Bresenham que ativa o próximo píxel com base em aproximações.

FOTOOOOOOOOOOOOOOOOOOOOOOOOOO

Este algoritimo é válido apenas para o primeiro octante, portanto é necessária a sua adaptação por meio de espelhamento para os demais octantes, como será mostrado a seguir:

```c++
void DrawLine(int xi, int yi, int xf, int yf, color corI, color corF){

int dx = xf - xi;
int dy = yf - yi;

if(dx < 0){ //3rd 4th 5th or 6th octant
  DrawLine(xf, yf, xi, yi, corF, corI);
}else{
	if(dy > 0){ //1st or 2nd octant
		if(abs(dx) > abs(dy)){ //1st octant
		  
			int d = 2 * dy - dx;
			int incr_e = 2 * dy;
			int incr_ne = 2 * (dy - dx);
			int x = xi;
			int y = yi;
			double dT = sqrt ((xf-xi) * (xf-xi) + (yf - yi) * (yf - yi)); 
			double dP;
			double p;
			PutPixel(x, y, corI);
			while (x < xf) {
			if (d <= 0) {
			d += incr_e;
			x++;
			} else {
			d += incr_ne;
			x++;
			y++;
			}
			dP = sqrt ((xf-x) * (xf-x) + (yf - y) * (yf - y));
			p = (dP/dT);
			cores = Interpolacao(p, corI, corF);
			PutPixel(x, y, cores);}
		}
    ...
```
O código dos demais octantes detalhado está na pasta cg_framework
 
  FOTOOOOOOOOOOOOOOOOOOO

Como foi dito na introdução, esta é a função mais importante que servirá de base para fazer as demais figuras geométricas, como por exemplo, o cubo que é mostrado a seguir:

FOTOOOOOOOOOOOOOOOOO

## DrawTriangle

Como já foi criado a função DrawLine, esta função se torna muito mais fácil, pois para a criação de um triângulo é necessário apenas realizar a chamada da função DrawLine três vezes, em que há vértices em comum. Ela recebe como parâmetro, as coordenadas dos três vertices, assim como as cores a serem interpolarizadas

```c++
void DrawTriangle(int x1, int y1, color cor1, int x2, int y2, color cor2, int x3, int y3, color cor3){
    
    DrawLine(x1,y1, x2, y2, cor1, cor2);
    DrawLine(x2, y2, x3, y3, cor2, cor3);
    DrawLine(x3, y3, x1, y1, cor3, cor1);
}
```
FOTOOOOOOOOOOOOOOOOOOOOOOOOOOOO

##Interpolação de Cores

Interpolar cores é uma técnica de renderização de sombras em objetos 3D, a qual se torna possível a variação de cores ao longo de uma mesma reta. A técnica começa a ser aplicada desde o primeiro pixel e para isso, é necessário calcular a distância total da reta e a distância parcial (distância que falta para chegar até o pixel final). Com essas duas distâncias, é possível o cálculo de uma taxa 'p', no qual será usada na fórmula do cálculo da cor do pŕoximo pixel a ser desenhado pelo algoritmo. Como a distância parcial varia, então o cálculo da taxa irá variar também e como a taxa, dentro da fórmula, determina a próxima cor, esta também sofrerá variação se aproximando cada vez mais da tonalidade da cor final.

```c++
color Interpolarizacao(double p, color corI, color corF){

      color newcolor;
	    newcolor.red = corI.red*p + (1-p)*corF.red;
    	newcolor.green = corI.green*p + (1-p)*corF.green;
    	newcolor.blue = corI.blue*p + (1-p)*corF.blue;
    	newcolor.alpha = corI.alpha*p + (1-p)*corF.alpha;

	return newcolor;
```

## Considerações finais

O objetivo inicial do trabalho foi alcançado, pois houve uma melhor compreensão do funcionamento do algoritmo de Bresenham, assim como de conceitos importantes para a computação gráfica e o avanço nesta disciplina.
Entre as principais dificuldades que foi encontrado, podem ser citados o espelhamento dos octantes, pois é um pouco confusa a adaptação dos cálculos das variáveis, portanto precisa de grande raciocínio. Além disso, o entendimento do código da interpolação foi bastante difícil. Após a compreensão, tudo fluiu melhor.

## Bibliografias utilizadas

http://letslearnbits.blogspot.com/2014/10/icgt1-interpolacao-de-cores.html (site explicando interpolação de cores).

-Slides disponibilizados pelo professor Cristhian Pagot.




