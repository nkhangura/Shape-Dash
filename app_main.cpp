#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <GLUT/glut.h>
#include "SOIL.h"


using namespace std;
void print();
// Store the width and height of the window
int width = 1400, height = 700;

float my_y = -1;
float my_x = -1.6;
float eL = .2;
float red = 1;
float green = 1;
float blue = 1;
bool run = false;
float r = 0;
int score = 0; 

float t1 = -.5, t2 = -1, t3 = 1.4;



// A function to draw the scene
void createShapes() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background  to black
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(red,green,blue-1);
	glBegin(GL_POLYGON);
	glVertex2f(my_x,my_y);
	glVertex2f(my_x-eL,my_y);
	glVertex2f(my_x-eL,my_y+eL);
	glVertex2f(my_x,my_y+eL);
	glEnable(GL_DEPTH_TEST);
	glEnd();

	glColor3f(red,green-1,blue);
	glBegin(GL_POLYGON);
	glVertex2f(t1,t2 );
	glVertex2f(t1 +.1,t2+eL);
	glVertex2f(t1+eL,t2);
	glEnable(GL_DEPTH_TEST);
	glEnd();

	glColor3f(red-1,green,blue);
	glBegin(GL_POLYGON);
	glVertex2f(t3,t2 );
	glVertex2f(t3 +.1,t2+eL);
	glVertex2f(t3+eL,t2);
	glEnable(GL_DEPTH_TEST);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

// A function to convert window coordinates to scene
//x, y - the coordinates to be updated
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}


// A function to handle window resizing
// Called every time the window is resized
void appReshapeFunc(int w, int h) {
	// Window size
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// x-axis and y-axis range
	const double appXmin = -1.0;
		const double appYmin = -1.0;
	const double appXmax = 1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void MouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);
	if(s==0){
		run = !run;
		
	}
	glutPostRedisplay(); 	// so that the changes above get implemented.
}


//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
//-------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y) {
	// Define what should happen for a given key press 
	switch (key) {
		// Escape to quit the program
		case ' ':
			my_x = my_x + .4;
			my_y = my_y + .30;
			score = score + 1;
			break; 
		case 27:
			exit(0);
			break;
		
		}
	glutPostRedisplay();
}

void KeyboardReleaseFunc(unsigned char key, int x, int y) {
	switch (key) {
		case ' ':
			my_x = my_x + .10;
			my_y = my_y -.30;
			if(my_y > -.5){
				my_y = -.8;
			}
			//cout<<my_y<<endl;
			glutPostRedisplay();
	}
} 
/*
void display(){
	print();
	glutPostRedisplay();
}

void renderBitMap(float x, float y, void *font, char *string){
	char *c;
	glRasterPos2f(x,y);
	for(c = string; *c != '\0'; c++){
		glutBitmapCharacter(font, *c);
	}
}

void print(){
	glColor3b(1,1,1);
	char string[100] = {0};
	snsprintf(string, "----Test-----");
	//sprintf_s(string,"----Test----");
	renderBitMap(-40,80,GLUT_BITMAP_TIMES_ROMAN_24,string);
}
 */


void idle(){
	if(run){
		my_x += 0.033;
		/*if(my_x <= (t1+.04) && my_x >= (t1-.04)){
			cout<< "You LOST" <<endl;
			cout<<my_x<<endl;
			//run = !run; 
			//my_x = -1.4;
		} */
		if(my_x >= (t1-.033) && my_x <= (t1+.233) ){
			cout<< "You LOST" <<endl;
			cout<<"Score: "<<score<<endl;
			run = !run; 
			my_x = -1.7;
			score = 0;
			//my_x = -1.4;
			glutPostRedisplay();
		}
		if(my_x >= (t3-.033) && my_x <= (t3+.233)){
			cout<< "\nYou LOST" <<endl;
			cout<<"Score: "<<score<<"\n"<<endl;
			run = !run; 
			my_x = -1.7;
			score = 0;
			//my_x = -1.4;
			glutPostRedisplay();
		}


		if(my_x >1.99){
			my_x = -1.7;
			r = (rand() % 10) +1;
			r = r / 10;
			t1 = t1 + r;
			if(t1 > 1.6){
				t1 = -.5;
			}
		
			r = (rand() % 10) +1;
			r = r / 10;
			t3 = t3 - r;
			if(t3 < -.1){
				t3 = 1.4;
			}

	/*		int x = t1 - t3;
			x = abs(x); */
			if(t1 > (t3 -.6)){
				t1 = -.4;
				t3 = 1.5;
			}

		}
		glutPostRedisplay();
	}
	if(my_y > -.5){
		my_y = -.8;
	}
	//run = !run;
	//my_x = -1.4;
	glutPostRedisplay();
}


int main(int argc, char** argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window 
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width-1, height-1);

	// Create the window
	glutCreateWindow("OpenGL Project");

	// Set callback for drawing the scene
	glutDisplayFunc(createShapes);

	//for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// to handle mouse clicks
	glutMouseFunc(MouseFunc);

	//to handle keyboad events
	glutKeyboardFunc(KeyboardFunc);

	// triggered when we release a keyboard key.
	glutKeyboardUpFunc(KeyboardReleaseFunc);

	// Set idle function. It gets called repeatly all the time
	glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}
