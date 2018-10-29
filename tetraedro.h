// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

#ifndef _TETRAEDRO_H
#define _TETRAEDRO_H

class Tetraedro : public ObjMallaIndexada{

   public:

	   Tetraedro(){

	   // inicializar la tabla de vértices
	    vertices = {  { -0.5, -0.5, -0.5 },
			  { +0.5, -0.5, -0.5 },
			  { +0.0,  -0.5, +0.5 },
			  { +0.0,  +0.5, +0.0 }
			 };

	    triangulos = { {3, 1, 0}, {3, 0, 2},
			   {3, 2, 1}, {2, 0, 1}
			 };

	   for (int i = 0; i < triangulos.size(); i++)
		if (i%2)
			triangulos_impar.push_back(triangulos[i]);
		else
			triangulos_par.push_back(triangulos[i]);

	   Tupla3f color_default = {0, 0, 0};
	   Tupla3f color_secundario = {0.5, 0.5, 0};

	   for (int i = 0; i < vertices.size(); i++){
			colores_default.push_back(color_default);
			colores_secundario.push_back(color_secundario);
	   }


   }

};

#endif
