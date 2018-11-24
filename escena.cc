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
    //obj_jer = new ObjJerarquico();
    torito = new ObjJerarquico();
    yunque = new Yunque();
    //cuenco = new Cuenco(10, 10); //-> los parámetros son el numero de puntos del perfil y el numero de instancias a generar

    luz1 = new Luz (GL_LIGHT0, Tupla4f(0.0,0.0,1.0,0.0), Tupla4f(0.0,0.0,0.0,1.0), Tupla4f(1.0,1.0,1.0,1.0), Tupla4f(1.0,1.0,1.0,1.0));
    luz2 = new Luz (GL_LIGHT1, Tupla4f(0.0,0.0,5.0,1.0), Tupla4f(0.0,0.0,0.0,1.0), Tupla4f(1.0,0.0,1.0,1.0), Tupla4f(1.0,0.0,1.0,1.0));

    // .......completar: ...
    // .....

    num_objetos = 8 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
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
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   break;

	case 3:
	   
	   // modo ajedrez
	   //glShadeModel(GL_FLAT);
	   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   break;
   }

   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {
      case 0:
       if ( cubo != nullptr ) cubo->draw(modo, visualizacion) ;
       break ;
      case 1:
         //  ......completar un caso por cada objeto que se haya creado
	 if (tetraedro != nullptr) tetraedro->draw(modo, visualizacion);
	 break;
      case 2:
	 if (cono != nullptr) cono->draw(modo, visualizacion);
	 break;
      case 3:
	 if (cilindro != nullptr) cilindro->draw(modo, visualizacion);
	 break;
      case 4:
	 if (esfera != nullptr) esfera->draw(modo, visualizacion);
	 break;
      case 5:
	 if (ply != nullptr) ply->draw(modo, visualizacion);
	 else if (obj_rev != nullptr) obj_rev->draw(modo, visualizacion);
	 break;
	//case 6:
	// if (obj_jer != nullptr) obj_jer->draw(modo, visualizacion);
	// break;
	case 7: 
	 if (yunque != nullptr) yunque->draw(modo, visualizacion);
	 break;
	case 6:
	 if (torito != nullptr) torito->draw(modo, visualizacion);
	 break;
	case 8:
	 if (cuenco != nullptr) cuenco->draw(modo, visualizacion);
	 break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
       break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  	ejes.draw();
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
	 visualizacion = 3;
	 cout << "Modo de visualización: ajedrez" << endl;
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
	case '7' :
	 objeto_actual = 6;
	 cout << "Objeto jerárquico" << endl;
	 break;
	case 'a' :
	 	this->conmutarAnimaciones();
	 break;
	case 'p' :
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
	case '8' :
	 //objeto_actual = 7;
	 //cout << "Objeto: yunque" << endl;
	break;
	case '9' :
	 //objeto_actual = 8;
	 //cout << "Objeto: cuenco" << endl;
	 break;
	case 'w' :
	 sombreado = (sombreado + 1) % 2;
	 break;
	case 'j' :
	 luz1->activar();
	 break;
	case 'k' :
	 luz2->activar();
	 break;
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
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

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane,
   wx = ratio_xy*wy ;
   glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width = newWidth;
   Height = newHeight;
   change_projection( float(Width)/float(Height) );
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
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

void Escena::mgeDesocupado(){
	if (objeto_actual == 6){
		//obj_jer->actualizarEstado();
		torito->actualizarEstado();
	}
	luz2->girar();
	glutPostRedisplay();
}

void Escena::conmutarAnimaciones(){

	 animado = !animado;

	 if (animado){
		if (objeto_actual == 6){
	 		//obj_jer->inicioAnimaciones();
	 		torito->inicioAnimaciones();
		}
		luz2->inicioAnimaciones();
	 	glutIdleFunc( funcion_desocupado );
	 }else
		glutIdleFunc( nullptr );
}

