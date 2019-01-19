// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################


#ifndef _CUENCO_H
#define _CUENCO_H

class Cuenco : public ObjRevolucion{

  private:
	
	const float PI = 3.14159265;
	Tupla3f origen = {0.0, 0.0, 0.0};

  public:

	Cuenco (float radio_interior, float radio_exterior, int num_puntos_perf, int num_instancias, int tapa, int r, int g, int b){

		Tupla3f vertice;
		float x, y, z;

		vertices_originales.push_back({origen(0), origen(1) - radio_exterior, origen(2)});
		
		for (int i = 1; i <= num_puntos_perf; i++){
			x = origen(0) + radio_exterior*cos(((PI*i/2)/num_puntos_perf) + 3*PI/2);
			y = origen(1) + radio_exterior*sin(((PI*i/2)/num_puntos_perf) + 3*PI/2);
			z = origen(2);
			vertice = {x, y, z};
			vertices_originales.push_back(vertice);
		}

		for (int i = num_puntos_perf; i >= 0; i--){
			x = origen(0) + radio_interior*cos(((PI*i/2)/num_puntos_perf) + 3*PI/2);
			y = origen(1) + radio_interior*sin(((PI*i/2)/num_puntos_perf) + 3*PI/2);
			z = origen(2);
			vertice = {x, y, z};
			vertices_originales.push_back(vertice);
		}

		crearMalla (vertices_originales, num_instancias, tapa, r, g, b);

	}

	Cuenco(int num_puntos_perf, int num_instancias) : Cuenco (0.4, 0.5, num_puntos_perf, num_instancias, 2, 0, 0, 0) {}


	Cuenco(int num_puntos_perf, int num_instancias, int tapa) : Cuenco (0.4, 0.5, num_puntos_perf, num_instancias, tapa, 0, 0, 0) {}

};

#endif
