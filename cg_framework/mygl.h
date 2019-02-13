#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

typedef struct {  // unsigned determina apenas valores positivos
	unsigned char red; 
	unsigned char green; 
	unsigned char blue; 
	unsigned char alpha; 
}color;


color red = {255,0,0,255}; //Vermelho     intensidade de cada cor em cada componente do pixel
color green = {0,255,0,255};// Verde
color blue = {0,0,255,255};// Azul
color black = {0,0,0,255};// Preto
color white = {255,255,255,255};// Branco
color orange = {205, 127, 50, 255};// Laranja
color purple = {153, 50, 205, 255};// Roxo
color yellow = {255, 255, 0, 255};// Amarelo
color cores;


//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************


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

color Interpolarizacao(double p, color corI, color corF){

	    color newcolor;
	    newcolor.red = corI.red*p + (1-p)*corF.red;
    	newcolor.green = corI.green*p + (1-p)*corF.green;
    	newcolor.blue = corI.blue*p + (1-p)*corF.blue;
    	newcolor.alpha = corI.alpha*p + (1-p)*corF.alpha;

	return newcolor;
	

}

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
			double dT = sqrt ((xf-xi) * (xf-xi) + (yf - yi) * (yf - yi)); // distancia total
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

			cores = Interpolarizacao(p, corI, corF);
			PutPixel(x, y, cores);}

		} else{  //2nd octant
			
			int d = dy - 2 * dx;
			int incr_e = 2 * (-dy + dx);
			int incr_ne = 2 * (dx);
			int x = xi;
			int y = yi;
			double dT = sqrt ((xf-xi) * (xf-xi) + (yf - yi) * (yf - yi)); // distancia total
			double dP;
			double p;
			PutPixel(x, y, corI);
			while (y < yf) {
			if (d < 0) {
			d += incr_ne;
			y++;
			} else {
			d += incr_e;
			x++;
			y++;
			}
			dP = sqrt ((xf-x) * (xf-x) + (yf - y) * (yf - y));
			p = (dP/dT);

			cores = Interpolarizacao(p, corI, corF);
			PutPixel(x, y, cores);
		}

	}
}else{
	if(abs(dx) > abs(dy)){ //8th octant

			int d = -2 * dy + dx;
			int incr_e = -2 * dy;
			int incr_ne = 2 * (-dy -dx);
			int x = xi;
			int y = yi;
			double dT = sqrt ((xf-xi) * (xf-xi) + (yf - yi) * (yf - yi)); // distancia total
			double dP;
			double p;
			PutPixel(x, y, corI);
			while (x < xf) {
			if (d < 0) {
			d += incr_e;
			x++;
			} else {
			d += incr_ne;
			x++;
			y--;
			}
			
			dP = sqrt ((xf-x) * (xf-x) + (yf - y) * (yf - y));
			p = (dP/dT);

			cores = Interpolarizacao(p, corI, corF);
			PutPixel(x, y, cores);		

	}
}else{  //7th octant


			int d = dy + 2 * dx;
			int incr_e = 2 * dx;
			int incr_ne = 2 * (dx + dy); 
			int x = xi;
			int y = yi;
			double dT = sqrt ((xf-xi) * (xf-xi) + (yf - yi) * (yf - yi)); // distancia total
			double dP;
			double p;
			PutPixel(x, y, corI);
			while (y > yf) {
			if (d < 0) {
			d += incr_e;
			y--;
			} else {
			d += incr_ne;
			x++;
			y--;
			}
			dP = sqrt ((xf-x) * (xf-x) + (yf - y) * (yf - y));
			p = (dP/dT);

			cores = Interpolarizacao(p, corI, corF);
			PutPixel(x, y, cores);
}


}

}
}
}

void DrawTriangle(int x1, int y1, color cor1, int x2, int y2, color cor2, int x3, int y3, color cor3){
    
    DrawLine(x1,y1, x2, y2, cor1, cor2);
    DrawLine(x2, y2, x3, y3, cor2, cor3);
    DrawLine(x3, y3, x1, y1, cor3, cor1);

}
// fim


#endif // _MYGL_H_

