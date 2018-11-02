// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Juan Manuel Rubio Rodríguez
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "cubo.h"
#include "tetraedro.h"

constexpr int num_parametros = 4 ; // número de parámetros o grados de libertad
                                   // de este modelo

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const int p_usar_diferido, const int p_modo_vis );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void columna( const float altura, const float ag_rotacion,
                             const float radio_cil );

   void bola (); // dibuja la bola con el cable
   void brazo (); // dibuja el brazo sobre el que cuelga la bola
   void base (); // dibuja la base junto con la columna central


   // objetos tipo malla indexada (nodos terminales)

   Cilindro * cilindro = nullptr ;
   Cubo *     cubo     = nullptr ;
   Esfera *	  esfera   = nullptr ;

   // parámetros de la llamada actual (o última) a 'draw'
   int modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   float rotacion1, rotacion2, rotacion3, traslacion;

} ;

#endif
