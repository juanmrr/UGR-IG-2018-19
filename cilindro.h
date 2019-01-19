// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################


#ifndef _CILINDRO_H
#define _CILINDRO_H

class Cilindro : public ObjRevolucion{

  private:

	//Tupla3f origen = {0.0, 0.0, 0.0};

  public:

	Cilindro(float radio, float altura, int num_puntos_perf, int num_instancias, int tapa, int r, int g, int b){

		origen = {0.0, 0.0, 0.0};

		Tupla3f vertice;
		float x, y, z;
		
		for (int i = 0; i <= num_puntos_perf; i++){
			x = origen(0) + radio;
			y = i*altura/num_puntos_perf;
			z = origen(2);
			vertice = {x, y, z};
			vertices_originales.push_back(vertice);
		}

		crearMalla (vertices_originales, num_instancias, tapa, r, g, b);

	}

	Cilindro(int num_puntos_perf, int num_instancias) : Cilindro (0.5, 2.5, num_puntos_perf, num_instancias, 3, 0, 0, 0) {}


	Cilindro(int num_puntos_perf, int num_instancias, int tapa) : Cilindro (0.5, 2.5, num_puntos_perf, num_instancias, tapa, 0, 0, 0) {}

};

#endif
