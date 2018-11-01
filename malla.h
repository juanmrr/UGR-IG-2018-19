// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"


// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int visualizacion);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int visualizacion);

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo, int visualizacion);

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   // perfil y vertices de las tapas

   std::vector<Tupla3f> vertices_originales ; // array con los vértices originales leídos de un archivo ply
   Tupla3f vert_tapa_superior ; // vertice de la tapa superior
   Tupla3f vert_tapa_inferior ; // vertice de la tapa inferior

   // arrays de vertices, triangulos y colores

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

   std::vector<Tupla3i> triangulos_par ; // una terna de 3 enteros por cada cara o triángulo par -> modo ajedrez
   std::vector<Tupla3i> triangulos_impar ; // una terna de 3 enteros por cada cara o triángulo impar -> modo ajedrez

   std::vector<Tupla3f> colores_default ;    // array de colores con un color por defecto (0,0,0)
   std::vector<Tupla3f> colores_secundario ;    // array de colores secundario para el modo ajedrez

   // identificadores para buffers
   GLuint id_vbo_ver = 0; // identificador de VBO vertices
   GLuint id_vbo_col_default = 0; // identificador de VBO colores
   GLuint id_vbo_col_impar = 0; // identificador de VBO colores
   GLuint id_vbo_tri = 0; // identificador de VBO de triangulos
   GLuint id_vbo_tri_par = 0; 
   GLuint id_vbo_tri_impar = 0; 
   // completar: tabla de colores, tabla de normales de vértices

} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      ObjRevolucion();
      ObjRevolucion( const std::string & nombre_ply_perfil, const int num_instancias );
	ObjRevolucion( const std::string & nombre_ply_perfil, const int num_instancias, const int tapa );

   protected:
      void crearMalla( const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, const int tapa);

   private:
	void crearTapa (const int tapa, const int M, const int N);

	// genera los vértices por revolución de acuerdo al eje
	// 0 -> eje x; 1 -> eje y; 2 -> eje z
	void generarVertices (int N, int M, const int eje, std::vector<Tupla3f> aux);

	// comprueba si el perfil es de orden ascendente y devuelve true en ese caso
	// 0 -> eje x; 1 -> eje y; 2 -> eje z
	bool perfilAscendente (std::vector<Tupla3f> perfil, const int eje);

	// cambiar un vector dado en orden descendente por uno dado en orden ascendente
	std::vector<Tupla3f> cambiarAPerfilAscendente(std::vector<Tupla3f> perfil_original);

} ;

#endif
