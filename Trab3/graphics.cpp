#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"
#include <math.h>
#include <vector>

GLfloat gx = 0.0, gy = 0.0;
bool keyStatus [256];
Configuration config;
Movement movement;

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

void drawCircle(Circle circle){
	float x, y;
	glColor3f(circle.color.red, circle.color.green, circle.color.blue);
	glBegin(GL_POLYGON);
		for(int i = 0; i<360;i++){
			x = circle.r*cos(M_PI*i/180.0) ;
			y = (circle.r*sin(M_PI*i/180.0));
			glVertex2f(x,y);
		}
	glEnd();
}

void drawCircleDislocated(Circle circle, float dx, float dy){
	float x, y;
	glColor3f(circle.color.red, circle.color.green, circle.color.blue);
	glBegin(GL_POLYGON);
		for(int i = 0; i<360;i++){
			x = circle.r*cos(M_PI*i/180.0) + dx ;
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

void drawRectCannon(Rect rect){
	glColor3f(rect.color.red, rect.color.green, rect.color.blue);
	glBegin(GL_QUADS);
		glVertex2f(-rect.width/2, 4);
		glVertex2f(rect.width/2, 4);
		glVertex2f(rect.width/2, -rect.height);
		glVertex2f(-rect.width/2, -rect.height);
	glEnd();
}

void drawRect(Rect rect){
	glColor3f(rect.color.red, rect.color.green, rect.color.blue);
	glBegin(GL_QUADS);
		glVertex2f(-rect.width/2, -rect.height/2);
		glVertex2f(rect.width/2, -rect.height/2);
		glVertex2f(rect.width/2, rect.height/2);
		glVertex2f(-rect.width/2, rect.height/2);
	glEnd();
}

void drawLine(Rect rect, int increment){
	float position;
	if(increment <= 0)
		position = (increment/3 % (rect.height -1)) + rect.height/2;
		else
			position = (increment/3 % (rect.height -1)) - rect.height/2;
	glLineWidth(1);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-rect.width/2, position);
	glVertex2f(rect.width/2, position);
	glEnd();
}

void drawShot(Player player, Shot shot){
	glPushMatrix();
	glTranslatef(shot.x,shot.y,0.0);
	glRotatef(shot.tetaCannon,0,0,1);
	drawCircleDislocated(player.car.ammo,0,shot.increment);
	glPopMatrix();
}

void drawCar(Player player, Movement movement, float cx, float cy){
	int i = 0;
	for(std::vector<Shot>::iterator it = player.shots.begin(); it != player.shots.end(); it++, i++){
		drawShot(player,*it);
	}
	glPushMatrix();
		int x = player.circle.cx - cx;
		int y = player.circle.cy - cy;
		int x1;
		int y1;
		if(movement.tetaWheelsG <= 0){
			x1 = 0 - player.car.body.width/2 - player.car.wheel.width/2;
			y1 = 0 + player.car.body.height/2 - player.car.wheel.height/2;
		}
		else{
			x1 = 0 + player.car.body.width/2 + player.car.wheel.width/2;
			y1 = 0 + player.car.body.height/2 - player.car.wheel.height/2;
		}
		glTranslatef(x,y,0.0);
		glRotatef(movement.tetaCarG,0,0,1);
		//drawCircle(player.circle);

		//Canhão
		glPushMatrix();
			x = 0;
			y = 0 - player.car.body.height/2;
			glTranslatef(x,y,0.0);
			glRotatef(movement.tetaCannonG,0,0,1);
			drawRectCannon(player.car.cannon);
		glPopMatrix();
		//Dianteira esquerda
		glPushMatrix();
			x = 0 - player.car.body.width/2 - player.car.wheel.width/2;
			y = 0 - player.car.body.height/2 + player.car.wheel.height/2;
			glTranslatef(x,y,0.0);
			glRotatef(movement.tetaWheelsG,0,0,1);
			drawRect(player.car.wheel);
			drawLine(player.car.wheel, movement.increment);
		glPopMatrix();
		//Dianteira direita
		glPushMatrix();
			x = 0 + player.car.body.width/2 + player.car.wheel.width/2;
			y = 0 - player.car.body.height/2 + player.car.wheel.height/2;
			glTranslatef(x,y,0.0);
			glRotatef(movement.tetaWheelsG,0,0,1);
			drawRect(player.car.wheel);
			drawLine(player.car.wheel, movement.increment);
		glPopMatrix();
		//Traseira esquerda
		glPushMatrix();
			x = 0 - player.car.body.width/2 - player.car.wheel.width/2;
			y = 0 + player.car.body.height/2 - player.car.wheel.height/2;
			glTranslatef(x,y,0.0);
			drawRect(player.car.wheel);
			drawLine(player.car.wheel, movement.increment);
		glPopMatrix();
		//Traseira dreita
		glPushMatrix();
			x = 0 + player.car.body.width/2 + player.car.wheel.width/2;
			y = 0 + player.car.body.height/2 - player.car.wheel.height/2;
			glTranslatef(x,y,0.0);
			drawRect(player.car.wheel);
			drawLine(player.car.wheel, movement.increment);
		glPopMatrix();
		//Lataria
		drawRect(player.car.body);
	glPopMatrix();
}

void display(void){
	int cx = config.arena.outsideCircle.cx;
	int cy = config.arena.outsideCircle.cy;
	glClear (GL_COLOR_BUFFER_BIT);
	drawCircle(config.arena.outsideCircle, cx, cy);
	drawCircle(config.arena.insideCircle, cx, cy);
	drawRect(config.arena.line, cx, cy);
	for(std::vector<Circle>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		drawCircle(*it, cx, cy);
	}
	drawCar(config.arena.player, movement, cy, cx);
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

float euclidianDistancePointOrigin(float cx, float cy){
	return sqrt(pow(cx,2) + pow(cy,2));
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
	float x1 = movement.tetaWheelsG + increment*1.5;
	if(x1 > 45)
		x1 = 45;
	else if(x1 < -45)
		x1 = -45;
	if(1){
		movement.tetaWheelsG = x1;
		movement.tetaWheelsR = x1*M_PI/180.0;
	}
	return;
}

void moveY(float increment){
	Circle player = config.arena.player.circle;
	float teta;
	if(increment < 0)
		teta = movement.tetaCarG + movement.tetaWheelsG*0.05*0.5;
	else
		teta = movement.tetaCarG - movement.tetaWheelsG*0.05*0.5;
	float tetaR = teta*M_PI/180;
	float cx = player.cx - increment*sin(tetaR);
	float cy = player.cy + increment*cos(tetaR);
	if(!itCollides(player.cx, cy, player.r) && !itCollides(cx, player.cy, player.r)){
	//if(!itCollides(player.cx, cy, player.r)){
		movement.increment+=increment;
		config.arena.player.circle.cx = cx;
		config.arena.player.circle.cy = cy;
		//movement.movementStatus = true;
		movement.tetaCarG = teta;
		movement.tetaCarR = tetaR;
	}
	return;
}

void moveShot(float increment){
	for(std::vector<Shot>::iterator it = config.arena.player.shots.begin(); it != config.arena.player.shots.end();){
		float teta = M_PI*((*it).tetaCannon)/180;
		float dx = sin(teta)*((*it).increment + increment);
		float dy = cos(teta)*((*it).increment + increment);
		float d = euclidianDistancePointOrigin((*it).x - dx, (*it).y + dy);
		int r = config.arena.outsideCircle.r;
		if( d > r + config.arena.player.car.ammo.r){
			it = config.arena.player.shots.erase(it);
		}else{
			(*it).increment += increment;
			it++;
		}
	}
}

void idle(void){
	float increment = config.speed.carSpeed;
	float incrementX = 2;
	//movement.movementStatus = false;
	if(keyStatus['s'] || keyStatus['S']){
		moveY(increment);
	}
	if(keyStatus['w'] || keyStatus['W'])
		moveY(-increment);
	if(keyStatus['a'] || keyStatus['A'])
		moveX(-incrementX);
	if(keyStatus['d'] || keyStatus['D'])
		moveX(incrementX);
	if(keyStatus[' ']){
		gx = 0;
		gy = 0;
	}
	//printf("%f\n",config.speed.shotSpeed);
	moveShot(-config.speed.shotSpeed);
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			float sx = config.arena.player.circle.cx - config.arena.outsideCircle.cx + sin(movement.tetaCarR)*config.arena.player.car.body.height/2 +  sin(movement.tetaCannonR + movement.tetaCarR)* config.arena.player.car.cannon.height/2;
			float sy = config.arena.player.circle.cy - config.arena.outsideCircle.cy -
			cos(movement.tetaCarR)*config.arena.player.car.body.height/2 - cos(movement.tetaCannonR + movement.tetaCarR)*config.arena.player.car.cannon.height/2;
			float tetaCannon = movement.tetaCannonG + movement.tetaCarG;
			float tetaCar = movement.tetaCarG;
			config.arena.player.shots.push_back(createShot(sx,sy,tetaCannon,tetaCar));
		}
	}
}

void mouseMovement (int x, int y){
	float x1 = (x - movement.mouse)/2;
	float teta = movement.tetaCannonG + x1;
	if(teta > 45)
		teta = 45;
	else if(teta < -45)
		teta = -45;
	movement.tetaCannonG = teta;
	movement.tetaCannonR = teta*M_PI/180.0;
	movement.mouse = x;
}



/* Não utilizado neste trabalho
bool isInsideSquare(float x, float y){
	double dl = config.square.resized;
	if(x >=gx && x <= gx + dl && y >= gy && y <= gy + dl)
		return true;
	return false;
}

void moveX(float increment){
	Circle player = config.arena.player.circle;
	float cx = player.cx + increment;
	if(!itCollides(cx, player.cy, player.r))
		config.arena.player.circle.cx = cx;
	return;
}
*/
