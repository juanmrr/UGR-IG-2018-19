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
		bool activa;
		GLuint textura_id;
   		std::vector<Tupla2i> coordenadas_texturas_vertices;


	public:
		Textura(const char *filename);
		void activar();

};

#endif
