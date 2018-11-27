#include "textura.h"
#include <string>

#include <GL/glut.h>

#include "CImg.h"
using namespace cimg_library;

using namespace std ;

int Textura::texturasActivas = 0;

Textura::Textura(const char *filename){

   CImg<unsigned char> logo;
   logo.load(filename);

   // empaquetamos bien los datos
   for (long y = 0; y < logo.height(); y ++){
      for (long x = 0; x < logo.width(); x ++)
      {
	 unsigned char *r = logo.data(x, y, 0, 0);
	 unsigned char *g = logo.data(x, y, 0, 1);
	 unsigned char *b = logo.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }
   }

	ancho = logo.width();
	alto = logo.height();

   coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));

}

void Textura::activar(){

   glGenTextures(1, &textura_id);
   glBindTexture(GL_TEXTURE_2D, textura_id);

   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());

   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glEnableClientState (GL_TEXTURE_COORD_ARRAY);
   glBindTexture( GL_TEXTURE_2D, textura_id ); // activa textura con id textura_id
   glTexCoordPointer(2, GL_FLOAT, 0, coordenadas_texturas_vertices.data());
   //glBindTexture(GL_TEXTURE_2D, 0);

}
