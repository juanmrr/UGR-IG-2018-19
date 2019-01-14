// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################


#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
//#include "malla.h"
#include "jerarquico.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "cubo.h"
#include "tetraedro.h"
#include "yunque.h"
#include "cuenco.h"
#include "luz.h"
#include "cuadro.h"
#include "dado.h"
#include "camara.h"

class Escena
{

   private:

   Ejes ejes;
   bool animado = false;
   std::vector<Luz> luces;
   std::vector<Camara> camaras;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
   void dibujar_objeto_actual();
   void dibujar_luces();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos   = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)

   // Objetos de la escena
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr;
   ObjPLY * ply = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   ObjRevolucion * obj_rev = nullptr;
   //ObjJerarquico * obj_jer = nullptr;
   Yunque * yunque = nullptr;
   ObjJerarquico * torito = nullptr;
   Cuenco * cuenco = nullptr;
   Cuadro * cuadro = nullptr;
   Dado * dado = nullptr;
   

   // completar: añadir punteros a tetraedro u otros (práctica 1),
   //            y a un objeto PLY y de revolución (práctica 2),
   //           y a un objeto jerarquico (práctica 3).
   // ......

   public:

	int camara_activa = 0;
	int visualizacion = 0; // 0 -> modo puntos       1 -> modo aristas       2 -> modo caras	3 -> modo ajedrez
	int modo = 0; // 0 -> modo inmediato      1 -> modo diferido
	int tapa = 0; // 0 -> sin tapadera; 1 -> con tapadera superior; 2 -> con tapadera inferior; 3 -> con tapadera superior e inferior
	int sombreado = 0; // 0 -> sombreado plano; 1 -> sombreado Gouroud
	int material = 0; // posicion dentro del array de material
	int textura_activa = 0;

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
	void mgeDesocupado();

   private:
	void conmutarAnimaciones();
	void conmutarAnimacionesLuz();


};
#endif
