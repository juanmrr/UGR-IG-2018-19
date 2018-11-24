// *****************************************************************************
//
// Clase Luz (práctica 4)
//
// *****************************************************************************

#include "luz.h"
#include <chrono>

int Luz::luces = 0;

Luz::Luz (GLenum indice, Tupla4f punto, Tupla4f luz_ambiente, Tupla4f luz_difusa, Tupla4f luz_especular){

	this->indice = indice;
	this->punto = punto;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->activa = false;

}

void Luz::activar(){

	activa = !activa;

	if (activa){
		glEnable (indice);
		glEnable (GL_LIGHTING);
		glLightfv (indice, GL_AMBIENT, (GLfloat*) &luz_ambiente);
		glLightfv (indice, GL_DIFFUSE, (GLfloat*) &luz_difusa);
		glLightfv (indice, GL_SPECULAR, (GLfloat*) &luz_especular);
    			glMatrixMode(GL_MODELVIEW);
    			glPushMatrix();
   			glLoadIdentity();
			glLightfv (indice, GL_POSITION, (GLfloat*) &punto);
    			glPopMatrix();
		luces = luces + 1;
	}
	else{
		glDisable (indice);
		luces = luces - 1;
	}

	if (luces == 0)
		glDisable (GL_LIGHTING);
		
}

void Luz::colocarLuz(){

    //float rotacion = 30.0*sin( 0.1 * (2.0*M_PI*0.5));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(rotacion, 0.0, 1.0, 0.0);
    glLightfv (indice, GL_POSITION, (GLfloat*) &punto);
    glPopMatrix();

}

void Luz::inicioAnimaciones( )
{
   using namespace std::chrono ;
   ultima_actu = steady_clock::now() ;
}

void Luz::girar(){

   using namespace std::chrono ;

   const Instante   ahora       =  steady_clock::now();
   const Duracion_s duracion_s  =  ahora - ultima_actu;
   ultima_actu = ahora ;
   rotar(duracion_s.count() * 100);

}

void Luz::rotar(float duracion){

	rotacion = fmod((rotacion + duracion), 360);
	colocarLuz();

}



