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
#include<stdio.h>
#include <cmath>
#include<string>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

//
using namespace std;

//my own obj type
class myObj{
public:
	string shape;
	 //position x y and z is the position we paint  this object at.(x,y,z)
	GLdouble position[3];
	// rotation x y and z is the degree of angle that rotates around this axis.
	//for example rotaionx=90 means rotate 90 degress around x angle
	//rotation direction is rom y axis to z axis
	GLdouble rotation[3];
	//scale of x and y and z.
	GLdouble scale[3];
	//default color, any object with color setting will not be effected
	GLdouble color[3];
	//constructor
	//default shape is cube (just for preventing erros)
	myObj() {
		shape = "cube";
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
	//set the shape of object
	myObj(string s) {
		//error prevention
		if (s != "cube" || s != "cylinder" || s != "cuboid" || s != "sphere") shape = "cube";
		shape = s;
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
	~myObj() {};
	//the object paints itself according to the position
	//rotation, and scale
	

	void setter(char command, GLdouble x, GLdouble y, GLdouble z) {
		//cout << "setter called" << endl;
		switch (command)
		{
		case'w':
			position[0] = x;
			position[1] = y;
			position[2] = z;
			//cout << "positions: " << position[0] << " " << position[1] << " " << position[3] << endl;
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
		case'n':
			break;
		default:
			break;
		}
	}

	//this outputs my shape, position, rotation, and scale, and color
	//i can use this to out put to a file.
	string tostring() {
		string ans="";
		string line[5];
		//reference:
		//http://www.cplusplus.com/reference/cstdio/sprintf/
		//sprintf buffer
		//why did I waste time on this?
		char *buf = new char[50];
		line[0] = "shape: " + shape + "\n" + "position: ";

		sprintf(buf, "position: %1.2f %1.2f %1.2f \n", double(position[0]), double(position[1]), double(position[2]));
		line[1]= std::string(std::move(buf));
		
		sprintf(buf, "rotation: %1.2f %1.2f %1.2f \n", double(rotation[0]), double(rotation[1]), double(rotation[2]));
		line[2] = std::string(std::move(buf));

		sprintf(buf, "scale: %1.2f %1.2f %1.2f \n", double(scale[0]), double(scale[1]), double(scale[2]));
		line[3] = std::string(std::move(buf));

		sprintf(buf, "color: %1.2f %1.2f %1.2f \n", double(color[0]), double(color[1]), double(color[2]));
		line[4] = std::string(std::move(buf));

		ans = line[0] + line[1] + line[2] + line[3] + line[4];
		return ans;
	}
};
	



#endif