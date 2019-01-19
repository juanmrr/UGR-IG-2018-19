// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

#ifndef _DADO_H
#define _DADO_H

class Dado : public ObjMallaIndexada{

   public:

   Dado(int r, int g, int b){

	   // inicializar la tabla de vértices
	   vertices =  { 	{ -0.5, -0.5, -0.5 }, // 0
		            { -0.5, -0.5, +0.5 }, // 1
		            { -0.5, +0.5, -0.5 }, // 2
		            { -0.5, +0.5, +0.5 }, // 3

		            { +0.5, -0.5, -0.5 }, // 4
		            { +0.5, -0.5, +0.5 }, // 5
		            { +0.5, +0.5, -0.5 }, // 6
		            { +0.5, +0.5, +0.5 }, // 7

		            { -0.5, -0.5, +0.5 }, // 8
		            { +0.5, -0.5, +0.5 }, // 9
		            { -0.5, +0.5, +0.5 }, // 10
		            { +0.5, +0.5, +0.5 }, // 11

				{ -0.5, -0.5, -0.5 }, // 12
		            { +0.5, -0.5, -0.5 }, // 13
		            { -0.5, +0.5, -0.5 }, // 14
		            { +0.5, +0.5, -0.5 }, // 15

		            { -0.5, +0.5, +0.5 }, // 16
		            { +0.5, +0.5, +0.5 }, // 17
		            { -0.5, +0.5, -0.5 }, // 18
		            { +0.5, +0.5, -0.5 }, // 19

		            { -0.5, -0.5, +0.5 }, // 20
		            { +0.5, -0.5, +0.5 }, // 21
				{ -0.5, -0.5, -0.5 }, // 22
		            { +0.5, -0.5, -0.5 }, // 23
		         };

	   // inicializar la tabla de caras o triángulos:
	   // (es importante en cada cara ordenar los vértices en sentido contrario
	   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

	   triangulos = { { 0, 1, 3 }, { 0, 3, 2 },
		            { 5, 4, 7 }, { 4, 6, 7 },
		            { 8, 9, 11 }, { 8, 11, 10 },
		            { 13, 12, 14 }, { 13, 14, 15 },
		            { 16, 17, 19 }, { 16, 19, 18 },
		            { 21, 20, 22 }, { 21, 22, 23 }
		          } ;

	   for (int i = 0; i < triangulos.size(); i++)
		if (i%2)
			triangulos_impar.push_back(triangulos[i]);
		else
			triangulos_par.push_back(triangulos[i]);

	setColor(r, g, b);

	calcular_normales();

	texturas.push_back(Textura("./Img/logo.jpg"));
/*
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
*/

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.25,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.25,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.75,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.5,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.75,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.5,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.25,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.5,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.25,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.5,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.75,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.75,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));

   }

   Dado() : Dado(0, 0, 0) {};

};

#endif
