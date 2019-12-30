#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"
#include <math.h>
#include <vector>

GLfloat gx = 0.0, gy = 0.0;
bool keyStatus [256];
Configuration config;
//Moviment moviment; //Não utilizado neste trabalho.

void drawCircle(Circle circle, float cx, float cy){
	float x, y;
	float dx = circle.cx - cx;
	float dy = circle.cy - cy;
	glColor3f(circle.color.red, circle.color.green, circle.color.blue);
	glBegin(GL_POLYGON);
		for(int i = 0; i<360;i++){
			x = circle.r*cos(M_PI*i/180.0) + dx;
			y = (circle.r*sin(M_PI*i/180.0) + dy);
			glVertex2f(x,y);
		}
	glEnd();
}

void drawRect(Rect rect, float cx, float cy){
 	float dx = rect.x - cx;
	float dy = rect.y - cy;
	glColor3f(rect.color.red, rect.color.green, rect.color.blue);
	glBegin(GL_QUADS);
		glVertex2f(dx, dy);
		glVertex2f(dx + rect.width, dy);
		glVertex2f(dx + rect.width, dy + rect.height);
		glVertex2f(dx, dy + rect.height);
	glEnd();
}

bool isInsideSquare(double x, double y){
	double dl = config.square.resized;
	if(x >=gx && x <= gx + dl && y >= gy && y <= gy + dl)
		return true;
	return false;
}

void display(void){
	int cx = config.arena.outsideCircle.cx;
	int cy = config.arena.outsideCircle.cy;
	glClear (GL_COLOR_BUFFER_BIT);
	drawCircle(config.arena.outsideCircle, cx, cy);
	drawCircle(config.arena.insideCircle, cx, cy);
	drawRect(config.arena.line, cx, cy);
	drawCircle(config.arena.player, cx, cy);
	for(std::vector<Circle>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		drawCircle(*it, cx, cy);
	}
	glutSwapBuffers();
}

void init(void){
	Window window = config.window;
	glClearColor(window.background.red,window.background.green,window.background.blue,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-window.width/2.0,window.width/2.0, window.height/2.0,-window.height/2.0, -1.0,1.0);
}

void keyPress(unsigned char key, int x, int y){
	keyStatus[key] = true;
	glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
	keyStatus[key] = false;
}

float euclidianDistancePointCircle (float cx, float cy, Circle circle){
	return sqrt(pow(cx - circle.cx,2) + pow(cy - circle.cy,2));
}

bool itCollides(float cx,float cy, int r){
	Arena arena = config.arena;
	if(euclidianDistancePointCircle(cx, cy, arena.outsideCircle) > arena.outsideCircle.r - r)
		return true;
	if(euclidianDistancePointCircle(cx, cy, arena.insideCircle) < r + arena.insideCircle.r)
		return true;
		for(std::vector<Circle>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
			if(euclidianDistancePointCircle(cx, cy, *it) < r + (*it).r)
				return true;
		}
	return false;
}

void moveX(float increment){
	Circle player = config.arena.player;
	float cx = player.cx + increment;
	if(!itCollides(cx, player.cy, player.r))
		config.arena.player.cx = cx;
	return;
}

void moveY(float increment){
	Circle player = config.arena.player;
	float cy = player.cy + increment;
	if(!itCollides(player.cx, cy, player.r))
		config.arena.player.cy = cy;
	return;
}
void idle(void){
	float increment = 1;
	if(keyStatus['s'] || keyStatus['S'])
		moveY(increment);
	if(keyStatus['w'] || keyStatus['W'])
		moveY(-increment);
	if(keyStatus['a'] || keyStatus['A'])
		moveX(-increment);
	if(keyStatus['d'] || keyStatus['D'])
		moveX(increment);
	if(keyStatus[' ']){
		gx = 0;
		gy = 0;
	}
	glutPostRedisplay();
}

/*Não utilizadas nesse trabalho, guardar para os próximos
void mouse(int button, int state, int x, int y){
	double x1 = x/((double) config.window.width);
	double y1 = (config.window.height-y)/((double)config.window.height);
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN)
			printf("clique\n");
		if(!moviment.squareStatus && state == GLUT_DOWN){
			moviment.squareStatus = true;
			printf("clique esquerdo aperto %f %f\n", x1,y1);
			gx = x1 - config.square.resized/2;
			gy = y1 - config.square.resized/2;
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
	double x1 = x/((double)config.window.width);
	double y1 = (config.window.height-y)/((double) config.window.height);
	if(moviment.leftButtonDown){
		gx = x1 - moviment.dx;
		gy = y1 - moviment.dy;
	}

}
*/
