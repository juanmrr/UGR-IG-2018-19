// #############################################################################
// Juan Manuel Rubio Rodríguez
//
// Informática Gráfica (Grado Informática)
//
// #############################################################################

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "ply_reader.h"
#include <limits.h>

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane = 0.1;
    Back_plane = 2000.0;
    Observer_distance = 2.0;


    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    cono = new Cono (5, 25, 3);
    cilindro = new Cilindro (10, 20, 3);
    esfera = new Esfera (30, 30, 3);
    ply = new ObjPLY ("./plys/ant");
    //obj_jer = new ObjJerarquico();
    torito = new ObjJerarquico();
    yunque = new Yunque();
    cuadro = new Cuadro();
    dado = new Dado();
    //cuenco = new Cuenco(10, 10); //-> los parámetros son el numero de puntos del perfil y el numero de instancias a generar

	cubo_sel = new Cubo (0, 0, 20);
	cono_sel = new Cono (0.5, 1, 5, 25, 3, 0, 0, 40);
	cilindro_sel_1 = new Cilindro (0.5, 2.5, 10, 20, 3, 0, 0, 60);
	cilindro_sel_2 = new Cilindro (0.5, 2.5, 10, 20, 3, 0, 0, 80);
	cilindro_sel_3 = new Cilindro (0.5, 2.5, 10, 20, 3, 0, 0, 100);
	cilindro_sel_4 = new Cilindro (0.5, 2.5, 10, 20, 3, 0, 0, 120);
	esfera_sel_1 = new Esfera (1.0, 30, 30, 3, 0, 0, 140);
	esfera_sel_2 = new Esfera (1.0, 30, 30, 3, 0, 0, 160);
	esfera_sel_3 = new Esfera (1.0, 30, 30, 3, 0, 0, 180);

    // posicion, ambiente, difusa, especular

    luces.push_back(Luz(GL_LIGHT0, Tupla4f(0.0,0.0,1.0,0.0), Tupla4f(0.0,0.0,0.0,1.0), Tupla4f(1.0,1.0,1.0,1.0), Tupla4f(1.0,1.0,1.0,1.0)));
    luces.push_back(Luz(GL_LIGHT1, Tupla4f(0.0,10.0,10.0,1.0), Tupla4f(0.0,0.0,0.0,1.0), Tupla4f(1.0,0.0,1.0,1.0), Tupla4f(1.0,0.0,1.0,1.0)));

	// luz direccional en el séptimo octante de color amarillo
    luces.push_back(Luz(GL_LIGHT2, Tupla4f(-1.0,-1.0,1.0,0.0), Tupla4f(0.0,0.0,0.0,1.0), Tupla4f(1.0,1.0,0.0,1.0), Tupla4f(1.0,1.0,0.0,1.0)));

	// luz posicional verde
    luces.push_back(Luz(GL_LIGHT3, Tupla4f(10.0,-10.0,10.0,1.0), Tupla4f(0.0,0.0,0.0,1.0), Tupla4f(0.0,1.0,0.0,1.0), Tupla4f(0.0,1.0,0.0,1.0)));

    // .......completar: ...
    // .....

    camaras.push_back(Camara({0, 0, 1}, {0, 0, 0}, {0, 1, 0}, 0, -0.5, 0.5, -0.5, 0.5, 0.1, 50.0));
    camaras.push_back(Camara({0, 0, 20}, {0, 0, 0}, {0, 1, 0}, 1, -0.03, 0.03, -0.03, 0.03, 0.1, 50.0));
    camaras.push_back(Camara({0, 20, 0}, {0, 0, 0}, {1, 0, 0}, 1, -0.03, 0.03, -0.03, 0.03, 0.1, 50.0));
    camaras.push_back(Camara({20, 0, 0}, {0, 0, 0}, {0, 1, 0}, 1, -0.03, 0.03, -0.03, 0.03, 0.1, 50.0));
    camaras.push_back(Camara({20, 20, 20}, {0, 0, 0}, {0, 1, 0}, 1, -0.03, 0.03, -0.03, 0.03, 0.1, 50.0));

    num_objetos = 7 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	redimensionar( UI_window_width, UI_window_height );
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)

   switch(sombreado)
   {
	case 0:
		glShadeModel(GL_FLAT);
		break;
	case 1:
		glShadeModel(GL_SMOOTH);
		break;
   }

   
   switch(visualizacion)
   {
	case 0:

	   // dibujar vertices
	   glPointSize(6);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	   break;

	case 1:

	   // dibujar aristas
	   glLineWidth(1);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	   break;

	case 2:

	   // dibujar caras
	   //glShadeModel(GL_FLAT);
	   if (objeto_actual == 9)
		glColor3f (1.0, 1.0, 1.0);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   break;

	case 3:
	   
	   // modo ajedrez
	   //glShadeModel(GL_FLAT);
	   if (objeto_actual == 9)
		glColor3f (1.0, 1.0, 1.0);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   break;
   }

   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {
      case 0:
       if ( cubo != nullptr ) cubo->draw(modo, visualizacion, textura_activa, 0) ;
       break ;
      case 1:
         //  ......completar un caso por cada objeto que se haya creado
	 if (tetraedro != nullptr) tetraedro->draw(modo, visualizacion, textura_activa, 0);
	 break;
      case 2:
	 if (cono != nullptr) cono->draw(modo, visualizacion, textura_activa, 0);
	 break;
      case 3:
	 if (cilindro != nullptr) cilindro->draw(modo, visualizacion, textura_activa, 0);
	 break;
      case 4:
	 if (esfera != nullptr) esfera->draw(modo, visualizacion, textura_activa, 0);
	 break;
      case 5:
	 if (ply != nullptr) ply->draw(modo, visualizacion, textura_activa, 0);
	 else if (obj_rev != nullptr) obj_rev->draw(modo, visualizacion, textura_activa, 0);
	 break;
	//case 6:
	// if (obj_jer != nullptr) obj_jer->draw(modo, visualizacion);
	// break;
    /*case 6:
	 if (dado != nullptr) dado->draw(modo, visualizacion, textura_activa);
	 break;
	case 7: 
	 if (yunque != nullptr) yunque->draw(modo, visualizacion, textura_activa);
	 break;
	case 6:
	 if (torito != nullptr) torito->draw(modo, visualizacion);
	 break;
	//case 8:
	 //if (cuenco != nullptr) cuenco->draw(modo, visualizacion, textura_activa);
	 //break;*/
	case 6:
	 //if (cuadro != nullptr) cuadro->draw(modo, visualizacion, textura_activa);
	 colocar_escena();
	 break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
       break ;
   }
}

void Escena::dibujar_luces(){

	for (int i = 0; i < luces.size(); i++)
		if (luces[i].esta_activa())
			luces[i].dibujar();

}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
/*
	glEnable (GL_NORMALIZE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	// si las luces están activadas, las desactivamos temporalmente para dibujar los ejes
	if (glIsEnabled (GL_LIGHTING)){
		glDisable (GL_LIGHTING);
  			ejes.draw();
		glEnable (GL_LIGHTING);
	}
	else
		ejes.draw();
	if (glIsEnabled(GL_LIGHTING))
		dibujar_luces();
	dibujar_objeto_actual();
*/

	//////////////////////////////////
	////
	////	Pruebas con ViewPort
	////
	//////////////////////////////////



	glEnable (GL_NORMALIZE);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

	glViewport(0, Height/2, Width/2, Height/2);
   	camaras[1].setProyeccion();
   	camaras[1].setObserver();
	// si las luces están activadas, las desactivamos temporalmente para dibujar los ejes
	if (glIsEnabled (GL_LIGHTING)){
		glDisable (GL_LIGHTING);
  			ejes.draw();
		glEnable (GL_LIGHTING);
	}
	else
		ejes.draw();
	if (glIsEnabled(GL_LIGHTING))
		dibujar_luces();
	dibujar_objeto_actual();

	glViewport(Width/2, Height/2, Width/2, Height/2);
   	camaras[2].setProyeccion();
   	camaras[2].setObserver();
	// si las luces están activadas, las desactivamos temporalmente para dibujar los ejes
	if (glIsEnabled (GL_LIGHTING)){
		glDisable (GL_LIGHTING);
  			ejes.draw();
		glEnable (GL_LIGHTING);
	}
	else
		ejes.draw();
	if (glIsEnabled(GL_LIGHTING))
		dibujar_luces();
	dibujar_objeto_actual();

	glViewport(0, 0, Width/2, Height/2);
   	camaras[3].setProyeccion();
   	camaras[3].setObserver();
	// si las luces están activadas, las desactivamos temporalmente para dibujar los ejes
	if (glIsEnabled (GL_LIGHTING)){
		glDisable (GL_LIGHTING);
  			ejes.draw();
		glEnable (GL_LIGHTING);
	}
	else
		ejes.draw();
	if (glIsEnabled(GL_LIGHTING))
		dibujar_luces();
	dibujar_objeto_actual();

	glViewport(Width/2, 0, Width/2, Height/2);
   	camaras[4].setProyeccion();
   	camaras[4].setObserver();
	// si las luces están activadas, las desactivamos temporalmente para dibujar los ejes
	if (glIsEnabled (GL_LIGHTING)){
		glDisable (GL_LIGHTING);
  			ejes.draw();
		glEnable (GL_LIGHTING);
	}
	else
		ejes.draw();
	if (glIsEnabled(GL_LIGHTING))
		dibujar_luces();
	dibujar_objeto_actual();


}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   string nombre;
   int num_puntos_perf, num_instancias, tipo;
   float radio, altura;

   switch( tecla )
   {
      case 'q' :
        // salir
        return true ;
        break ;
      case 'o' :
         // activar siguiente objeto
        objeto_actual = (objeto_actual+1) % num_objetos ;
        cout << "objeto actual == " << objeto_actual << endl ;
        break ;
      case 'm' :
	 visualizacion = (visualizacion + 1) % 4;
	 cout << "Modo de visualización: " << visualizacion << " (0: puntos; 1: lineas; 2: solido; 3: ajedrez)" << endl;
	 break;
      case 'v' :
	 modo = (modo + 1) % 2;
	 cout << "Modo de envío: " << modo << " (0: inmediato; 1: diferido)" << endl;
	 break;
      case '1' :
	 objeto_actual = 1;
	 cout << "Objeto: Tetraedro" << endl;
	 break;
      case '0' :
	 objeto_actual = 0;
	 cout << "Objeto: Cubo" << endl;
	 break;
      case 's' :
	 visualizacion = 0;
	 cout << "Modo de visualización: puntos" << endl;
	 break;
      case 'l' :
	 visualizacion = 1;
	 cout << "Modo de visualización: líneas" << endl;
	 break;
      case 'f' :
	 visualizacion = 2;
	 cout << "Modo de visualización: relleno" << endl;
	 break;
      case 'c' :
	 camara_activa = (camara_activa + 1) % camaras.size();
	 cout << "Cámara activa número: " << camara_activa << endl;
	 break;
	case 't' :
	 tapa = (tapa + 1) % 4;
	 cout << "Tapadera: " << tapa << "(0: sin tapa; 1: tapa superior; 2: tapa inferior; 3: ambas tapas)" << endl;
	 switch (objeto_actual)
		{
		case 2:
			cono = new Cono (5, 25, tapa);
			break;
		case 3:
			cilindro = new Cilindro (20, 20, tapa);
			break;
		case 4:
			esfera = new Esfera (20, 20, tapa);
			break;
		}
	 break;
      case '3' :
	 objeto_actual = 2;
	 cout << "Objeto: cono" << endl;
	 cout << "Introduzca el número de puntos a generar para el perfil" << endl;
	 cin >> num_puntos_perf;
	 cout << "Introduzca el número de instancias que desea generar" << endl;
	 cin >> num_instancias;
//	 cout << "Introduzca el radio (float) del cono" << endl;
//	 cin >> radio;
//	 cout << "Introduzca la altura (float) del cono" << endl;
//	 cin >> altura;
//	 cono = new Cono (radio, altura, num_puntos_perf, num_instancias);
	 cono = new Cono (num_puntos_perf, num_instancias);
	 break;
      case '4' :
	 objeto_actual = 3;
	 cout << "Objeto: cilindro" << endl;
	 cout << "Introduzca el número de puntos a generar para el perfil" << endl;
	 cin >> num_puntos_perf;
	 cout << "Introduzca el número de instancias que desea generar" << endl;
	 cin >> num_instancias;
//	 cout << "Introduzca el radio (float) del cilindro" << endl;
//	 cin >> radio;
//	 cout << "Introduzca la altura (float) del cilindro" << endl;
//	 cin >> altura;
//	 cilindro = new Cilindro (radio, altura, num_puntos_perf, num_instancias);
	 cilindro = new Cilindro (num_puntos_perf, num_instancias);
	 break;
      case '5' :
	 objeto_actual = 4;
	 cout << "Objeto: esfera" << endl;
	 cout << "Introduzca el número de puntos a generar para el perfil" << endl;
	 cin >> num_puntos_perf;
	 cout << "Introduzca el número de instancias que desea generar" << endl;
	 cin >> num_instancias;
//	 cout << "Introduzca el radio (float) de la esfera" << endl;
//	 cin >> radio;
//	 esfera = new Esfera (radio, num_puntos_perf, num_instancias);
	 esfera = new Esfera (num_puntos_perf, num_instancias);
	 break;
      case '6' :
	 objeto_actual = 5;
	 cout << "Introduzca el nombre de un archivo PLY" << endl;
	 cin >> nombre;
	 tipo = ply::tipo_fichero (nombre);
	 if (tipo)
	 	ply = new ObjPLY (nombre);
	 else{
	 	cout << "Introduzca el número de instancias que desea generar" << endl;
	 	cin >> num_instancias;
		obj_rev = new ObjRevolucion (nombre, num_instancias);
	 }
	 break;
	//case '7' :
	// objeto_actual = 6;
	// cout << "Objeto jerárquico" << endl;
	// break;
	//case '8' :
	// objeto_actual = 8;
	// break;
	case 'a' :
	 	this->conmutarAnimaciones();
	 break;
	/*case 'p' :
	 if (objeto_actual == 6)
	 	//obj_jer->siguienteParametro();
	 	torito->siguienteParametro();
	 else
		cout << "No es un objeto jerárquico" << endl;
	break;
	case '<' :
 	 if (objeto_actual == 6)
	 	//obj_jer->decelerar();
	 	torito->decelerar();
	 else
		cout << "No es un objeto jerárquico" << endl;
	break;
	case '>' :
	 if (objeto_actual == 6)
	 	//obj_jer->acelerar();
	 	torito->acelerar();
	 else
		cout << "No es un objeto jerárquico" << endl;
	break;
	case 'z' :
	 if (objeto_actual == 6)
	 	//obj_jer->decrementaParamAct();
	 	torito->decrementaParamAct();
	 else
		cout << "No es un objeto jerárquico" << endl;
	break;
	case 'Z' :
	 if (objeto_actual == 6)
	 	//obj_jer->incrementaParamAct();
	 	torito->incrementaParamAct();
	 else
		cout << "No es un objeto jerárquico" << endl;
	break;
	//case '8' :
	 //objeto_actual = 7;
	 //cout << "Objeto: yunque" << endl;
	break;*/
	case '7' :
	 objeto_actual = 6;
	 //objeto_actual = 8;
	 //cout << "Objeto: cuenco" << endl;
	 break;
	case 'w' :
	 sombreado = (sombreado + 1) % 2;
	 break;
	case 'j' :
	 luces[0].activar();
	 break;
	case 'k' :
	 luces[1].activar();
	 break;
	case 'g' :
	 switch (objeto_actual)
	 {
		case 0: 
			cubo->sigMaterial();
			break;
		case 1:
			tetraedro->sigMaterial();
			break;
		case 2:
			cono->sigMaterial();
			break;
		case 3:
			cilindro->sigMaterial();
			break;
		case 4:
			esfera->sigMaterial();
			break;
		case 5:
	 		if (ply != nullptr) ply->sigMaterial();
	 		else if (obj_rev != nullptr) obj_rev->sigMaterial();
	 		break;
		/*case 6:
			torito->sigMaterial();
			break;
		case 9:
			cuadro->sigMaterial();
			break;*/
	 }
	 break;
	case 'r' :
	 textura_activa = (textura_activa + 1) % cuadro->texturas.size();
	 break;
	case 'y' :
	 luces[2].activar();
	 break;
	case 'u' :
	 luces[3].activar();
	 break;
	//case 'h' :
	 //this->conmutarAnimacionesLuz();
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[camara_activa].rotarYExaminar(-3.0) ;
         //Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camara_activa].rotarYExaminar(3.0) ;
         //Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         camaras[camara_activa].rotarXExaminar(3.0) ;
         break;
	   case GLUT_KEY_DOWN:
         camaras[camara_activa].rotarXExaminar(-3.0) ;
         //Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
	   camaras[camara_activa].zoom(1.2);
         //Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
	   camaras[camara_activa].zoom(-1.2);
         //Observer_distance /= 1.2 ;
         break;
	   case GLUT_KEY_F1:
	   camara_activa = 0;
	   break;
	   case GLUT_KEY_F2:
	   camara_activa = 1;
	   break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

/*void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane,
   wx = ratio_xy*wy ;
   glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}*/
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width = newWidth;
   Height = newHeight;
   //change_projection( float(Width)/float(Height) );
   camaras[camara_activa].redimensionar(newWidth, newHeight);
   glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camara_activa].setProyeccion();
   camaras[camara_activa].setObserver();
}

void Escena::mgeDesocupado(){
	if (objeto_actual == 6){
		//obj_jer->actualizarEstado();
		//torito->actualizarEstado();
	}
	if (glIsEnabled(GL_LIGHT1)){
		luces[1].girar();
		glutPostRedisplay();
	}
	if (glIsEnabled(GL_LIGHT3)){
		luces[3].girar();
		glutPostRedisplay();
	}
	
	//camaras[camara_activa].girar();

		//////////////////
		////
		////	Pantalla dividida
		////
		/////////////////

	camaras[1].girar();
	camaras[2].girar();
	camaras[3].girar();
	camaras[4].girar();

	glutPostRedisplay();
}

void Escena::conmutarAnimaciones(){

	 animado = !animado;

	 if (animado){
		if (objeto_actual == 6){
	 		//obj_jer->inicioAnimaciones();
	 		//torito->inicioAnimaciones();
		}
		if (glIsEnabled(GL_LIGHT1)){
			luces[1].inicioAnimaciones();
	 		glutIdleFunc( funcion_desocupado );
		}
		//if (glIsEnabled(GL_LIGHT3)){
		//	luces[3].inicioAnimaciones();
	 	//	glutIdleFunc( funcion_desocupado );
		//}

		//camaras[camara_activa].inicioAnimaciones();

		//////////////////
		////
		////	Pantalla dividida
		////
		/////////////////

		camaras[1].inicioAnimaciones();
		camaras[2].inicioAnimaciones();
		camaras[3].inicioAnimaciones();
		camaras[4].inicioAnimaciones();

		////////////////

		glutIdleFunc( funcion_desocupado );
	 }else
		glutIdleFunc( nullptr );
}

void Escena::mouseFunc(GLint button, GLint state, GLint x, GLint y){

  switch( button ){
  case GLUT_LEFT_BUTTON:
    // mover cámara
    botonIzquierdoPulsado = state == GLUT_DOWN;
    cx = x;
    cy = y;
  break;
  case GLUT_RIGHT_BUTTON:
    if(state == GLUT_DOWN)
    	if(objeto_actual == 6){
		
		////////////////////
		/////
		/////	Pantalla dividida
		/////
		////////////////////

		if(x < Width/2 && y < Height/2){
			glViewport(0, Height/2, Width/2, Height/2);
   			camaras[1].setProyeccion();
   			camaras[1].setObserver();
		}
		else if(x > Width/2 && y < Height/2){
			glViewport(Width/2, Height/2, Width/2, Height/2);
   			camaras[2].setProyeccion();
   			camaras[2].setObserver();
		}
		else if(x < Width/2 && y > Height/2){
			glViewport(0, 0, Width/2, Height/2);
   			camaras[3].setProyeccion();
   			camaras[3].setObserver();
		}
		else{
			glViewport(Width/2, 0, Width/2, Height/2);
   			camaras[4].setProyeccion();
   			camaras[4].setObserver();
		}

		/////////////////
		
  		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glDisable(GL_DITHER);
		glDisable(GL_LIGHTING);
		draw_trasero();
		Tupla3ub pixel = leer_pixel(x, y);
		seleccionar(pixel);
		glFlush();
      	glEnable(GL_DITHER);
		glEnable(GL_LIGHTING);
    }
  break;
  case 3:
    // Rueda del ratón zoon-
    camaras[camara_activa].zoom(-1.2) ;
  break;
  case 4:
    // Rueda del ratón zoon+
    camaras[camara_activa].zoom(1.2) ;
  break;
  }

}

void Escena::motionFunc( int x, int y){

  float ang = 1; 
  if(botonIzquierdoPulsado){
    if(cx > x)
      //Observer_angle_y--;
      camaras[camara_activa].rotarYExaminar(-ang);
    else if(cx < x)
      camaras[camara_activa].rotarYExaminar(ang);
      //Observer_angle_y++;

    if (cy > y)
      camaras[camara_activa].rotarXExaminar(ang);
      //Observer_angle_x--;
    else if(cy < y)
      camaras[camara_activa].rotarXExaminar(-ang);
      //Observer_angle_x++;

    cx = x;
    cy = y;

  }

}

void Escena::colocar_escena(){

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glPushMatrix();
     //glTranslatef(0.0,-0.4,0.0);
     glPushMatrix();
     //glScalef(2.6,2.6,2.6);
     cono_sel->trasladar(0.8,0.0,-0.6);
     cono_sel->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix();      

     glPushMatrix(); 
     esfera_sel_1->trasladar(-3.9,1.0,1.5);
     esfera_sel_1->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix();

     glPushMatrix();
     //glScalef(0.3,0.3,0.3); 
     esfera_sel_2->trasladar(-1.0,1.0,1.2);
     esfera_sel_2->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix(); 

     glPushMatrix();
     //glScalef(0.6,0.6,0.6);
     esfera_sel_3->trasladar(-2.0,5.0,-2.0);
     esfera_sel_3->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix(); 
     
     glPushMatrix();
     cubo_sel->trasladar(1.2,0.5,1.4);
     //glRotatef(60.0,0.0,1.0,1.0);
     cubo_sel->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix();

     glPushMatrix(); 
     //glScalef(0.6,0.6,0.6);
     cilindro_sel_1->trasladar(-0.8,0.0,-0.7);
     cilindro_sel_1->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix(); 

     glPushMatrix();
     cilindro_sel_2->trasladar(-2.5,1.0,-2.3);
     //glRotatef(50.0,0.0,1.0,0.0);
     //glRotatef(70.0,0.0,0.0,1.0);
     cilindro_sel_2->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix(); 

     glPushMatrix();
     //glScalef(0.8,0.4,0.8);
     cilindro_sel_3->trasladar(-1.3,0.0,-2.3);
     cilindro_sel_3->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix(); 

     glPushMatrix(); 
     //glScalef(0.8,0.8,0.8);
     cilindro_sel_4->trasladar(-2.8,0.0,-1.0);
     cilindro_sel_4->draw(modo, visualizacion, textura_activa, 0);
     glPopMatrix();
 
   glPopMatrix();

}

void Escena::draw_trasero(){

  glPushMatrix();
     glPushMatrix();
     //glScalef(2.6,2.6,2.6);
     glTranslatef(0.8,0.0,-0.6);
     cono_sel->draw_back();
     glPopMatrix();      

     glPushMatrix(); 
     glTranslatef(-3.9,1.0,1.5);
     esfera_sel_1->draw_back();
     glPopMatrix();

     glPushMatrix();
     //glScalef(0.3,0.3,0.3); 
     glTranslatef(-1.0,1.0,1.2);
     esfera_sel_2->draw_back();
     glPopMatrix(); 

     glPushMatrix();
     //glScalef(0.6,0.6,0.6);
     glTranslatef(-2.0,5.0,-2.0);
     esfera_sel_3->draw_back();
     glPopMatrix(); 
     
     glPushMatrix();
     glTranslatef(1.2,0.5,1.4);
     //glRotatef(60.0,0.0,1.0,1.0);
     cubo_sel->draw_back();
     glPopMatrix();

     glPushMatrix(); 
     //glScalef(0.6,0.6,0.6);
     glTranslatef(-0.8,0.0,-0.7);
     cilindro_sel_1->draw_back();
     glPopMatrix(); 

     glPushMatrix();
     glTranslatef(-2.5,1.0,-2.3);
     //glRotatef(50.0,0.0,1.0,0.0);
     //glRotatef(70.0,0.0,0.0,1.0);
     cilindro_sel_2->draw_back();
     glPopMatrix(); 

     glPushMatrix();
     //glScalef(0.8,0.4,0.8);
     glTranslatef(-1.3,0.0,-2.3);
     cilindro_sel_3->draw_back();
     glPopMatrix(); 

     glPushMatrix(); 
     //glScalef(0.8,0.8,0.8);
     glTranslatef(-2.8,0.0,-1.0);
     cilindro_sel_4->draw_back();
     glPopMatrix();

   glPopMatrix();

}

Tupla3ub Escena::leer_pixel(GLint x, GLint y){

	Tupla3ub pixels;

	GLint viewport[4];
	unsigned char pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	//glReadBuffer(GL_BACK);
	//glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (GLubyte *) &pixel[0]);

	//////////////////////
	////
	////	Prueba con Viewport
	////
	//////////////////////

	if(x < Width/2 && y < Height/2){
		glReadPixels(x, 2*viewport[2] - y, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (GLubyte *) &pixel[0]);
	}
	else if(x > Width/2 && y < Height/2){
		glReadPixels(x, 2*viewport[2] - y, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (GLubyte *) &pixel[0]);
	}
	else if(x < Width/2 && y > Height/2){
		glReadPixels(x, viewport[3]*2 - y, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (GLubyte *) &pixel[0]);
	}
	else{
		glReadPixels(x, viewport[3]*2 - y, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (GLubyte *) &pixel[0]);
	}

	//////////////////////

	for(int i = 0; i < 3; i++){
		pixels(i) = pixel[i];
	}

	return pixels;

}

void Escena::seleccionar(Tupla3ub pixel){

	int color = pixel(2);
/*
	switch (color){
		case 20:
			if (cubo_sel->getSeleccionado()){
				cubo_sel->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({cubo_sel->getOrigen()});
			}
			else{
				cubo_sel->setSeleccionado(true);
				camaras[camara_activa].setObjetivo(cubo_sel->getCentro());
			}
		break;
		case 40:
			if (cono_sel->getSeleccionado()){
				cono_sel->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({cono_sel->getOrigen()});
			}
			else{
				cono_sel->setSeleccionado(true);
				camaras[camara_activa].setObjetivo(cono_sel->getCentro());
			}
		break;
		case 60:
			if (cilindro_sel_1->getSeleccionado()){
				cilindro_sel_1->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({cilindro_sel_1->getOrigen()});
			}
			else{
				cilindro_sel_1->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({cilindro_sel_1->getCentro()});
			}
		break;
		case 80:
			if (cilindro_sel_2->getSeleccionado()){
				cilindro_sel_2->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({cilindro_sel_2->getOrigen()});
			}
			else{
				cilindro_sel_2->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({cilindro_sel_2->getCentro()});
			}
		break;
		case 100:
			if (cilindro_sel_3->getSeleccionado()){
				cilindro_sel_3->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({cilindro_sel_3->getOrigen()});
			}
			else{
				cilindro_sel_3->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({cilindro_sel_3->getCentro()});
			}
		break;
		case 120:
			if (cilindro_sel_4->getSeleccionado()){
				cilindro_sel_4->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({cilindro_sel_4->getOrigen()});
			}
			else{
				cilindro_sel_4->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({cilindro_sel_4->getCentro()});
			}
		break;
		case 140:
			if (esfera_sel_1->getSeleccionado()){
				esfera_sel_1->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({esfera_sel_1->getOrigen()});
			}
			else{
				esfera_sel_1->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({esfera_sel_1->getCentro()});
			}
		break;
		case 160:
			if (esfera_sel_2->getSeleccionado()){
				esfera_sel_2->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({esfera_sel_2->getOrigen()});
			}
			else{
				esfera_sel_2->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({esfera_sel_2->getCentro()});
			}
		break;
		case 180:
			if (esfera_sel_3->getSeleccionado()){
				esfera_sel_3->setSeleccionado(false);
				camaras[camara_activa].setObjetivo({esfera_sel_3->getOrigen()});
			}
			else{
				esfera_sel_3->setSeleccionado(true);
				camaras[camara_activa].setObjetivo({esfera_sel_3->getCentro()});
			}
		break;
	}*/

	//////////////////
	////
	////	Con pantalla dividida
	////
	/////////////////

	switch (color){
		case 20:
			if (cubo_sel->getSeleccionado()){
				cubo_sel->setSeleccionado(false);
				camaras[1].setObjetivo({cubo_sel->getOrigen()});
				camaras[2].setObjetivo({cubo_sel->getOrigen()});
				camaras[3].setObjetivo({cubo_sel->getOrigen()});
				camaras[4].setObjetivo({cubo_sel->getOrigen()});
			}
			else{
				cubo_sel->setSeleccionado(true);
				camaras[1].setObjetivo(cubo_sel->getCentro());
				camaras[2].setObjetivo(cubo_sel->getCentro());
				camaras[3].setObjetivo(cubo_sel->getCentro());
				camaras[4].setObjetivo(cubo_sel->getCentro());
			}
		break;
		case 40:
			if (cono_sel->getSeleccionado()){
				cono_sel->setSeleccionado(false);
				camaras[1].setObjetivo({cono_sel->getOrigen()});
				camaras[2].setObjetivo({cono_sel->getOrigen()});
				camaras[3].setObjetivo({cono_sel->getOrigen()});
				camaras[4].setObjetivo({cono_sel->getOrigen()});
			}
			else{
				cono_sel->setSeleccionado(true);
				camaras[1].setObjetivo(cono_sel->getCentro());
				camaras[2].setObjetivo(cono_sel->getCentro());
				camaras[3].setObjetivo(cono_sel->getCentro());
				camaras[4].setObjetivo(cono_sel->getCentro());
			}
		break;
		case 60:
			if (cilindro_sel_1->getSeleccionado()){
				cilindro_sel_1->setSeleccionado(false);
				camaras[1].setObjetivo({cilindro_sel_1->getOrigen()});
				camaras[2].setObjetivo({cilindro_sel_1->getOrigen()});
				camaras[3].setObjetivo({cilindro_sel_1->getOrigen()});
				camaras[4].setObjetivo({cilindro_sel_1->getOrigen()});
			}
			else{
				cilindro_sel_1->setSeleccionado(true);
				camaras[1].setObjetivo({cilindro_sel_1->getCentro()});
				camaras[2].setObjetivo({cilindro_sel_1->getCentro()});
				camaras[3].setObjetivo({cilindro_sel_1->getCentro()});
				camaras[4].setObjetivo({cilindro_sel_1->getCentro()});
			}
		break;
		case 80:
			if (cilindro_sel_2->getSeleccionado()){
				cilindro_sel_2->setSeleccionado(false);
				camaras[1].setObjetivo({cilindro_sel_2->getOrigen()});
				camaras[2].setObjetivo({cilindro_sel_2->getOrigen()});
				camaras[3].setObjetivo({cilindro_sel_2->getOrigen()});
				camaras[4].setObjetivo({cilindro_sel_2->getOrigen()});
			}
			else{
				cilindro_sel_2->setSeleccionado(true);
				camaras[1].setObjetivo({cilindro_sel_2->getCentro()});
				camaras[2].setObjetivo({cilindro_sel_2->getCentro()});
				camaras[3].setObjetivo({cilindro_sel_2->getCentro()});
				camaras[4].setObjetivo({cilindro_sel_2->getCentro()});
			}
		break;
		case 100:
			if (cilindro_sel_3->getSeleccionado()){
				cilindro_sel_3->setSeleccionado(false);
				camaras[1].setObjetivo({cilindro_sel_3->getOrigen()});
				camaras[2].setObjetivo({cilindro_sel_3->getOrigen()});
				camaras[3].setObjetivo({cilindro_sel_3->getOrigen()});
				camaras[4].setObjetivo({cilindro_sel_3->getOrigen()});
			}
			else{
				cilindro_sel_3->setSeleccionado(true);
				camaras[1].setObjetivo({cilindro_sel_3->getCentro()});
				camaras[2].setObjetivo({cilindro_sel_3->getCentro()});
				camaras[3].setObjetivo({cilindro_sel_3->getCentro()});
				camaras[4].setObjetivo({cilindro_sel_3->getCentro()});
			}
		break;
		case 120:
			if (cilindro_sel_4->getSeleccionado()){
				cilindro_sel_4->setSeleccionado(false);
				camaras[1].setObjetivo({cilindro_sel_4->getOrigen()});
				camaras[2].setObjetivo({cilindro_sel_4->getOrigen()});
				camaras[3].setObjetivo({cilindro_sel_4->getOrigen()});
				camaras[4].setObjetivo({cilindro_sel_4->getOrigen()});
			}
			else{
				cilindro_sel_4->setSeleccionado(true);
				camaras[1].setObjetivo({cilindro_sel_4->getCentro()});
				camaras[2].setObjetivo({cilindro_sel_4->getCentro()});
				camaras[3].setObjetivo({cilindro_sel_4->getCentro()});
				camaras[4].setObjetivo({cilindro_sel_4->getCentro()});
			}
		break;
		case 140:
			if (esfera_sel_1->getSeleccionado()){
				esfera_sel_1->setSeleccionado(false);
				camaras[1].setObjetivo({esfera_sel_1->getOrigen()});
				camaras[2].setObjetivo({esfera_sel_1->getOrigen()});
				camaras[3].setObjetivo({esfera_sel_1->getOrigen()});
				camaras[4].setObjetivo({esfera_sel_1->getOrigen()});
			}
			else{
				esfera_sel_1->setSeleccionado(true);
				camaras[1].setObjetivo({esfera_sel_1->getCentro()});
				camaras[2].setObjetivo({esfera_sel_1->getCentro()});
				camaras[3].setObjetivo({esfera_sel_1->getCentro()});
				camaras[4].setObjetivo({esfera_sel_1->getCentro()});
			}
		break;
		case 160:
			if (esfera_sel_2->getSeleccionado()){
				esfera_sel_2->setSeleccionado(false);
				camaras[1].setObjetivo({esfera_sel_2->getOrigen()});
				camaras[2].setObjetivo({esfera_sel_2->getOrigen()});
				camaras[3].setObjetivo({esfera_sel_2->getOrigen()});
				camaras[4].setObjetivo({esfera_sel_2->getOrigen()});
			}
			else{
				esfera_sel_2->setSeleccionado(true);
				camaras[1].setObjetivo({esfera_sel_2->getCentro()});
				camaras[2].setObjetivo({esfera_sel_2->getCentro()});
				camaras[3].setObjetivo({esfera_sel_2->getCentro()});
				camaras[4].setObjetivo({esfera_sel_2->getCentro()});
			}
		break;
		case 180:
			if (esfera_sel_3->getSeleccionado()){
				esfera_sel_3->setSeleccionado(false);
				camaras[1].setObjetivo({esfera_sel_3->getOrigen()});
				camaras[2].setObjetivo({esfera_sel_3->getOrigen()});
				camaras[3].setObjetivo({esfera_sel_3->getOrigen()});
				camaras[4].setObjetivo({esfera_sel_3->getOrigen()});
			}
			else{
				esfera_sel_3->setSeleccionado(true);
				camaras[1].setObjetivo({esfera_sel_3->getCentro()});
				camaras[2].setObjetivo({esfera_sel_3->getCentro()});
				camaras[3].setObjetivo({esfera_sel_3->getCentro()});
				camaras[4].setObjetivo({esfera_sel_3->getCentro()});
			}
		break;
	}

}
