#ifndef _TEXTURA_H
#define _TEXTURA_H

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include <string>

typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char *data;
} AUX_RGBImageRec;

class Textura {

	protected:

		static int texturasActivas;
		GLuint textura_id;
   		std::vector<Tupla2f> coordenadas_texturas_vertices;
		std::vector<unsigned char> data;
		int ancho;
		int alto;


	public:

		Textura(const char *filename);
		void activar();

};

#endif
