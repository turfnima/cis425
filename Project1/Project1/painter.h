#pragma once
//Xiaozhi Li
//
//references:
/*I used function pointer, which is something I don't fully understand
so this is the tutorial I saw
https://www.cprogramming.com/tutorial/function-pointers.html
*/

#ifndef __PAINTER_H_INCLUDED__   // if x.h hasn't been included yet...
#define __PAINTER_H_INCLUDED__
#include <cstdlib>
#include <vector>
//includes any dependencies.
#include <iostream>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

//
using namespace std;

class Painter {
public:
	//attributes
	// position x y and z is the position we paint  this object at.(x,y,z)
	GLdouble position[3];
	// rotation x y and z is the degree of angle that rotates around this axis.
	//for example rotaionx=90 means rotate 90 degress around x angle
	//rotation direction is rom y axis to z axis
	GLdouble rotation[3];
	//scale of x and y and z.
	GLdouble scale[3];
	//default color, any object with color setting will not be effected
	GLdouble color[3];
	//
	Painter() {
		//initialize for any object we paint.
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;

		rotation[0] = 0;
		rotation[1] = 0;
		rotation[2] = 0;

		scale[0] = 1;
		scale[1] = 1;
		scale[2] = 1;

		color[0] = 1.0;
		color[1] = 0.0;
		color[2] = 0.0;
	}
//prototypes
	void setter(char command, GLdouble x, GLdouble y, GLdouble z);
	GLdouble getter(char command, char axis);
	void paintIt( void *func_name);
	void paintIt(int size);
	//destructor
	~Painter() {}
};


//change values
// there are three command, 'w' means location, 'e' means rotation
//'r' means rescale, 
//this idea is taken from 3d studio ma[0] and unity3d (sort of common setting)
void Painter::setter(char command, GLdouble x, GLdouble y, GLdouble z) {

	switch (command)
	{
	case'w':
		position[0] = x;
		position[1] = y;
		position[2] = z;
		break;
	case'e':
		rotation[0] = x;
		rotation[1] = y;
		rotation[2] = z;
		break;
	case'r':
		//resize can have weird things, because resizing something to negative is funny.
		scale[0] = x;
		scale[1] = y;
		scale[2] = z;
			break;
	default:
		break;
	}
}
//take the 'w', 'e','r', command, and 'x', 'y', 'z', axis, and
//return the value.
GLdouble Painter::getter(char command, char axis) {
	string temp1 = "";
	
	int tempAxis = -1;
	GLdouble result;

	switch (axis) {
	case'x':
		tempAxis = 0;
		break;
	case'y':
		tempAxis = 1;
		break;
	case'z':
		tempAxis = 2;
		break;
	default:
		cout << "error in painter::getter: the axis is unclear" << endl;
		break;
	}
	switch (command) {
	case'w':
		temp1 = "position";
		result = position[tempAxis];
		break;
	case'e':
		temp1 = "rotation";
		result = rotation[tempAxis];
		break;
	case'r':
		temp1 = "scale";
		result = scale[tempAxis];
		break;
	default:
		cout << "error: there is no command for char \nin getter, the current command is "<<command << endl;
		return -404;
	}
	printf("getter the value type is %s at %s axis\n", temp1, axis);
	cout << "getter: the value  is " << result << endl;
	return result;
}
//never used *func_name before
//I am playing with fire.
//reference:https://www.cprogramming.com/tutorial/function-pointers.html
void Painter::paintIt( void *func_name) {
	//load in all the x,y,z for this object and tranlated, rotate, scale it.
	glPushMatrix();
	glScalef(this->scale[0], this->scale[1], this->scale[2]);
	glRotatef(this->rotation[2], 0, 0, 1);
	glRotatef(this->rotation[1], 0, 1, 0);
	glRotatef(this->rotation[0], 1, 0, 0);
	glTranslatef(this->position[0],this->position[1],this->position[2]);
	//I should have an exception handler here, 
	//but I don't know how to tell the difference of functions yet
	//save that for next versions.
	func_name;
	glPopMatrix();
}

void Painter::paintIt(int size) {
	//load in all the x,y,z for this object and tranlated, rotate, scale it.
	glPushMatrix();
	glScalef(this->scale[0], this->scale[1], this->scale[2]);
	glRotatef(this->rotation[2], 0, 0, 1);
	glRotatef(this->rotation[1], 0, 1, 0);
	glRotatef(this->rotation[0], 1, 0, 0);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	//I should have an exception handler here, 
	//but I don't know how to tell the difference of functions yet
	//save that for next versions.
	glutSolidCube(size);
	glPopMatrix();
}
#endif