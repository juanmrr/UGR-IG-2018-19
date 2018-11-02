// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Juan Manuel Rubio Rodríguez
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 8, 16 );
   cubo     = new Cubo();
   esfera	= new Esfera (16, 16);
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5 ;

/*   switch( iparam )
   {
      case 0:
         // altura 1: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
         // inicialmente es 1.0 (media de los valores extremos)
         altura_1= 1.0 + 0.3*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 1:
         // altura 2: oscila entre 1.1 y 1.9, a 0.8 oscilaciones por segundo
         altura_2 = 1.5 + 0.4*sin( 0.8*(2.0*M_PI*valor_na) );
         break ;
      case 2:
         // angulo en grados de rotacion 1 (cubo rojoaa)
         // crece linealmente a 150 grados por segundo, inicialmente es 20 grados
         ag_rotacion_1 = 20.0 + 150.0*valor_na ;
         break ;
      case 3:
         // ángulo en grados de rotacion 2 (cubo azul)
         // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         // (inicialmente es -7.5 grados)
         ag_rotacion_2 = -7.5 + 37.5*sin( 1.5*(2.0*M_PI*valor_na) );
         break ;
   }*/

	switch (iparam){
		case 0:
			rotacion1 = 30.0*sin( 0.1 * (2.0*M_PI*valor_na));
		break;
		case 1:
			rotacion2 = 45.0*valor_na;
		break;
		case 2: 
			traslacion = 0.2*sin( 0.2 * (2.0*M_PI*valor_na));
		break;
		case 3: 
			rotacion3 = 30*valor_na;
		break;
	}
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );
   assert( cilindro != nullptr );
   assert( esfera   != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;

   // dibujar objetos

	glPushMatrix();
		glPushMatrix();
			base ();
		glPopMatrix();
		glPushMatrix();
			glTranslatef (0.0, 2.0, 0.0);
			brazo ();
		glPopMatrix();
	glPopMatrix();
}

void GrafoParam::bola (){


glPushMatrix();
   glPushMatrix();
	glTranslatef (traslacion, 0.0, 0.0);
	glPushMatrix();
		glScalef (0.2, 0.2, 0.2);
		cubo->draw (modo_vis, usar_diferido);
	glPopMatrix();
	glRotatef (rotacion2, 0.0, 1.0, 0.0);
	glRotatef (rotacion1, 0.0, 0.0, 1.0);
	glPushMatrix();
		glTranslatef (0.0, -1.1, 0.0);
		glScalef (0.05, 1.1, 0.05);
		cilindro->draw (modo_vis, usar_diferido);
	glPopMatrix();
	glPushMatrix();
		glTranslatef (0.0, -1.25, 0.0);
		glScalef (0.2, 0.2, 0.2);
		esfera->draw (modo_vis, usar_diferido);
	glPopMatrix();
   glPopMatrix();
glPopMatrix();

}

void GrafoParam::brazo (){

	glPushMatrix();
		glRotatef (rotacion3, 0.0, 1.0, 0.0);
		glTranslatef (1.5, 0.0, 0.0);
		glPushMatrix();
			glTranslatef (-1.5, 0.0, 0.0);
			glScalef (0.4, 0.4, 0.4);
			cubo->draw (modo_vis, usar_diferido);
		glPopMatrix();
		glPushMatrix();
			glRotatef (90.0, 0.0, 0.0, 1.0);
			glScalef (0.1, 2.0, 0.1);
			cilindro->draw (modo_vis, usar_diferido);
		glPopMatrix();
		glPushMatrix();
			glScalef (0.2, 0.2, 0.2);
			cubo->draw (modo_vis, usar_diferido);
		glPopMatrix();
		glPushMatrix();
			glTranslatef (-0.5, 0.0, 0.0);
			bola ();
		glPopMatrix();
	glPopMatrix();

}

void GrafoParam::base (){

	glPushMatrix();
		glTranslatef (0.0, 0.3, 0.0);
		glScalef (0.2, 2.0, 0.2);
		cilindro->draw (modo_vis, usar_diferido);
	glPopMatrix();
	glPushMatrix();
		glTranslatef (0.0, 0.1, 0.0);
		glScalef (0.7, 0.2, 0.7);
		cilindro->draw (modo_vis, usar_diferido);
	glPopMatrix();
	glPushMatrix();
		glTranslatef (0.0, 0.05, 0.0);
		glScalef (1.0, 0.1, 1.0);
		cubo->draw (modo_vis, usar_diferido);
	glPopMatrix();

}
