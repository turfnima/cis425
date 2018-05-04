//Xiaozhi Li
//CIS 425 CAD project (final project)
//april 07 2018
/*description:
basic functions:
Type: a CAD tool
Target: a CAD tool that utilizes 3d shaped objects and can export and import files. It has multiple windows to visualize the object in creation.

Details£»
There will be buttons on the side, which generates objects in the center as described.
There will have multiple objects to be chosen from, a sphere, a cylinder, a cube, a cuboid.
Each of these objects can have their dimension changed (the sphere and cylinder should have their slices and stacks changed), by clicking on them, and then presses some button.
Each of these objects can be turned around, by keyboard.
Each of these objects can be moved around, in 3d space.
There will be at least 3 windows, each looks at the scene from a different angle.
There should be a reasonable limit of the maximum objects one can have in the scene.
The objects, and the coordinates of the objects, can be exported out into a file.
Should the exported file exist, the program can read it and extract the same object file and print it to the scene.


build 0.1:
a opengl screen, using double buffer, and depth buffer.
painter class:
a class that holds the information of the objects that gets to be print
	attributes within this class the object's x,y,z location, x,y,z rotation, x,y,z scale
	attributes within this calss that holds the color
	I will start use glcube first
keyInput: a key changed location and rotatioin change
		  mouse drag that changes location and rotation
grid at center:
   could visually help, a standard thing with CAD design.
*/
#pragma once

#include <iostream>
#include<math.h>
//vector for vector
#include <cstdlib>
#include <vector>
#include<iterator>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

//my header files
#include"painter.h"
//
using namespace std;

//prototypes:
void keyInput(unsigned char key, int x, int y);
void printInteraction(void);
void setup(void);
void drawScene();
void drawSceneSmall();


//values for window
static double window_w = 800, window_h = 800;
static double window_position_x = 100, window_position_y = 100;

//values for ortho view
static double view_w = 20, view_h = 20, view_d = 90;

//lists of objects for printing
vector<myObj> paintPipe;
vector<myObj>::iterator it1;
myObj *a = new myObj("cube");
myObj *b = new myObj("sphere");
bool load = false;

//select and drag
//closest hit
//from BallAndTorusPicking
int closestName;
static unsigned int buffer[1024]; // Hit buffer.
static int hits; // Number of entries in hit buffer.
bool isSelecting = false;
int isDragging = 0;
bool ortho = false;

//values for w, e, r command
static char command = 'n';
static double cx, cy, cz;
//vector <Painter> listObj;
//key inputs
void keyInput(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	//basic translation, rotation, scale
	case 'w':
		command = 'w';
		glutPostRedisplay();
		break;
	case'e':
		command = 'e';
		glutPostRedisplay();
		break;
	case'r':
		command = 'n';
		glutPostRedisplay();
		break;
	case'a':
		cx = cx+0.5;
		glutPostRedisplay();
		break;
	case'd':
		cx = cx-0.5;
		glutPostRedisplay();
		break;
	//end of translation, rotation, scale
	default:
		break;
	}
}

//for select and drag
// Process hit buffer to find record with smallest min-z value.
//Copied (almost) exactly from BallAndTorusPicking
void findClosestHit(int hits, unsigned int buffer[])
{
	unsigned int *ptr, minZ;

	minZ = 0xffffffff; // 2^32 - 1
	ptr = buffer;
	closestName = 0;
	for (int i = 0; i < hits; i++)
	{
		ptr++;
		if (*ptr < minZ)
		{
			minZ = *ptr;
			ptr += 2;
			closestName = *ptr;
			ptr++;
		}
		else ptr += 3;
	}
} // end findClosestHit


  //The mouse callback routine.
  //based on BallAndTorusPicking pickFunction
void pickFunction(int button, int state, int x, int y)
{
	int viewport[4]; // Viewport data.

					 // Don't react unless left button is pressed.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport data.
		glSelectBuffer(1024, buffer); // Specify buffer to write hit records in selection mode
		(void)glRenderMode(GL_SELECT); // Enter selection mode.
									   //**************  Set new viewing volume ***********
									   // Save the viewing volume defined in the setProjection routine,
									   // the real projection matrix for rendering
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		// Define a viewing volume corresponding to selecting in 2 x 2 region around the cursor.
		glLoadIdentity();
		gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);
		cout << "x= " << x << "  y= " << y << endl;
		//real projection used, copied from setProjection
		//DON'T load identity here
		if(ortho)
			glOrtho(-view_w, view_w, -view_h, view_h, -view_d, view_d);
		else
			gluPerspective(120.0, double(window_w) / double(window_h), 1, 300);
	


		glMatrixMode(GL_MODELVIEW); // Return to modelview mode before drawing.
		glLoadIdentity();

		
		glInitNames(); // Initializes the name stack to empty.
		glPushName(0); // Puts name 0 on top of stack.


		isSelecting = 1;
		drawSceneSmall();

		hits = glRenderMode(GL_RENDER); // Return to rendering mode, returning number of hits.
										// Determine closest of the hit objects (if any).
										// closest object name will be saved in closestName.
		findClosestHit(hits, buffer);

		//if red cube was hit, start dragging.
		if (closestName >0) //clicked on red cube
			isDragging = closestName;

		cout << "closest hit==" << closestName << endl;
		// -------------- - END OF Selecting--------------

		//back to drawing mode
		// Restore viewing volume of the resize routine and return to modelview mode.
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isDragging = 0;
	}
}

//void sePerspective(void) {
//	//view box
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	if (ortho)
//		glOrtho(-view_w, view_w, -view_h, view_h, -view_d, view_d);
//	else
//		gluPerspective(120.0, double(window_w) / double(window_h), 1, 300);
//}

//print interaction to the console (i dont think i need this for actual build)
void printInteraction(void) {
	cout << "welcome to my CAD 0.1 version" << endl;
	cout << "press 'w' for position transform." << endl;
	cout << "press 'e' for rotation transform." << endl;
	cout << "press 'r' for rescaling (does not work ATM)" <<endl;
	
	cout << "press 'a' and 'd' to adjust the y value of the transform you picked" << endl;
	cout << "future versions will have more functions" << endl;
}

void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
}



void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ortho)
		glOrtho(-view_w, view_w, -view_h, view_h, -view_d, view_d);
	else
		gluPerspective(120.0, double(window_w) / double(window_h), 1, 300);

	
	glMatrixMode(GL_MODELVIEW);
}



//load the objects into paintPipe
void loadObj() {
	a->setter('w', 1, 1, -1);
	b->setter('w', -1, -1, -1);
	paintPipe.push_back((*b));
	paintPipe.push_back((*a));
	load = true;
}

void drawSceneTest() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(1, 0, 0);
	cout << cx << " " <<cy<< " " << cz<<" " << endl;
	
	glLoadIdentity();



	glDisable(GL_DEPTH_TEST);
}
void paintIt(myObj  ob) {
	glPushMatrix();
	glColor3f(ob.color[0], ob.color[1], ob.color[2]);
	glTranslatef(ob.position[0], ob.position[1], ob.position[2]);
	glRotatef(ob.rotation[2], 0, 0, 1);
	glRotatef(ob.rotation[1], 0, 1, 0);
	glRotatef(ob.rotation[0], 1, 0, 0);
	glScalef(ob.scale[0], ob.scale[1], ob.scale[2]);
	//I should have an exception handler here, 
	//but I don't know how to tell the difference of functions yet
	//save that for next versions.
	if (ob.shape == "cube") {
		//cout << "cube" << endl;
		glutSolidCube(1);
	}
	else if (ob.shape == "sphere") {
		//cout << "sphere" << endl;
		glutSolidSphere(1, 15, 15);
	}
	glPopMatrix();
}

void drawSceneSmall() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	it1 = paintPipe.begin();
	int i = 1;
	/*paintPipe[0].setter('w', -1, -1, 0);
	paintPipe[1].setter('w', 1, 1, 0);*/
	while ( it1 != paintPipe.end()) {
	if (isSelecting) glLoadName(i);
	paintIt(*it1);
	i++;
	it1++;
}


	glLoadIdentity();
	gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
	//gluLookAt(meX, meY, meZ, meX + sin(angle*PI / 180), meY + headAngle * PI / 180, meZ + cos(angle*PI / 180), 0, 1, 0);
	//cout<<paintPipe[0].tostring();
	
	glDisable(GL_DEPTH_TEST);
	
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	isSelecting = 0;
	drawSceneSmall();

	if (isSelecting) {
		glPopName();
		//cout << "is selecting" << endl;
	}
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	//window
	glutInitWindowSize(window_w, window_h);
	glutInitWindowPosition(window_position_x, window_position_y);
	//create window
	glutCreateWindow("CAD-Caesar assisted design");
	setup();
	glutReshapeFunc(resize);

	if (!load) loadObj();
	glutDisplayFunc(drawScene);

	glutKeyboardFunc(keyInput);
	glutMouseFunc(pickFunction);
	glutMainLoop();
	return 0;
}