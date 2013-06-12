#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
 

// altura e comprimento maximo do seu quadrado inicial ou janela
#define WIDTH 1024
#define HEIGHT 600



float distanceBetweenTwoPoints(float firstPoint[2], float secondPoint[2]) {
   float result = sqrt((firstPoint[0]-secondPoint[0])*(firstPoint[0]-secondPoint[0]) + (firstPoint[1]-secondPoint[1])*(firstPoint[1]-secondPoint[1]));
   return result;
}

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

//Função que a openGL chamará
//Inicia as cores das pontas do grid aleatoriamente
void display(void) {
    
   float leftBottom[2], leftUp[2], rightUp[2], rightBottom[2];
   float colorLeftBottom, colorLeftUp, colorRightUp, colorRightBottom;
 
   srand(time(NULL));
   
   //Define os pontos limites da janela(grid inicial)
   leftBottom[0]=0.0f;
   leftBottom[1]=0.0f;
 
   leftUp[0]=0.0f;
   leftUp[1]=HEIGHT;
 
   rightUp[0]=WIDTH;
   rightUp[1]=HEIGHT;
 
   rightBottom[0]=WIDTH;
   rightBottom[1]=0.0f;
   
   //Gera aleatóriamente a cor de cada ponto limite
   colorLeftBottom = rand()%100;
   colorLeftBottom /= 100;
   colorLeftUp = rand()%100;
   colorLeftUp /= 100;
   colorRightUp = rand()%100;
   colorRightUp/= 100;
   colorRightBottom = rand()%100;
   colorRightBottom/= 100;
 
   glClearColor(1.0f,1.0f,1.0f,1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,WIDTH,0,HEIGHT);
 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   generateFourSubGrids(colorLeftBottom, colorLeftUp, colorRightUp, colorRightBottom, leftBottom, leftUp, rightUp, rightBottom);      
   glFlush();
}

 
int main(int argc, char** argv) {
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(WIDTH,HEIGHT);
   glutCreateWindow("Andre, Guilherme e Jean - Fractal de Plasma");
   glutInitWindowPosition(0,0);
   glutDisplayFunc(display);
   glutMainLoop();
 
   return 0;
}
