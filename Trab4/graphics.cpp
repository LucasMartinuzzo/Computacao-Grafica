#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "graphics.h"
#include <math.h>
#include <vector>

// gx = 0.0, gy = 0.0;
bool keyStatus [256];
Configuration config;
Chrono chrono;
void *font1 = GLUT_BITMAP_9_BY_15;
void *font2 = GLUT_BITMAP_TIMES_ROMAN_24;

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

void drawCar(Player player, float cx, float cy){
	int i = 0;
	Movement movement = player.movement;
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

void printText(char* text, void *font, GLfloat x, GLfloat y){
    //Create a string to be printed
    char *tmpStr;
    //Define the position to start printing
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = text;
    //Print each of the other Char at time
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }

}

void display(void){
	int cx = config.arena.outsideCircle.cx;
	int cy = config.arena.outsideCircle.cy;
	glClear (GL_COLOR_BUFFER_BIT);
	drawCircle(config.arena.outsideCircle, cx, cy);
	drawCircle(config.arena.insideCircle, cx, cy);
	drawRect(config.arena.line, cx, cy);
	for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		drawCar((*it), cx, cy);
	}
	if(config.win == 1){
		drawCar(config.arena.player, cy, cx);
		char chronoString[15];
		snprintf(chronoString,14,"%.3f",chrono.final);
		glColor3f(0,0,0);
		printText(chronoString,font1,275, -310);
		char win[10];
		snprintf(win,10,"YOU WIN!");
		printText(win,font1,-30, 0);
	}
	else if(config.win == -1){
		char chronoString[15];
		snprintf(chronoString,14,"%.3f",chrono.final);
		glColor3f(0,0,0);
		printText(chronoString,font1,275, -310);
		char win[10];
		snprintf(win,10,"YOU LOST!");
		printText(win,font1,-30, 0);
	}
	else{
		drawCar(config.arena.player, cy, cx);
		char chronoString[15];
		snprintf(chronoString,14,"%.3f",chrono.seconds);
		glColor3f(0,0,0);
		printText(chronoString,font1,275, -310);

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

float euclidianDistancePointCircle2 (float cx, float cy, Circle circle){
	return sqrt(pow(cx - (circle.cx - config.arena.outsideCircle.cx),2) + pow(cy - (circle.cy - config.arena.outsideCircle.cy),2));
}

float euclidianDistancePointOrigin(float cx, float cy){
	return sqrt(pow(cx,2) + pow(cy,2));
}

bool itCollides(float cx,float cy, int r, bool isEnemy){
	Arena arena = config.arena;
	float increment = -config.speed.shotSpeed;
	if(euclidianDistancePointCircle(cx, cy, arena.outsideCircle) > arena.outsideCircle.r - r)
		return true;
	if(euclidianDistancePointCircle(cx, cy, arena.insideCircle) < r + arena.insideCircle.r)
		return true;
	if(isEnemy && euclidianDistancePointCircle(cx, cy, arena.player.circle) < r + arena.player.circle.r && config.win != -1)
		return true;
	for(std::vector<Player>::iterator it = arena.enemies.begin(); it != arena.enemies.end(); it++){
		float distance = euclidianDistancePointCircle(cx, cy, (*it).circle);
		//std::cout << distance << std::endl;
		if(distance < r + (*it).circle.r){
			if(!isEnemy)
				return true;
			else if(distance > config.enemyConf.velCar)
				return true;
		}
	}
	return false;
}

bool moveX(Movement *movement, float increment){
	float x1 = (*movement).tetaWheelsG + increment*1.5;
	if(x1 > 45){
		x1 = 45;
		return false;
	}
	else if(x1 < -45){
		x1 = -45;
		return false;
	}
	(*movement).tetaWheelsG = x1;
	(*movement).tetaWheelsR = x1*M_PI/180.0;
	return true;
}

void win(float cy){
	Player player = config.arena.player;
	int px = player.circle.cx - config.arena.outsideCircle.cx;
	int pyI = player.circle.cy - config.arena.outsideCircle.cy - player.car.body.height/2;
	int pyF = player.circle.cy - config.arena.outsideCircle.cy + player.car.body.height/2;
	int y = cy - config.arena.outsideCircle.cy;
	int yI = y - player.car.body.height/2;
	int yF = y + player.car.body.height/2;
	int line = config.arena.line.height/2;
	if(px > 0){
		if(pyI < -line && pyF < line){
			if(!(yI < -line && yF < line))
				config.arena.player.movement.checkpoint--;
		}
		else if(pyI >= -line && pyF >= line){
			if(!(yI >= -line && yF >= line))
			config.arena.player.movement.checkpoint++;
		}
	}
	if(config.arena.player.movement.checkpoint >= 1){
		if(config.win == 0)
			chrono.final = chrono.seconds;
		config.win = 1;
		for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end();)
			it = config.arena.enemies.erase(it);
	}
}

bool moveY(Player *player,Movement *movement, float increment, bool isEnemy){
	Circle playerC = (*player).circle;
	float teta;
	if(increment < 0)
		teta = (*movement).tetaCarG + (*movement).tetaWheelsG*0.05*0.5;
	else
		teta = (*movement).tetaCarG - (*movement).tetaWheelsG*0.05*0.5;
	float tetaR = teta*M_PI/180;
	float cx = playerC.cx - increment*sin(tetaR);
	float cy = playerC.cy + increment*cos(tetaR);
	if(!itCollides(playerC.cx, cy, playerC.r,isEnemy) && !itCollides(cx, playerC.cy, playerC.r,isEnemy)){
		if(!isEnemy){
			win(cy);
			if(!chrono.hasStarted){
				chrono.init = glutGet(GLUT_ELAPSED_TIME);
				chrono.hasStarted = true;
			}
		}
	//if(!itCollides(player.cx, cy, player.r))
		(*movement).increment+=increment;
		(*player).circle.cx = cx;
		(*player).circle.cy = cy;
		//movement.movementStatus = true;
		(*movement).tetaCarG = teta;
		(*movement).tetaCarR = tetaR;
		return true;
	}
	return false;
}

bool itCollidesShotArena(std::vector<Shot>::iterator it, float increment, int dist){
	float teta = M_PI*((*it).tetaCannon)/180;
	float dx = sin(teta)*((*it).increment + increment);
	float dy = cos(teta)*((*it).increment + increment);
	float d = euclidianDistancePointOrigin((*it).x - dx, (*it).y + dy);
	int R = config.arena.outsideCircle.r;
	int r = config.arena.insideCircle.r;
	if( d > dist){
		return true;
	}
	return false;
}

void enemyShots(float chrono){
	int nShot = (int) config.enemyConf.nShots;
	config.enemyConf.nShots = config.enemyConf.freqShot*chrono;
	int newNShot = (int) config.enemyConf.nShots;
	if(nShot != newNShot){
		for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
			Movement movement = (*it).movement;
			float sx = (*it).circle.cx - config.arena.outsideCircle.cx + sin(movement.tetaCarR)*config.arena.player.car.body.height/2 +  sin(movement.tetaCannonR + movement.tetaCarR)* (*it).car.cannon.height/2;
			float sy = (*it).circle.cy - config.arena.outsideCircle.cy -
			cos(movement.tetaCarR)*(*it).car.body.height/2 - cos(movement.tetaCannonR + movement.tetaCarR)*(*it).car.cannon.height/2;
			float tetaCannon = movement.tetaCannonG + movement.tetaCarG;
			float tetaCar = movement.tetaCarG;
			(*it).shots.push_back(createShot(sx,sy,tetaCannon,tetaCar));
		}
	}
	float increment = - config.enemyConf.velShot;
	for(std::vector<Player>::iterator it1 = config.arena.enemies.begin(); it1 != config.arena.enemies.end(); it1++){
		for(std::vector<Shot>::iterator it = (*it1).shots.begin(); it != (*it1).shots.end();){
			float teta = M_PI*((*it).tetaCannon)/180;
			float dx = sin(teta)*((*it).increment + increment);
			float dy = cos(teta)*((*it).increment + increment);
			float d = euclidianDistancePointOrigin((*it).x - dx, (*it).y + dy);
			int R = config.arena.outsideCircle.r;
			int r = config.arena.insideCircle.r;
			if(itCollidesShotArena(it,increment, R) || !itCollidesShotArena(it,increment,r)){
				it = (*it1).shots.erase(it);
			}else{
				(*it).increment += increment;
				it++;
			}
		}
	}
}

void moveShot(float increment){
	for(std::vector<Shot>::iterator it = config.arena.player.shots.begin(); it != config.arena.player.shots.end();){
		float teta = M_PI*((*it).tetaCannon)/180;
		float dx = sin(teta)*((*it).increment + increment);
		float dy = cos(teta)*((*it).increment + increment);
		float d = euclidianDistancePointOrigin((*it).x - dx, (*it).y + dy);
		int R = config.arena.outsideCircle.r;
		int r = config.arena.insideCircle.r;
		if(itCollidesShotArena(it,increment, R) || !itCollidesShotArena(it,increment,r)){
			it = config.arena.player.shots.erase(it);
		}else{
			(*it).increment += increment;
			it++;
		}
	}
}

void updateTime(int increment){
	float incrementSeconds = (increment -chrono.init)/1000;
	float old = chrono.seconds;
	chrono.seconds = incrementSeconds;
}

void itCollidesShotPlayers(void){
	Player player = config.arena.player;
	for(std::vector<Player>::iterator it1 = config.arena.enemies.begin(); it1 != config.arena.enemies.end(); it1++){
		for(std::vector<Shot>::iterator it = (*it1).shots.begin(); it != (*it1).shots.end();){
			float teta = M_PI*((*it).tetaCannon)/180;
			float dx = sin(teta)*((*it).increment);
			float dy = cos(teta)*((*it).increment);
			float cx = (*it).x - dx;
			float cy = (*it).y + dy;
			float euclid = euclidianDistancePointCircle2(cx, cy, player.circle);
			//printf("%f %f %f %f %f %d\n",cx, cy,player.circle.cx - config.arena.outsideCircle.cx, player.circle.cy - config.arena.outsideCircle.cy, euclid,  player.circle.r + (*it1).car.ammo.r);
			if(euclid < player.circle.r + (*it1).car.ammo.r){
				if(config.win == 0)
					chrono.final = chrono.seconds;
				config.win = -1;
				it = (*it1).shots.erase(it);
			}
			else
				it++;
		}
	}
	for(std::vector<Shot>::iterator it = config.arena.player.shots.begin(); it != config.arena.player.shots.end();){
		bool collide = false;
		float teta = M_PI*((*it).tetaCannon)/180;
		float dx = sin(teta)*((*it).increment);
		float dy = cos(teta)*((*it).increment);
		float cx = (*it).x - dx;
		float cy = (*it).y + dy;
		for(std::vector<Player>::iterator it1 = config.arena.enemies.begin(); it1 != config.arena.enemies.end();){
			float euclid = euclidianDistancePointCircle2(cx, cy, (*it1).circle);
			if(euclid < (*it1).circle.r + player.car.ammo.r){
				it1 = config.arena.enemies.erase(it1);
				collide = true;
				it = config.arena.player.shots.erase(it);
				break;
			}
			else
				it1++;
		}
		if(!collide)
			it++;
	}
}

void enemyMovement(float increment){
	int i;
	for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		i = rand()%2;
		switch(i){
			case 0:
			if(!moveX(&((*it).movement), -increment))
				moveX(&((*it).movement), increment);
			break;
			case 1:
			if(!moveX(&((*it).movement), increment))
				moveX(&((*it).movement), -increment);
			break;
		}
		if(((int) glutGet(GLUT_ELAPSED_TIME)) % 1000 == 0){
			(*it).movement.direction = rand()%2;
		}
		switch((*it).movement.direction){
			case 1:
			if(!moveY(&(*it), &((*it).movement), increment, true)){
				moveY(&(*it), &((*it).movement), -increment, true);
				(*it).movement.direction = 0;
			}
			break;
			case 0:
			if(!moveY(&(*it), &((*it).movement), -increment, true)){
				moveY(&(*it), &((*it).movement), increment, true);
				(*it).movement.direction = 1;
			}
			break;
		}
	}
}

void idle(void){
	float increment = config.speed.carSpeed;
	float incrementX = 2;
	//movement.movementStatus = false;
	if(config.win!= -1){
		if(keyStatus['s'] || keyStatus['S']){
			moveY(&config.arena.player, &config.arena.player.movement, increment, false);
		}
		if(keyStatus['w'] || keyStatus['W'])
			moveY(&config.arena.player, &config.arena.player.movement,-increment, false);
		if(keyStatus['a'] || keyStatus['A'])
			moveX(&config.arena.player.movement,-incrementX);
		if(keyStatus['d'] || keyStatus['D'])
			moveX(&config.arena.player.movement,incrementX);
	}
	//printf("%f\n",config.speed.shotSpeed);
	moveShot(-config.speed.shotSpeed);
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
	Movement movement = config.arena.player.movement;
	float x1 = (x - movement.mouse)/2;
	float teta = movement.tetaCannonG + x1;
	if(teta > 45)
		teta = 45;
	else if(teta < -45)
		teta = -45;
	config.arena.player.movement.tetaCannonG = teta;
	config.arena.player.movement.tetaCannonR = teta*M_PI/180.0;
	config.arena.player.movement.mouse = x;
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
