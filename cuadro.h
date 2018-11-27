// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################


#ifndef _CUADRO_H
#define _CUADRO_H

class Cuadro : public ObjMallaIndexada{

	public:

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

		texturas.push_back(Textura("./logo.jpg"));

	}

};

#endif
