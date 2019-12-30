#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"

GLfloat gx = 0.0, gy = 0.0;
bool keyStatus [256];
Configuration config;
Moviment moviment;

bool isInsideSquare(double x, double y){
	double dl = config.getSquare().resized;
	if(x >=gx && x <= gx + dl && y >= gy && y <= gy + dl)
		return true;
	return false;
}

void display(void){
	glClear (GL_COLOR_BUFFER_BIT);
	double dl = config.getSquare().resized;
	glColor3f(config.getSquare().color.red,config.getSquare		().color.green,config.getSquare().color.blue);
	if(moviment.squareStatus){
		glBegin(GL_POLYGON);
			glVertex3f(gx, gy,0.0);
			glVertex3f(gx + dl, gy,0.0);
			glVertex3f(gx + dl, gy + dl,0.0);
			glVertex3f(gx, gy + dl,0.0);
		glEnd();
	}
	
	glutSwapBuffers();
}

void init(void){
	glClearColor(config.getWindow().background.red,config.getWindow().background.green,config.getWindow().background.blue,0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

void keyPress(unsigned char key, int x, int y){
	keyStatus[key] = true;
	glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
	keyStatus[key] = false;
}

void idle(void){
	if(keyStatus['s'] || keyStatus['S'])
		gy-=0.01;
	if(keyStatus['w'] || keyStatus['W'])
		gy+=0.01;
	if(keyStatus['a'] || keyStatus['A'])
		gx-=0.01;
	if(keyStatus['d'] || keyStatus['D'])
		gx+=0.01;
	if(keyStatus[' ']){
		gx = 0;
		gy = 0;
	}
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y){	
	double x1 = x/((double) config.getWindow().width);
	double y1 = (config.getWindow().height-y)/((double)config.getWindow().height);
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN)
			printf("clique\n");
		if(!moviment.squareStatus && state == GLUT_DOWN){ 
			moviment.squareStatus = true;
			printf("clique esquerdo aperto %f %f\n", x1,y1);
			gx = x1 - config.getSquare().resized/2;
			gy = y1 - config.getSquare().resized/2;
		}
		if(state == GLUT_DOWN && isInsideSquare(x1,y1)){
			moviment.leftButtonDown = true;
			moviment.dx = x1 - gx;
			moviment.dy = y1 - gy;
			
		}
	}
	else if(button == GLUT_RIGHT_BUTTON && isInsideSquare(x1,y1) && state == GLUT_DOWN){
		moviment.squareStatus = false;
	}
	if(state == GLUT_UP){
		moviment.leftButtonDown = false;
		printf("clique solto\n");
	}
}

void mouseMoviment (int x, int y){
	double x1 = x/((double)config.getWindow().width);
	double y1 = (config.getWindow().height-y)/((double) config.getWindow().height);
	if(moviment.leftButtonDown){
		gx = x1 - moviment.dx;
		gy = y1 - moviment.dy;
	}
}

