// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################


#ifndef _CUADRO_H
#define _CUADRO_H

class Cuadro : public ObjMallaIndexada{

	/*public:

		Cuadro(){

			vertices = {{-1.0, -1.0, 0.0},
					 {1.0, -1.0, 0.0},
					{-1.0, 1.0, 0.0},
					 {1.0, 1.0, 0.0}
					};

			triangulos = {{0, 3, 2},
					  {0, 1, 3}
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

		calcular_normales();

		texturas.push_back(Textura("./Img/logo.jpg"));
		texturas.push_back(Textura("./Img/prueba.jpg"));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));

	}
*/

	public:

		Cuadro(int r, int g, int b){

			vertices = {{ 0.0,  1.0, 0.0},
					{ 1.0,  1.0, 0.0},
					{ 0.0,  0.0, 0.0},
					{ 1.0,  0.0, 0.0},
					{-1.0,  1.0, 0.0},
					{-1.0,  0.0, 0.0},
					{-1.0, -1.0, 0.0},
					{ 0.0, -1.0, 0.0},
					{ 1.0, -1.0, 0.0},
					{ 0.0,  0.0, 0.0},
					{ 1.0,  0.0, 0.0},
					{ 0.0,  1.0, 0.0},
					};

			triangulos = {{11, 4, 5},
					  {11, 5, 9},
					  {1, 0, 2},
					  {3, 1, 2},
					  {9, 5, 6},
					  {9, 6, 7},
					  {10, 9, 7},
					  {10, 7, 8}
					 };

	   	for (int i = 0; i < triangulos.size(); i++)
			if (i%2)
				triangulos_impar.push_back(triangulos[i]);
			else
				triangulos_par.push_back(triangulos[i]);

	   	setColor(r, g, b);

		calcular_normales();

		texturas.push_back(Textura("./Img/logo.jpg"));

   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,0.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(0.0,1.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(1.0,1.0));

   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));
   	coordenadas_texturas_vertices.push_back(Tupla2f(2.0,2.0));

	}

	Cuadro() : Cuadro(0, 0, 0) {};

};

#endif
