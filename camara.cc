#include "camara.h"
#include "cmath"

#define PI 3.141592

Camara::Camara (Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float bottom, float top, float near, float far){
	
	this->eye = eye;
	this->at = at;
	this->up = up;
	this->tipo = tipo;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;

}

void Camara::rotarXExaminar (float angle){

	std::cout << "eye original :" << eye(0) << "," << eye(1) << "," << eye(2) << std::endl;

	Tupla3f n, u, v, vup, xd;

	float modulo_u, modulo_v, modulo_n;

	float x, y, z, s;

	n = eye - at;

	modulo_n = sqrt(n(0)*n(0) + n(1)*n(1) + n(2)*n(2));

	n = {n(0)/modulo_n, n(1)/modulo_n, n(2)/modulo_n};

	std::cout << "eje z: " << n(0) << "," << n(1) << "," << n(2) << std::endl;

	vup = up - at;

	u = {vup(1) * n(2) - vup(2) * n(1), vup(2) * n(0) - vup(0) * n(2), vup(0) * n(1) - vup(1) * n(0)};

	modulo_u = sqrt(u(0)*u(0) + u(1)*u(1) + u(2)*u(2));

	u = {u(0)/modulo_u, u(1)/modulo_u, u(2)/modulo_u};

	std::cout << "eje x: " << u(0) << "," << u(1) << "," << u(2) << std::endl;

	v = {n(1) * u(2) - n(2) * u(1), n(2) * u (0) - n(0) * u(2), n(0) * u(1) - n(1) * u(0)};

	modulo_v = sqrt(v(0)*v(0) + v(1)*v(1) + v(2)*v(2));

	v = {v(0)/modulo_v, v(1)/modulo_v, v(2)/modulo_v};

	std::cout << "eje y: " << v(0) << "," << v(1) << "," << v(2) << std::endl;

	eye = {producto_escalar(-eye, u, 3), producto_escalar(-eye, v, 3), producto_escalar(-eye, n, 3)};

	//std::cout << "eye escalar :" << eye(0) << "," << eye(1) << "," << eye(2) << std::endl;

	float hip = sqrt(eye(1)*eye(1) + eye(2)*eye(2));

	eye = {eye(0), sin(angle*PI/180)*hip, cos(angle*PI/180)*hip};

	std::cout << "eye en el origen :" << eye(0) << "," << eye(1) << "," << eye(2) << std::endl;

	s = u(0) * v(1) * n(2) + u(1) * v(2) * n(0) + u(2) * v(0) * n(1) - (u(2) * v(1) * n(0) + u(1) * v(0) * n(2) + u(0) * v(2) * n(1));

	x = eye(0) * v(1) * n(2) + u(1) * v(2) * eye(2) + u(2) * eye(1) * n(1) - (u(2) * v(1) * eye(2) + u(1) * eye(1) * n(2) + eye(0) * v(2) * n(1));

	y = u(0) * eye(1) * n(2) + eye(0) * v(2) * n(0) + u(2) * v(0) * eye(2) - (u(2) * eye(1) * n(0) + eye(0) * v(0) * n(2) + u(0) * v(2) * eye(2));

	z = u(0) * v(1) * eye(2) + u(1) * eye(1) * n(0) + eye(0) * v(0) * n(1) - (eye(0) * v(1) * n(0) + u(1) * v(0) * eye(2) + u(0) * eye(1) * n(1));

	x = x/s;

	y = y/s;

	z = z/s;

	eye = {x, y, z};

	std::cout << "eye final " << x << "," << y << "," << z << std::endl;

	up = {producto_escalar(-up, u, 3), producto_escalar(-up, v, 3), producto_escalar(-up, n, 3)};

	hip = sqrt(up(1)*up(1) + up(2)*up(2));

	up = {up(0), cos(angle*PI/180)*hip, sin(angle*PI/180)*hip};

      s = u(0) * v(1) * n(2) + u(1) * v(2) * n(0) + u(2) * v(0) * n(1) - (u(2) * v(1) * n(0) + u(1) * v(0) * n(2) + u(0) * v(2) * n(1));

	x = up(0) * v(1) * n(2) + u(1) * v(2) * up(2) + u(2) * up(1) * n(1) - (u(2) * v(1) * up(2) + u(1) * up(1) * n(2) + up(0) * v(2) * n(1));

	y = u(0) * up(1) * n(2) + up(0) * v(2) * n(0) + u(2) * v(0) * up(2) - (u(2) * up(1) * n(0) + up(0) * v(0) * n(2) + u(0) * v(2) * up(2));

	z = u(0) * v(1) * up(2) + u(1) * up(1) * n(0) + up(0) * v(0) * n(1) - (up(0) * v(1) * n(0) + u(1) * v(0) * up(2) + u(0) * up(1) * n(1));

	x = x/s;

	y = y/s;

	z = z/s;

	float up_normal = sqrt(x*x + y*y + z*z);

	up = {x/up_normal, y/up_normal, z/up_normal};

	std::cout << "up final " << x << "," << y << "," << z << std::endl;

}

void Camara::rotarYExaminar (float angle){

	std::cout << "eye original :" << eye(0) << "," << eye(1) << "," << eye(2) << std::endl;

	Tupla3f n, u, v, vup, xd;

	float modulo_u, modulo_v, modulo_n;

	float x, y, z, s;

	n = eye - at;

	modulo_n = sqrt(n(0)*n(0) + n(1)*n(1) + n(2)*n(2));

	n = {n(0)/modulo_n, n(1)/modulo_n, n(2)/modulo_n};

	std::cout << "eje z: " << n(0) << "," << n(1) << "," << n(2) << std::endl;

	vup = up - at;

	u = {vup(1) * n(2) - vup(2) * n(1), vup(2) * n(0) - vup(0) * n(2), vup(0) * n(1) - vup(1) * n(0)};

	modulo_u = sqrt(u(0)*u(0) + u(1)*u(1) + u(2)*u(2));

	u = {u(0)/modulo_u, u(1)/modulo_u, u(2)/modulo_u};

	std::cout << "eje x: " << u(0) << "," << u(1) << "," << u(2) << std::endl;

	v = {n(1) * u(2) - n(2) * u(1), n(2) * u (0) - n(0) * u(2), n(0) * u(1) - n(1) * u(0)};

	modulo_v = sqrt(v(0)*v(0) + v(1)*v(1) + v(2)*v(2));

	v = {v(0)/modulo_v, v(1)/modulo_v, v(2)/modulo_v};

	std::cout << "eje y: " << v(0) << "," << v(1) << "," << v(2) << std::endl;

	eye = {producto_escalar(-eye, u, 3), producto_escalar(-eye, v, 3), producto_escalar(-eye, n, 3)};

	//std::cout << "eye escalar :" << eye(0) << "," << eye(1) << "," << eye(2) << std::endl;

	float hip = sqrt(eye(1)*eye(1) + eye(2)*eye(2));

	eye = {sin(angle*PI/180)*hip, eye(1), cos(angle*PI/180)*hip};

	std::cout << "eye en el origen :" << eye(0) << "," << eye(1) << "," << eye(2) << std::endl;

	s = u(0) * v(1) * n(2) + u(1) * v(2) * n(0) + u(2) * v(0) * n(1) - (u(2) * v(1) * n(0) + u(1) * v(0) * n(2) + u(0) * v(2) * n(1));

	x = eye(0) * v(1) * n(2) + u(1) * v(2) * eye(2) + u(2) * eye(1) * n(1) - (u(2) * v(1) * eye(2) + u(1) * eye(1) * n(2) + eye(0) * v(2) * n(1));

	y = u(0) * eye(1) * n(2) + eye(0) * v(2) * n(0) + u(2) * v(0) * eye(2) - (u(2) * eye(1) * n(0) + eye(0) * v(0) * n(2) + u(0) * v(2) * eye(2));

	z = u(0) * v(1) * eye(2) + u(1) * eye(1) * n(0) + eye(0) * v(0) * n(1) - (eye(0) * v(1) * n(0) + u(1) * v(0) * eye(2) + u(0) * eye(1) * n(1));

	x = x/s;

	y = y/s;

	z = z/s;

	eye = {x, y, z};

	std::cout << "eye final " << x << "," << y << "," << z << std::endl;

	up = {producto_escalar(up, u, 3), producto_escalar(up, v, 3), producto_escalar(up, n, 3)};

	hip = sqrt(up(1)*up(1) + up(2)*up(2));

	up = {sin(angle*PI/180)*hip, up(1), cos(angle*PI/180)*hip};

      s = u(0) * v(1) * n(2) + u(1) * v(2) * n(0) + u(2) * v(0) * n(1) - (u(2) * v(1) * n(0) + u(1) * v(0) * n(2) + u(0) * v(2) * n(1));

	x = up(0) * v(1) * n(2) + u(1) * v(2) * up(2) + u(2) * up(1) * n(1) - (u(2) * v(1) * up(2) + u(1) * up(1) * n(2) + up(0) * v(2) * n(1));

	y = u(0) * up(1) * n(2) + up(0) * v(2) * n(0) + u(2) * v(0) * up(2) - (u(2) * up(1) * n(0) + up(0) * v(0) * n(2) + u(0) * v(2) * up(2));

	z = u(0) * v(1) * up(2) + u(1) * up(1) * n(0) + up(0) * v(0) * n(1) - (up(0) * v(1) * n(0) + u(1) * v(0) * up(2) + u(0) * up(1) * n(1));

	x = x/s;

	y = y/s;

	z = z/s;

	float up_normal = sqrt(x*x + y*y + z*z);

	up = {x/up_normal, y/up_normal, z/up_normal};

	std::cout << "up final " << x << "," << y << "," << z << std::endl;

}

void Camara::rotarZExaminar (float angulo){

	float hip = sqrt(eye(0)*eye(0) + eye(1)*eye(1));

	mover(sin(angulo)*hip, cos(angulo)*hip, eye(2));

}

void Camara::setObserver(){

	gluLookAt(eye(0), eye(1), eye(2), at(0), at(1), at(2), up(0), up(1), up(2));

}

void Camara::setProyeccion(){

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

	if (tipo)
		glFrustum(left, right, bottom, top, near, far);
	else 
		glOrtho(left, right, bottom, top, near, far);

	//std::cout << "left: " << left << " right: " << right << " bottom: " << bottom << " top: " << top << std::endl;

}

void Camara::mover(float x , float y , float z){

	this->eye = Tupla3f(x, y, z);

}

float Camara::producto_escalar(Tupla3f v1, Tupla3f v2, int d)
{
	float resultado = 0;

	for (int i=0; i < d; i++) {
		resultado += v1(i) * v2(i);
	}
	return resultado;
}

void Camara::zoom (float factor){

	//std::cout << "left: " << left << " right: " << right << " bottom: " << bottom << " top: " << top << std::endl;

    if(factor > 0){
        left *= factor;
        right *= factor;
        bottom *= factor;
        top *= factor;
    }else{
        left /= -factor;
        right /= -factor;
        bottom /= -factor;
        top /= -factor;
    }

	//std::cout << "left: " << left << " right: " << right << " bottom: " << bottom << " top: " << top << std::endl;


}

void Camara::redimensionar(int newWidth, int newHeight){

   this->top = 0.84*near;
   this->bottom = -this->top;
   this->right = newWidth/newHeight * this->top;
   this->left = -this->right;

}
