// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################


#ifndef _ESFERA_H
#define _ESFERA_H

class Esfera : public ObjRevolucion{

  private:
	
	const float PI = 3.14159265;
	Tupla3f origen = {0.0, 0.0, 0.0};

  public:

	Esfera (float radio, int num_puntos_perf, int num_instancias, int tapa){

		Tupla3f vertice;
		float x, y, z;

		vertices_originales.push_back({origen(0), origen(1) - radio, origen(2)});
		
		for (int i = 1; i <= num_puntos_perf - 1; i++){
			x = origen(0) + radio*cos(((PI*i)/num_puntos_perf) + 3*PI/2);
			y = origen(1) + radio*sin(((PI*i)/num_puntos_perf) + 3*PI/2);
			z = origen(2);
			vertice = {x, y, z};
			vertices_originales.push_back(vertice);
		}

		vertices_originales.push_back({origen(0), origen(1) + radio, origen(2)});


		crearMalla (vertices_originales, num_instancias, tapa);

	}

	Esfera(int num_puntos_perf, int num_instancias) : Esfera (1, num_puntos_perf, num_instancias, 3) {}


	Esfera(int num_puntos_perf, int num_instancias, int tapa) : Esfera (1, num_puntos_perf, num_instancias, tapa) {}

};

#endif
