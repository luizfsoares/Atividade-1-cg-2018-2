#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	
	
	//TESTE DOS PIXELS
	/*PutPixel(255,255, orange);
	PutPixel(255,256, orange);
	PutPixel(130,130, white);
	PutPixel(130,131, white);
	PutPixel(338,338, purple);
	PutPixel(338,339, purple);
	PutPixel(470,470, red);
	PutPixel(470,471, red);
	PutPixel(190,190, green);
	PutPixel(190,191, green);
	PutPixel(60,61, blue);
	PutPixel(60,60, blue);*/
	
	
	
	
//TESTES DOS OCTANTES
/*DrawLine(255, 255, 512, 255, red, blue); 
DrawLine(255, 255, 512, 512, white, orange); 
DrawLine(255, 255, 255, 512, red, blue);
DrawLine(255, 255, 0, 512, orange, blue);
DrawLine(255, 255, 0, 255, red, white);
DrawLine(255, 255, 0, 0, green, blue);
DrawLine(255, 255, 255, 0, white, yellow);
DrawLine(255, 255, 512, 255, red, blue);
DrawLine(255, 255, 512, 0, yellow, purple);*/



//TRIANGULOS DESENHADOS
//DrawTriangle(255, 255, red, 255, 0, blue, 512, 255, white);
//DrawTriangle(255, 255, blue, 255, 512, green, 0, 255, orange);






//CUBO DESENHADO
/*DrawLine(150, 170, 150, 296, red, blue);
DrawLine(150, 170, 276, 170, red, blue);
DrawLine(150, 296, 276, 296, red, blue);
DrawLine(276, 170, 276, 296, red, blue);
DrawLine(213, 233, 338, 233, red, blue);
DrawLine(338, 233, 338, 108, red, blue);
DrawLine(338, 108, 213, 108, red, blue);
DrawLine(213, 108, 213, 233, red, blue);
DrawLine(150, 296, 213, 233, red, blue);
DrawLine(150, 170, 213, 108, red, blue);
DrawLine(276, 170, 338, 108, red, blue);
DrawLine(276, 296, 338, 233, red, blue);*/


}




//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}


