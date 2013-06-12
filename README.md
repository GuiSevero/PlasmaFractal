Computação Evolutiva - Trabalho #2
=========
## UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
#### INF01037 - Computação Evolutiva (Dante Barone).
---------------
- André Gonçalves
- Guilherme Severo
- Jean Lima



## Implementação de um fractal para geração de céu nublado
### O algoritmo
O trabalho desenvolvido foi um programa baseado no algoritmo de fractal de plasma 
para gerar texturas semelhantes as nuvens que encontramos no céu nublado.
O algoritmo de plasma se baseia num grid quadrado onde cada ponta possui um valor 
de cor. 

1. Dado um grid e as cores de cada vértice, verificar se ele pode ser subdividido em 4 
subgrids iguais, se sim, ir para 2, caso contrário ir para 6.

2. Calcular pontos que serão as metades de cada aresta do grid;

3. Calcular a cor(a média) de cada ponto criado baseado nas cores dos pontos da 
aresta;

4. Gerar um quinto ponto, no centro do grid, sua cor será a média de todas as arestas;

5. Chamar a função recursivamente a função para cada subgrid passando como 
parâmetro os pontos de cada subgrid e suas cores;

6. Calcular o ponto central do subgrid e sua cor e desenhar o ponto.
Para a implementação, em especial, do gerador de nuvens, as cores dos vértices 
iniciais foram geradas aleatóriamente, vale destacar também que a imagem final será em tons 
de cinza. Também foi aplicado o conceito de rugosidade para gerar as nuvens, mais suaves ou 
não;

Dependências
** C++ Compiler - http://www.bloodshed.net/devcpp.html
** OpenGL - http://www.opengl.org/
** Glut Toolkit - http://www.opengl.org/resources/libraries/glut/

Resultados:

![Figura 01](images/figura01.gif "Figura 01")
![Figura 02](images/figura02.gif "Figura 02")
![Figura 03](images/figura03.gif "Figura 03")


Bibliografia:
http://www.ic.sunysb.edu/Stu/jseyster/plasma/

Algoritmo para Gerar o Plasma
------
```c
/*
  Função que aplica o algoritmo do Fractal de Plasma
  Recebe as cores dos quatro pontos e os quatro pontos
  Calcula os quatro novos grids, analisa se pode ser subdividido
  Se pode ser subdividido, chama recursivamente, caso contrário é pintado o ponto na tela
*/
void generateFourSubGrids(float colorLeftBottom,float colorLeftUp,float colorRightUp,float colorRightBottom, float leftBottom[2], float leftUp[2], float rightUp[2], float rightBottom[2]) {
  
   if (distanceBetweenTwoPoints(leftBottom,leftUp) > 1.0f) {
       float newColorLeft, newColorUp, newColorRight, newColorBottom, newColorCenter ;
   	   float middleLeft[2], middleUp[2], middleRight[2], middleBottom[2], centerPoint[2];
 
 	   //calcula as novas cores dos novos pontos
 	   newColorLeft = (colorLeftBottom+colorLeftUp)/2.0f;
   	   newColorUp = (colorLeftUp+colorRightUp)/2.0f;
   	   newColorRight = (colorRightUp+colorRightBottom)/2.0f;
   	   newColorBottom = (colorRightBottom+colorLeftBottom)/2.0f;
	  
	   // calcula novos pontos dos subgrids
	   middleLeft[0] = (leftBottom[0]+leftUp[0])/2.0f;
	   middleLeft[1] = (leftBottom[1]+leftUp[1])/2.0f;
 
	   middleUp[0] = (leftUp[0]+rightUp[0])/2.0f;
	   middleUp[1] = (leftUp[1]+rightUp[1])/2.0f;
	 
	   middleRight[0] = (rightUp[0]+rightBottom[0])/2.0f;
	   middleRight[1] = (rightUp[1]+rightBottom[1])/2.0f;
	 
	   middleBottom[0] = (rightBottom[0]+leftBottom[0])/2.0f;
	   middleBottom[1] = (rightBottom[1]+leftBottom[1])/2.0f;
	 
	   centerPoint[0] = (leftBottom[0]+leftUp[0]+rightUp[0]+rightBottom[0])/4.0f;
	   centerPoint[1] = (leftBottom[1]+leftUp[1]+rightUp[1]+rightBottom[1])/4.0f;
 	   newColorCenter = (colorLeftBottom+colorLeftUp+colorRightUp+colorRightBottom)/4.0f;
 
      float rugosity;
      rugosity = (distanceBetweenTwoPoints(rightBottom, rightUp)/WIDTH)*0.3f;   
      float randAux;
      randAux = rand()%100;
      randAux = randAux / 100.0f;
      //Deixa a transição de nuvens mais suave, sem os grids ficarem marcados
      if (randAux > 0.5f)
 	      rugosity = rugosity * -1.0f;
   
      newColorCenter += rugosity;
      
      //corrige possíveis erros
      if (newColorCenter < 0.0f) {
         newColorCenter = 0.0f;
      }
      else {
		  if (newColorCenter > 1.0f) {
	         newColorCenter = 1.0f;
	      }
	  }
 
      generateFourSubGrids(newColorLeft,colorLeftUp,newColorUp,newColorCenter,middleLeft,leftUp,middleUp,centerPoint);
      generateFourSubGrids(newColorCenter,newColorUp,colorRightUp,newColorRight,centerPoint,middleUp,rightUp,middleRight);
      generateFourSubGrids(colorLeftBottom,newColorLeft,newColorCenter,newColorBottom,leftBottom,middleLeft,centerPoint,middleBottom);
      generateFourSubGrids(newColorBottom,newColorCenter,newColorRight,colorRightBottom,middleBottom,centerPoint,middleRight,rightBottom);
   }
   else {
   		float centerPoint[2];
		float newColorCenter = (colorLeftBottom+colorLeftUp+colorRightUp+colorRightBottom)/4.0f;   
	   	centerPoint[0] = (leftBottom[0]+leftUp[0]+rightUp[0]+rightBottom[0])/4.0f;
	    centerPoint[1] = (leftBottom[1]+leftUp[1]+rightUp[1]+rightBottom[1])/4.0f;   

      glColor3f(newColorCenter, newColorCenter, newColorCenter);
      glBegin(GL_POINTS);
         glVertex2f(centerPoint[0],centerPoint[1]);
      glEnd();   

    }
}

```
