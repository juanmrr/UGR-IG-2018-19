// *****************************************************************************
//
// Clase Luz (práctica 4)
//
// *****************************************************************************

#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"
#include <chrono>

// tipo para registrar instantes de tiempo
typedef std::chrono::time_point<std::chrono::steady_clock> Instante ;

// tipo para duraciones en segundos (como números 'float', con parte fraccionaria)
typedef std::chrono::duration<float,std::ratio<1,1>> Duracion_s ;

class Luz 
{

	public:

	Luz (GLenum indice, Tupla4f punto, Tupla4f luz_ambiente, Tupla4f luz_difusa, Tupla4f luz_especular);

	void activar();
	void colocarLuz();
	void inicioAnimaciones();
	void girar();
	void rotar(float duracion);

	protected:

		GLenum indice;
		Tupla4f punto;
		Tupla4f luz_ambiente;
		Tupla4f luz_difusa;
		Tupla4f luz_especular;
		bool activa;
		static int luces;
		float rotacion = 0.0;
		Instante ultima_actu;
		
		

};

#endif
