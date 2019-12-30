#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "graphics.h"
#include "glutFunctions.h"
#include <math.h>
#include <vector>

bool keyStatus [256];
Configuration config;
Chrono chrono;
void *font1 = GLUT_BITMAP_9_BY_15;
void *font2 = GLUT_BITMAP_TIMES_ROMAN_24;

void display(void){
	Player player = config.arena.player;
	int cx = player.circle.cx - config.arena.outsideCircle.cx;
	int cy = player.circle.cy - config.arena.outsideCircle.cy;
	float y = player.car.body.height/2;
	float z = -player.car.body.depth*0.7;
	float tetaCarR = player.movement.tetaCarR;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,2.5,2,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 500, 500, 200);
	gluLookAt(cx - sin(tetaCarR)*y,cy + cos(tetaCarR)*y, z, cx - sin(tetaCarR)*2*player.circle.r, cy + cos(tetaCarR)*2*player.circle.r,z, 0.0,0.0,-1.0);
	drawScene();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1.0,1.3,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, 500, 500);
	switchCamera(config.cam);
	drawScene();

	//Mini-mapa
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(250,0,250,250);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-125,125,-125,125,-1,-1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1,0,0);
	int cam2 = config.cam;
	config.cam = 6;
	glPushMatrix();
		glScalef(0.00285f,-0.00285f,0.1f);
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		drawScene();
		glPopAttrib();
	glPopMatrix();
	config.cam = cam2;
	glutSwapBuffers();
}

void init(void){
	Window window = config.window;
	glClearColor(window.background.red,window.background.green,window.background.blue,0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void keyPress(unsigned char key, int x, int y){
	keyStatus[key] = true;
	glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
	keyStatus[key] = false;
}

void idle(void){
	float increment = config.speed.carSpeed;
	float incrementX = 2;
	if(config.win!= -1){
		if(keyStatus['s'] || keyStatus['S'])
			moveY(&config.arena.player, &config.arena.player.movement, increment, false);
		if(keyStatus['w'] || keyStatus['W'])
			moveY(&config.arena.player, &config.arena.player.movement,-increment, false);
		if(keyStatus['a'] || keyStatus['A'])
			moveX(&config.arena.player.movement,-incrementX);
		if(keyStatus['d'] || keyStatus['D'])
			moveX(&config.arena.player.movement,incrementX);
		if((keyStatus['n'] || keyStatus['N'])){
			config.nightMode = !config.nightMode;
			keyStatus['n'] = false;
			keyStatus['N'] = false;
		}
		if(keyStatus['1'])
			config.cam = 1;
		if(keyStatus['2'])
			config.cam = 2;
		if(keyStatus['3'])
			config.cam = 3;
		if(keyStatus['4'])
			config.cam = 4;
		if(keyStatus['5'])
			config.cam = 5;
		if((keyStatus['k'] || keyStatus['K']) && !config.killAll)
			config.killAll = true;
	}
	//KILL ALL OF THEM
	if(config.killAll){
		for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end();)
			it = config.arena.enemies.erase(it);
	}
	float incrementShot =-config.speed.shotSpeed;
	moveShot(incrementShot);
	if(chrono.hasStarted){
		enemyMovement(config.enemyConf.velCar);
		updateTime(glutGet(GLUT_ELAPSED_TIME));
	}

	enemyShots(glutGet(GLUT_ELAPSED_TIME));
	itCollidesShotPlayers();
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	Movement movement = config.arena.player.movement;
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			float sx = config.arena.player.circle.cx - config.arena.outsideCircle.cx
			+ sin(movement.tetaCarR)*(config.arena.player.car.body.height/2 - 4) +
			sin(movement.tetaCannonXR + movement.tetaCarR)*cos(movement.tetaCannonZR)*(config.arena.player.car.cannon.height + 4);

			float sy = config.arena.player.circle.cy - config.arena.outsideCircle.cy -
			cos(movement.tetaCarR)*(config.arena.player.car.body.height/2 - 4) -
			cos(movement.tetaCannonXR + movement.tetaCarR)*cos(movement.tetaCannonZR)*(config.arena.player.car.cannon.height + 4);

			float sz = -config.arena.player.car.body.depth/2 - config.arena.player.car.wheel.depth/4
			+ config.arena.player.car.cannon.depth/2.0 -
			sin(movement.tetaCannonZR)*(config.arena.player.car.cannon.height + 4);
			float tetaShotX = movement.tetaCannonXG + movement.tetaCarG;
			float tetaShotZ = movement.tetaCannonZG;
			float tetaCar = movement.tetaCarG;
			config.arena.player.shots.push_back(createShot(sx,sy,sz,tetaShotX,tetaShotZ,tetaCar));
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		config.arena.player.movement.rightButtonDown = true;
		config.arena.player.movement.camX = x;
		config.arena.player.movement.camY = y;
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		config.arena.player.movement.rightButtonDown = false;
	}
}

void mouseMovement(int x, int y){
	Movement movement = config.arena.player.movement;
	if(movement.rightButtonDown){
		//Movimento esquerda/direita
		float x1 = (x - movement.camX)/2;
		float teta = movement.tetaCamXG + x1;
		if(teta > 180)
			teta = 180;
		else if(teta < -180)
			teta = -180;
		config.arena.player.movement.tetaCamXG = teta;
		config.arena.player.movement.tetaCamXR = teta*M_PI/180.0;
		config.arena.player.movement.camX = x;
		//Movimento baixo/cima
		float y1 = (y - movement.camY)/2;
		teta = movement.tetaCamZG + y1;
		if(teta > 90)
			teta = 90;
		else if(teta < -90)
			teta = -90;
		config.arena.player.movement.tetaCamZG = teta;
		config.arena.player.movement.tetaCamZR = teta*M_PI/180.0;
		config.arena.player.movement.camY = y;
	}
}

void mousePassiveMovement (int x, int y){
	//Movimento esquerda/direita
	Movement movement = config.arena.player.movement;
	float x1 = (x - movement.mouseX)/2;
	float teta = movement.tetaCannonXG + x1;
	if(teta > 45)
		teta = 45;
	else if(teta < -45)
		teta = -45;
	config.arena.player.movement.tetaCannonXG = teta;
	config.arena.player.movement.tetaCannonXR = teta*M_PI/180.0;
	config.arena.player.movement.mouseX = x;
	//Movimento meio/cima
	float y1 = (y - movement.mouseY)/2;
	teta = movement.tetaCannonZG - y1;
	if(teta > 45)
		teta = 45;
	else if(teta < 0)
		teta = 0;
	config.arena.player.movement.tetaCannonZG = teta;
	config.arena.player.movement.tetaCannonZR = teta*M_PI/180.0;
	config.arena.player.movement.mouseY = y;
}
