// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"
#include "math.h"
#include "textura.h"

using namespace std;

const float PI = 3.141592;

ObjMallaIndexada::ObjMallaIndexada(){

	Tupla3f ambiente;
	Tupla3f difusa;
	Tupla3f especular;
	float brillo;

	ambiente = {0.1, 0.1, 0.1};
	difusa = {0.7, 0.7, 0.7};
	especular = {0.2, 0.2, 0.2};
	brillo = 0.3;

	materiales.push_back(Material(ambiente, difusa, especular, brillo));

	ambiente = {0.8, 0.8, 0.8};
	difusa = {0.3, 0.3, 0.3};
	especular = {0.2, 0.2, 0.2};
	brillo = 0.4;

	materiales.push_back(Material(ambiente, difusa, especular, brillo));

	ambiente = {0.1, 0.1, 0.1};
	difusa = {0.1, 0.1, 0.1};
	especular = {0.8, 0.8, 0.8};
	brillo = 0.2;

	materiales.push_back(Material(ambiente, difusa, especular, brillo));

}


// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

GLuint ObjMallaIndexada::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ) {
  GLuint id_vbo;
  glGenBuffers( 1, & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
  glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador
  // esta instrucción hace la transferencia de datos desde RAM hacia GPU
  glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
  glBindBuffer( tipo_vbo, 0 ); // desactivación del VBO (activar 0)
  return id_vbo ; // devolver el identificador resultado
}

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato (int visualizacion)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...
  // para ahorrar código en la función, se pinta el objeto en dos fases, distinguiendo caras pares e impares
  // con vistas a implementar un modo ajedrez
  // primero vamos a pintar las caras pares...

  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, colores_default.data());

  if (glIsEnabled(GL_LIGHTING)){
  	glEnableClientState (GL_NORMAL_ARRAY);
  	glNormalPointer (GL_FLOAT, 0, normales.data());
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,  (GLfloat *) &materiales[material].difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (GLfloat *) &materiales[material].especular);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,  (GLfloat *) &materiales[material].ambiente);
  	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, materiales[material].brillo);
  }

  // habilitar uso de un array de vértices
  glEnableClientState( GL_VERTEX_ARRAY );
  // indicar el formato y la dirección de memoria del array de vértices
  // (son tuplas de 3 valores float, sin espacio entre ellas)
  glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;

  //if (!textura.empty()){
  //	textura[0].activar();
  // }

  //glDrawElements (GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data());

  // visualizar, indicando: tipo de primitiva, número de índices,
  // tipo de los índices, y dirección de la tabla de índices
  glDrawElements( GL_TRIANGLES, triangulos_par.size()*3, GL_UNSIGNED_INT, triangulos_par.data() );
  
  // si queremos visualizar el modo ajedrez, queremos pintar las caras impares de otro color
  if (visualizacion == 3)
	glColorPointer(3, GL_FLOAT, 0, colores_secundario.data());
  
  // en cualquier caso, vamos a querer pintar las caras impares
  glDrawElements( GL_TRIANGLES, triangulos_impar.size()*3, GL_UNSIGNED_INT, triangulos_impar.data() );
  // deshabilitar array de vértices
  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState (GL_NORMAL_ARRAY);

/*glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer ( 3, GL_FLOAT, 0, vertices.data() );
glDrawElements ( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
glDisableClientState (GL_VERTEX_ARRAY);
*/
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido (int visualizacion)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   // comprobar el estado de los buffer

   // comprobamos el buffer de vertices
   if (id_vbo_ver == 0)
 	id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, vertices.size()*sizeof(Tupla3f)*sizeof(float), vertices.data());

   // comprobamos el buffer de colores

   if (id_vbo_col_default == 0)
	id_vbo_col_default = CrearVBO (GL_ARRAY_BUFFER, colores_default.size()*sizeof(Tupla3f)*sizeof(float), colores_default.data());

   if (id_vbo_col_impar == 0)
	id_vbo_col_impar = CrearVBO (GL_ARRAY_BUFFER, colores_secundario.size()*sizeof(Tupla3f)*sizeof(float), colores_secundario.data());

   // comprobamos el buffer de triangulos

   if (id_vbo_tri_par == 0)
	id_vbo_tri_par = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, triangulos_par.size()*sizeof(Tupla3i)*sizeof(int), triangulos_par.data());

   if (id_vbo_tri_impar == 0)
	id_vbo_tri_impar = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, triangulos_impar.size()*sizeof(Tupla3i)*sizeof(int), triangulos_impar.data());

   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 ); // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_default); // activar VBO de colores
   glColorPointer (3, GL_FLOAT, 0, 0); 
   glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de colores
   glEnableClientState( GL_COLOR_ARRAY ); // habilitar la tabla de colores

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_par );// activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3*triangulos_par.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triangulos

   glDisableClientState(GL_ARRAY_BUFFER);


   // si queremos visualizar el modo ajedrez, vamos a querer cambiar de color
   if (visualizacion == 3){
	   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_impar); // activar VBO de colores
	   glColorPointer (3, GL_FLOAT, 0, 0); 
	   glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de colores
   }

   glEnableClientState( GL_COLOR_ARRAY ); // habilitar la tabla de colores

   // pintamos el resto de caras

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_impar );// activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3*triangulos_impar.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triangulos

   // desactivar uso de array de vértices y colores
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState(GL_ARRAY_BUFFER);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int modo, int visualizacion)
{
   // completar .....(práctica 1)
   glEnable(GL_CULL_FACE); // Elimina las partes de atrás de los triángulos

   switch(modo){
	case 0:
		draw_ModoInmediato(visualizacion);
		break;
	case 1:
		draw_ModoDiferido(visualizacion);
		break;
   }
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{

	Tupla3f normal, a, b;
	float m;
	std::vector<int> aux;

	for (int i = 0; i < vertices.size(); i++){
		normales.push_back(Tupla3f(0,0,0));
		aux.push_back(0);
	}
   
	for (int i = 0; i < triangulos.size(); i++){
		a = vertices[triangulos[i](1)] - vertices[triangulos[i](0)];
		b = vertices[triangulos[i](2)] - vertices[triangulos[i](0)];
		normal = {a(1) * b(2) - a(2) * b(1), a(0) * b (2) - a(2) * b(0), a(0) * b(1) - a(1) * b(0)};
		m = sqrt(pow(normal(0), 2) + pow (normal(1), 2) + pow (normal(2), 2));

		// normalizamos el vector
		normales_triangulos.push_back(Tupla3f(normal(0)/m, normal(1)/m, normal(2)/m));

		normales[triangulos[i](0)] = normales[triangulos[i](0)] + normales_triangulos[i];
    		normales[triangulos[i](1)] = normales[triangulos[i](1)] + normales_triangulos[i];
    		normales[triangulos[i](2)] = normales[triangulos[i](2)] + normales_triangulos[i];

		aux[triangulos[i](0)] += 1;
		aux[triangulos[i](1)] += 1;
		aux[triangulos[i](2)] += 1;
	}

	// normalizamos el array de vértices
	for(int j = 0; j < aux.size(); j++){
      	normales[j] = normales[j]/aux[j]; 
    }
		

}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   	// leer la lista de caras y vértices
 	  ply::read( nombre_archivo, vertices, triangulos );

  	 // distinguimos entre triangulos pares e impares para el modo ajedrez

  	 for (int i = 0; i < triangulos.size(); i++){
		if (i%2)
		triangulos_impar.push_back(triangulos[i]);
		else
		triangulos_par.push_back(triangulos[i]);
  	 }

   	Tupla3f color_default = {0.0, 0.0, 0.0};
   	Tupla3f color_secundario = {0.0, 1.0, 0.0};

  	 // rellenamos los dos vectores de colores

  	 for (int j = 0; j < vertices.size(); j++){
		colores_secundario.push_back (color_secundario);
		colores_default.push_back (color_default);
   	}

}

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(){}

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil, const int num_instancias )
{
   // completar ......(práctica 2)
	
	ply::read_vertices (nombre_ply_perfil, vertices_originales);
	crearMalla (vertices_originales, num_instancias, 3);

}

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil, const int num_instancias, const int tapa )
{
   // completar ......(práctica 2)
	
	ply::read_vertices (nombre_ply_perfil, vertices_originales);
	crearMalla (vertices_originales, num_instancias, tapa);

}

void ObjRevolucion::crearTapa (const int tapa, const int M, const int N){

	Tupla3i triangulo;

	if (tapa == 2 || tapa == 3)
		for (int i = 0; i < N; i++){
			triangulo = {(int)vertices.size() - 2, ((M * i) + M) % (N * M), (i * M) % (N * M)};
			triangulos.push_back(triangulo);			
		}

	if (tapa == 1 || tapa == 3)
		for (int i = 0; i < N; i++){
			triangulo = {(int)vertices.size() - 1, ((M * i) + M - 1) % (N * M), ((M * (i + 1)) + M - 1) % (N * M)};
			triangulos.push_back(triangulo);
		}

}

void ObjRevolucion::crearMalla( const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const int tapa){

	Tupla3f ver;
	float x, y, z, a, b;
	bool ascendente = true;

	std::vector<Tupla3f> aux = perfil_original;

	// comprobamos si el perfil es ascendente
	ascendente = this->perfilAscendente(perfil_original, 1);

	// si no es ascendente, permutamos el vector para que lo sea
	if (!ascendente)
		aux = this->cambiarAPerfilAscendente(perfil_original);

	int N = num_instancias_perf;

	int M = aux.size();

	if (aux[0](0) == 0 && aux[0](2) == 0){
		vert_tapa_inferior = aux.front();
		aux.erase(aux.begin());
	}
	else{
		vert_tapa_inferior = {0, aux[0](1), 0};
	}

	M = aux.size();

	if (aux[M - 1](0) == 0 && aux[M - 1](2) == 0){
		vert_tapa_superior = aux.back();
		aux.pop_back();
	}
	else{
		vert_tapa_superior = {0, aux[M - 1](1), 0};
	}

	M = aux.size();

	// generamos los vertices por rotacion

	this->generarVertices (N, M, 1, aux);

	// introducimos en el vector de vertices de la malla los vertices correspondientes a las tapas

	vertices.push_back(vert_tapa_inferior);
	vertices.push_back(vert_tapa_superior);

	Tupla3i triangulo;
	int c, d;

	// generamos las caras del cuerpo

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M - 1; j++){
			c = M * i + j;
			d = M * ((i + 1) % N) + j;
			triangulo = {c, d, d + 1};
			triangulos.push_back(triangulo);
			triangulo = {c, d + 1, c + 1};
			triangulos.push_back(triangulo);
		}
	}

	this->crearTapa (tapa, M, N);

	for (int i = 0; i < triangulos.size(); i++){
		if (i%2)
			triangulos_impar.push_back(triangulos[i]);
		else
			triangulos_par.push_back(triangulos[i]);
	}

	// generamos las tapas en función del parámetro "tapa"

	this->calcular_normales();

	// por último, generamos los arrays de colores

	Tupla3f color_default = {0, 0, 0};
	Tupla3f color_secundario = {0.5, 0.5, 0};

	for (int i = 0; i < vertices.size(); i++){
		colores_default.push_back(color_default);
		colores_secundario.push_back(color_secundario);
	}

}

void ObjRevolucion::generarVertices (int N, int M, const int eje, std::vector<Tupla3f> aux){

	float x, y, z, a, b;
	Tupla3f ver;

	switch (eje){
	   case 0 :
		for (int i = 0; i < N; i++){
			a = cos((2*PI*i)/N);
			b = sin((2*PI*i)/N);
			for (int j = 0; j < M; j++){
				x = aux[j](0);
				y = aux[j](1)*a + aux[j](2)*b;
				z = -aux[j](1)*b + aux[j](2)*a;
				ver = {x, y, z};
				vertices.push_back(ver);
			}
		}
	   break;
	   case 1 :
		for (int i = 0; i < N; i++){
			a = cos((2*PI*i)/N);
			b = sin((2*PI*i)/N);
			for (int j = 0; j < M; j++){
				x = aux[j](0)*a + aux[j](2)*b;
				y = aux[j](1);
				z = aux[j](2)*a - aux[j](0)*b;
				ver = {x, y, z};
				vertices.push_back(ver);
			}
		}
	   break;
	   case 2 :
		for (int i = 0; i < N; i++){
			a = cos((2*PI*i)/N);
			b = sin((2*PI*i)/N);
			for (int j = 0; j < M; j++){
				x = aux[j](0)*a + aux[j](1)*b;
				y = -aux[j](0)*b + aux[j](1)*a;
				z = aux[j](2);
				ver = {x, y, z};
				vertices.push_back(ver);
			}
		}
	   break;
	};

}

bool ObjRevolucion::perfilAscendente (std::vector<Tupla3f> perfil, const int eje){

	bool aux = true;
	int M = perfil.size();

	if (perfil[0](eje) > perfil[M - 1](eje))
		aux = false;

	return aux;
}

std::vector<Tupla3f> ObjRevolucion::cambiarAPerfilAscendente(std::vector<Tupla3f> perfil_original){

	std::vector<Tupla3f> aux;
	int M = perfil_original.size();

	for (int i = 0; i < M; i++)
		aux.push_back(perfil_original[M - 1 - i]);

	return aux;

}

void ObjMallaIndexada::sigMaterial(){

	material = (material + 1) % materiales.size();

}
