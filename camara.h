// *****************************************************************************
//
// Clase Cámara (práctica 5)
//
// *****************************************************************************

#ifndef _CAMARA_H
#define _CAMARA_H

#include "aux.h"
#include <chrono>

// tipo para registrar instantes de tiempo
typedef std::chrono::time_point<std::chrono::steady_clock> Instante ;

// tipo para duraciones en segundos (como números 'float', con parte fraccionaria)
typedef std::chrono::duration<float,std::ratio<1,1>> Duracion_s ;


class Camara {

   protected:

	Tupla3f eye;
	Tupla3f at;
	Tupla3f up;
	int tipo; // ORTOGONAL o Perspectiva
	float left, right, top, bottom, near, far; // o bien a spect, fov, near, far ;
	Instante ultima_actu;

   public:

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
	void inicioAnimaciones();
	void girar();
};

#endif
