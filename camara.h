// *****************************************************************************
//
// Clase Cámara (práctica 5)
//
// *****************************************************************************

#ifndef _CAMARA_H
#define _CAMARA_H

#include "aux.h"

class Camara {

   public:

	Tupla3f eye;
	Tupla3f at;
	Tupla3f up;
	int tipo; // ORTOGONAL o Perspectiva
	float left, right, top, bottom, near, far; // o bien a spect, fov, near, far ;
	Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float top, float bottom, float near, float far) ; // con los parametros necesarios
	void rotarXExaminar ( float angle ) ;
	void rotarYExaminar ( float angle ) ;
	void rotarZExaminar ( float angle ) ;
	void mover ( float x , float y , float z ) ;
	void zoom ( float factor ) ;
	void setObserver ( ) ; // completar
	void setProyeccion () ;
	float producto_escalar(Tupla3f v1, Tupla3f v2, int d);
	void redimensionar ( int newWidth, int newHeight );
};

#endif
