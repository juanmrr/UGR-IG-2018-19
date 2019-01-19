// *****************************************************************************
//
// Clase Yunque (práctica 1)
//
// *****************************************************************************

#ifndef _YUNQUE_H
#define _YUNQUE_H

class Yunque : public ObjMallaIndexada{

   public:

   Yunque(int r, int g, int b){

	   // inicializar la tabla de vértices
	   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
		            { -0.5, -0.5, +0.5 }, // 1
		            { -0.5, +0.5, -0.5 }, // 2
		            { -0.5, +0.5, +0.5 }, // 3
		            { +0.5, -0.5, -0.5 }, // 4
		            { +0.5, -0.5, +0.5 }, // 5
		            { +0.5, +0.5, -0.5 }, // 6
		            { +0.5, +0.5, +0.5 },  // 7
				{ -1.0, +0.0, +0.0 },
				{ +1.0, +0.0, +0.0 }
		         };

	   // inicializar la tabla de caras o triángulos:
	   // (es importante en cada cara ordenar los vértices en sentido contrario
	   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

	   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
		            { 1, 5, 3 }, { 3, 5, 7 },
		            { 1, 0, 5 }, { 5, 0, 4 },
		            { 3, 7, 2 }, { 2, 7, 6 },
				{ 2, 0, 8 }, { 3, 8, 1 },
				{ 3, 2, 8 }, { 8, 0, 1 },
				{ 7, 9, 6 }, { 9, 4, 6 },
				{ 9, 5, 4 }, { 7, 5, 9 }
		          } ;

	   for (int i = 0; i < triangulos.size(); i++)
		if (i%2)
			triangulos_impar.push_back(triangulos[i]);
		else
			triangulos_par.push_back(triangulos[i]);

	   setColor(r, g, b);

	   calcular_normales();

   }

   Yunque() : Yunque(0, 0, 0) {};

};

#endif
