#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "graphics.h"
#include "glutFunctions.h"
#include <math.h>
#include <vector>

void drawCircle(Circle circle, float cx, float cy){
	float x, y;
	float z = circle.cz;
	float dx = circle.cx - cx;
	float dy = circle.cy - cy;
	glColor3f(circle.color.red, circle.color.green, circle.color.blue);
	if(config.cam!=6){
		glColor3f(config.arena.outsideCircle.color.red, config.arena.outsideCircle.color.green, config.arena.outsideCircle.color.blue);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluQuadricOrientation(quadratic, GLU_INSIDE);
		gluDisk(quadratic,config.arena.insideCircle.r,config.arena.outsideCircle.r,50,50);
	}
	else {
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i<360;i++){
				x = circle.r*cos(M_PI*i/180.0) + dx;
				y = 	circle.r*sin(M_PI*i/180.0) + dy;
				glVertex3f(x,y,z);
			}
		glEnd();
		float r = config.arena.insideCircle.r;
		glColor3f(config.arena.insideCircle.color.red, config.arena.insideCircle.color.green, config.arena.insideCircle.color.blue);
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i<360;i++){
				x = r*cos(M_PI*i/180.0) + dx;
				y = r*sin(M_PI*i/180.0) + dy;
				glVertex3f(x,y,z);
			}
		glEnd();
	}
}

void printText(char *text, void *font, GLfloat x, GLfloat y){
	glMatrixMode (GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix();
	glLoadIdentity();
	glViewport(0, 0, 500, 500);
	gluOrtho2D(-250, 250, -250, 250);
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glRasterPos2f(x, y);
	char *tmpStr;
	tmpStr = text;
	while( *tmpStr ){
		glColor3d(0.0, 0.0, 0.0);
		glutBitmapCharacter(font, *tmpStr);
		tmpStr++;
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void drawCircle(Circle circle){
	float x, y;
	glColor4f(circle.color.red, circle.color.green, circle.color.blue,0.5);
	glutWireSphere(circle.r,30,30);
}

void drawCircleDislocated(Circle circle, float dx, float dy){
	float x, y;
	glColor3f(circle.color.red, circle.color.green, circle.color.blue);
	glBegin(GL_POLYGON);
		for(int i = 0; i<360;i++){
			x = circle.r*cos(M_PI*i/180.0) + dx ;
			y = (circle.r*sin(M_PI*i/180.0) + dy);
			glVertex3f(x,y,0);
		}
	glEnd();
}

void drawRect(Rect rect, float cx, float cy){
 	float dx = rect.x - cx;
	float dy = rect.y - cy;
	glColor3f(rect.color.red, rect.color.green, rect.color.blue);
	if (config.cam != 6){
		glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(dx, dy,0);
			glVertex3f(dx + rect.width, dy,0);
			glVertex3f(dx + rect.width, dy + rect.height,0);
			glVertex3f(dx, dy + rect.height,0);
		glEnd();
	}else{
		glBegin(GL_LINES);
		glVertex3f(dx, dy + rect.height/2, 0.0);
		glVertex3f(dx + rect.width, dy + rect.height/2, 0.0);
		glEnd();
	}
}

void drawRectCannon(Rect rect){
	glColor3f(rect.color.red, rect.color.green, rect.color.blue);
	glBegin(GL_QUADS);
		glVertex3f(-rect.width/2, 4, 0);
		glVertex3f(rect.width/2, 4, 0);
		glVertex3f(rect.width/2, -rect.height, 0);
		glVertex3f(-rect.width/2, -rect.height, 0);
	glEnd();
}

void drawRect(Rect rect){
	glColor3f(rect.color.red, rect.color.green, rect.color.blue);
	glutSolidCube(rect.depth);
}

void drawLine(Rect rect, int increment){
	float position;
	if(increment <= 0)
		position = (increment/3 % ((int) rect.height -1)) + (int) rect.height/2;
		else
			position = (increment/3 % ((int) rect.height -1)) - (int) rect.height/2;
	glLineWidth(1);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-rect.width/2, position, 0);
	glVertex3f(rect.width/2, position, 0);
	glEnd();
}

void drawShot(Player player, Shot shot){
	float z = -player.car.body.depth/2 - player.car.wheel.depth/4 + player.car.cannon.depth/2.0;
	glPushMatrix();
		glTranslatef(shot.x, shot.y,shot.z);
		glRotatef(shot.tetaShotX,0,0,1);
		glRotatef(shot.tetaShotZ,1,0,0);
		glTranslatef(0, shot.increment, 0);
		glColor3f(player.car.ammo.color.red, player.car.ammo.color.green, player.car.ammo.color.blue);
		glutSolidSphere(player.car.ammo.r, 50, 50);
	glPopMatrix();
}

void drawCylinderBase(Rect rect){
	glColor3f(0.9,0.9,0.9);
	float r = rect.depth/2;
	float x,y,z = 0;
	int i;
	glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, 0.0);
		for(int i = 359; i<405;i++){
			x = r*cos(M_PI*i/180.0);
			y = r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=44; i<90;i++){
			x = r*cos(M_PI*i/180.0);
			y = r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=89; i<135;i++){
			x = r*cos(M_PI*i/180.0);
			y = 	r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=134; i<180;i++){
			x = r*cos(M_PI*i/180.0);
			y = 	r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=179; i<225;i++){
			x = r*cos(M_PI*i/180.0);
			y = 	r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.1,0.1,0.1);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=224; i<270;i++){
			x = r*cos(M_PI*i/180.0);
			y = 	r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=269; i<315;i++){
			x = r*cos(M_PI*i/180.0);
			y = 	r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
	glColor3f(0.1,0.1,0.1);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glNormal3f(0.0, 0.0, -1.0);
		for(i=314; i<360;i++){
			x = r*cos(M_PI*i/180.0);
			y = 	r*sin(M_PI*i/180.0);
			glVertex3f(x,y,z);
		}
	glEnd();
}

void drawCylinder(Rect rect){
	glPushMatrix();
		glColor3f(rect.color.red, rect.color.green, rect.color.blue);
		glRotatef(-90, 0.0, 1.0, 0.0);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluCylinder(quadratic,rect.depth/2, rect.depth/2, rect.width/2, 50, 50);
	glPopMatrix();
}

void drawCylinderCannon(Rect rect){
	glPushMatrix();
		glColor3f(rect.color.red, rect.color.green, rect.color.blue);
		glRotatef(90, 1.0, 0.0, 0.0);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluCylinder(quadratic,rect.depth/2, rect.depth/2, rect.height + 4, 50, 50);
		glTranslatef(0, 0, 10);
		glColor3f(rect.color.red/2,rect.color.green/2,rect.color.blue/2);
		gluDisk(quadratic,0,rect.depth/2,50,50);
	glPopMatrix();
}

void switchCamera(int cam){
	Player player = config.arena.player;
	Movement movement = player.movement;
	int cx = player.circle.cx - config.arena.outsideCircle.cx;
	int cy = player.circle.cy - config.arena.outsideCircle.cy;
	int cz = -player.car.body.depth/2 - player.car.wheel.depth/4;
	float tetaCarR = player.movement.tetaCarR;
	float distance = 100;
	float farDistance = 1000;
	float altura = 2*player.car.body.depth + 50;
	float x, y, z;
	float lx, ly, lz;
	float sx = cx + sin(movement.tetaCarR)*(config.arena.player.car.body.height/2 - 4) +
	sin(movement.tetaCannonXR + movement.tetaCarR)*cos(movement.tetaCannonZR)*(config.arena.player.car.cannon.height + 4);

	float sy = cy -	cos(movement.tetaCarR)*(config.arena.player.car.body.height/2 - 4) -
	cos(movement.tetaCannonXR + movement.tetaCarR)*cos(movement.tetaCannonZR)*(config.arena.player.car.cannon.height + 4);

	float sz = cz -	sin(movement.tetaCannonZR)*(config.arena.player.car.cannon.height + 4);
	switch(cam){
	case 1:
		y = -player.car.body.height/6.0;
		z = -player.car.body.depth*0.8;
		gluLookAt(cx - sin(tetaCarR)*y,cy + cos(tetaCarR)*y, z, cx + sin(tetaCarR)*2*player.circle.r, cy - cos(tetaCarR)*2*player.circle.r,z,
		 		  0.0,0.0,-1.0);
		break;
	case 2:
		y = + player.car.body.height/2 - 6;
		z = cz;
		gluLookAt(cx + sin(tetaCarR)*y,cy - cos(tetaCarR)*y, cz -1,
			sx,sy,sz, 0.0,0.0,-1.0);
		break;
	case 3:
		gluLookAt(cx - distance*sin(tetaCarR + movement.tetaCamXR)*(cos(movement.tetaCamZR)+0.1),
		cy + distance*cos(tetaCarR + movement.tetaCamXR)*(cos(movement.tetaCamZR)+0.1),
		-altura*(sin(movement.tetaCamZR)+0.1),
		cx,cy,cz,
		0.0,0.0,-1.0);
		break;
	case 4:
		gluLookAt(0.0,0.0,cz-player.car.body.depth/3 , cx,cy,cz-player.car.body.depth/3 , 0.0,0.0,-1.0);
		break;
	case 5:
		gluLookAt(0.0,0.0,-850.0, 0.0,0.0,0.0, 0.0,-1.0,0.0);
	}
}

void drawScene(void){
	float materialSpecularity[] = {1.0, 1.0, 1.0, 1.0};
	int materialShineness =  64;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
	glMateriali(GL_FRONT, GL_SHININESS, materialShineness);
	float globalAmbientLight[] = {0.1, 0.1, 0.1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
	float ambientLight[] = {0.3, 0.3, 0.3, 1.0};
	float diffuseLight[] = {1.0, 1.0, 1.0, 1.0};
	float specularLight[] = {1.0, 1.0, 1.0, 1.0};
	float lightPosition[]= {0.0, 0.0, -4*config.arena.player.car.body.depth, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	if (config.nightMode)
		glDisable(GL_LIGHT0);
	else
		glEnable(GL_LIGHT0);

	Player player = config.arena.player;
	int cx = config.arena.outsideCircle.cx;
	int cy = config.arena.outsideCircle.cy;
	float tetaCarR = player.movement.tetaCarR;
	drawCircle(config.arena.outsideCircle, cx, cy);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -0.1);
		drawRect(config.arena.line,cx,cy);
	glPopMatrix();
	for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		drawCar((*it), cx, cy);
	}
	if(config.win == 1){
		drawCar(config.arena.player, cx, cy);
		char chronoString[15];
		snprintf(chronoString,14,"%.3f",chrono.final);
		glColor3f(0,0,0);
		printText(chronoString,font1,0.65*250, 0.9*250);
		char win[10];
		snprintf(win,10,"YOU WIN!");
		printText(win,font1,-0.15*250, 0);
	}
	else if(config.win == -1){
		char chronoString[15];
		snprintf(chronoString,14,"%.3f",chrono.final);
		glColor3f(0,0,0);
		printText(chronoString,font1,0.65*250, 0.9*250);
		char win[10];
		snprintf(win,10,"YOU LOST!");
		printText(win,font1, -0.15*250, 0);
	}
	else{
		drawCar(config.arena.player, cx, cy);
		char chronoString[15];
		snprintf(chronoString,14,"%.3f",chrono.seconds);
		glColor3f(0,0,0);
		printText(chronoString,font1,0.65*250, 0.9*250);

	}
}

void drawBody(Player player){
	float x = player.car.body.width;
	float y = player.car.body.height;
	float z = player.car.body.depth;
	glPushMatrix(); glPushAttrib(GL_LIGHTING_BIT);
		glMaterialf(GL_FRONT,  GL_SHININESS,  128);
		glColor3f(player.circle.color.red,player.circle.color.green,player.circle.color.blue);
		//Traseiro
		glBegin(GL_POLYGON);
			glNormal3f(0,1,0);
			glVertex3f(-x/2,y/2, -z/2);
			glVertex3f(x/2, y/2, -z/2);
			glVertex3f(x/2, y/2, z/2);
			glVertex3f(-x/2,y/2, z/2);
		glEnd();
		//Lado esquerdo
		glBegin(GL_POLYGON);
			glNormal3f(-1,0,0);
			glVertex3f(-x/2,-y/6,0);
			glVertex3f(-x/2,-y/2,0);
			glVertex3f(-x/2,-y/2,z/2);
			glVertex3f(-x/2, y/2,z/2);
			glVertex3f(-x/2, y/2,-z/2);
			glVertex3f(-x/2,-y/6,-z/2);
		glEnd();
		//Lado Direito
		glBegin(GL_POLYGON);
			glNormal3f(1,0,0);
			glVertex3f(x/2,-y/6,0);
			glVertex3f(x/2,-y/2,0);
			glVertex3f(x/2,-y/2,z/2);
			glVertex3f(x/2, y/2,z/2);
			glVertex3f(x/2, y/2,-z/2);
			glVertex3f(x/2,-y/6,-z/2);
		glEnd();
		//Cima recuado
		glBegin(GL_POLYGON);
			glNormal3f(0,0,-1);
			glVertex3f(-x/2,y/2,-z/2);
			glVertex3f(-x/2,-y/6,-z/2);
			glVertex3f(x/2,-y/6,-z/2);
			glVertex3f(x/2,y/2,-z/2);
		glEnd();
		//Cima não-recuado
		glBegin(GL_POLYGON);
			glNormal3f(0,0,-1);
			glVertex3f(-x/2,-y/6,0);
			glVertex3f(-x/2,-y/2,0);
			glVertex3f(x/2,-y/2,0);
			glVertex3f(x/2,-y/6,0);
		glEnd();
		//Inferior
		glBegin(GL_POLYGON);
			glNormal3f(0,0,1);
			glVertex3f(-x/2,y/2,z/2);
			glVertex3f(-x/2,-y/2,z/2);
			glVertex3f(x/2,-y/2,z/2);
			glVertex3f(x/2,y/2,z/2);
		glEnd();
		//Dianteira baixo
		glBegin(GL_POLYGON);
			glNormal3f(0,-1,0);
			glVertex3f(-x/2,-y/2,0);
			glVertex3f(-x/2,-y/2,z/2);
			glVertex3f(x/2,-y/2,z/2);
			glVertex3f(x/2,-y/2,0);
		glEnd();
		//Dianteira cima
		glBegin(GL_POLYGON);
			glNormal3f(0,-1,0);
			glVertex3f(-x/2,-y/6,-z/2);
			glVertex3f(-x/2,-y/6,0);
			glVertex3f(x/2,-y/6,0);
			glVertex3f(x/2,-y/6,-z/2);
		glEnd();

	glPopAttrib();glPopMatrix();

}

void drawCar(Player player, float cx, float cy){
	int i = 0;
	Movement movement = player.movement;
	for(std::vector<Shot>::iterator it = player.shots.begin(); it != player.shots.end(); it++, i++){
		drawShot(player,*it);
	}
	glPushMatrix();
		int x = player.circle.cx - cx; //NÃO PODE SER FLOAT (TERREMOTO)
		int y = player.circle.cy - cy;
		float z;
		float x1;
		float y1;
		float
		teta = 180*movement.increment/(M_PI*(player.car.wheel.depth/2));
		float comp;
		if(movement.tetaWheelsG <= 0){
			x1 = 0 - player.car.body.width/2 - player.car.wheel.width/2;
			y1 = 0 + player.car.body.height/2 - player.car.wheel.height/2;
		}
		else{
			x1 = 0 + player.car.body.width/2 + player.car.wheel.width/2;
			y1 = 0 + player.car.body.height/2 - player.car.wheel.height/2;
		}
		glTranslatef(x,y,-player.car.body.depth/2 - player.car.wheel.depth/4);
		glRotatef(movement.tetaCarG,0,0,1);
		//drawCircle(player.circle);

		//Canhão
		glPushMatrix();
			x = 0;
			y = 0 - player.car.body.height/2 + 4;
			z = player.car.cannon.depth/2.0;
			glTranslatef(x,y,z);
			glRotatef(movement.tetaCannonXG,0,0,1);
			glRotatef(movement.tetaCannonZG,1,0,0);
			drawCylinderCannon(player.car.cannon);
		glPopMatrix();
		//Dianteira esquerda
		glPushMatrix();
			x = 0 - player.car.body.width/2;
			y = 0 - player.car.body.height/2 + player.car.wheel.height/2 +2;
			glTranslatef(x,y, player.car.body.depth/2 - 1*player.car.wheel.depth/4);
			glRotatef(movement.tetaWheelsG,0,0,1);
			glRotatef(teta,1,0,0);
			drawCylinder(player.car.wheel);
			glPushAttrib(GL_LIGHTING_BIT);
			glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS,  128);
			//Roda de dentro
			glPushMatrix();
				glRotatef(-90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			//Roda de fora
			glPushMatrix();
				glTranslatef(-player.car.wheel.width/2,0,0);
				glRotatef(90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			glPopAttrib();
		glPopMatrix();
		//Dianteira direita
		glPushMatrix();
			x = 0 + player.car.body.width/2 + player.car.wheel.width/2;
			y = 0 - player.car.body.height/2 + player.car.wheel.height/2 +2;
			glTranslatef(x,y, player.car.body.depth/2 - 1*player.car.wheel.depth/4);
			glRotatef(movement.tetaWheelsG,0,0,1);
			glRotatef(teta,1,0,0);
			drawCylinder(player.car.wheel);
			glPushAttrib(GL_LIGHTING_BIT);
			glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS,  128);
			//Roda de fora
			glPushMatrix();
				glRotatef(-90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			//Roda de dentro
			glPushMatrix();
				glTranslatef(-player.car.wheel.width/2,0,0);
				glRotatef(90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			glPopAttrib();
		glPopMatrix();
		//Traseira esquerda
		glPushMatrix();
			x = 0 - player.car.body.width/2;
			y = 0 + player.car.body.height/2 - player.car.wheel.height/2 -2;
			glTranslatef(x,y, player.car.body.depth/2 - 1*player.car.wheel.depth/4);
			glRotatef(teta,1,0,0);
			drawCylinder(player.car.wheel);
			glPushAttrib(GL_LIGHTING_BIT);
			glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS,  128);
			//Roda de dentro
			glPushMatrix();
				glRotatef(-90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			//Roda de fora
			glPushMatrix();
				glTranslatef(-player.car.wheel.width/2,0,0);
				glRotatef(90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			glPopAttrib();
		glPopMatrix();
		//Traseira direita
		glPushMatrix();
			x = 0 + player.car.body.width/2 + player.car.wheel.width/2;
			y = 0 + player.car.body.height/2 - player.car.wheel.height/2 -2;
			glTranslatef(x,y, player.car.body.depth/2 - 1*player.car.wheel.depth/4);
			glRotatef(teta,1,0,0);
			drawCylinder(player.car.wheel);
			glPushAttrib(GL_LIGHTING_BIT);
			glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS,  128);
			//Roda de fora
			glPushMatrix();
				glRotatef(-90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			//Roda de dentro
			glPushMatrix();
				glTranslatef(-player.car.wheel.width/2,0,0);
				glRotatef(90, 0.0, 1.0, 0.0);
				drawCylinderBase(player.car.wheel);
			glPopMatrix();
			glPopAttrib();
		glPopMatrix();
		//Lataria
		drawBody(player);
	glPopMatrix();
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

void win(float cx, int cy){
	Player player = config.arena.player;
	Rect line = config.arena.line;
	float lineX = line.x;
	int lineY = line.y;
	float px = player.circle.cx;
	int py = player.circle.cy;
	if((px >= lineX) && (px <= lineX + line.width) && (py == lineY)){
		if(cy < py)
			config.arena.player.movement.checkpoint = true;
		if(cy> py)
			config.arena.player.movement.checkpoint = false;
	}
	if(config.arena.player.movement.checkpoint)
		if((px >= lineX) && (px <= lineX + line.width) && (py == lineY + (int) line.height)){
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
			win(cx,cy);
			if(!chrono.hasStarted){
				chrono.init = glutGet(GLUT_ELAPSED_TIME);
				chrono.hasStarted = true;
			}
		}
		(*movement).increment+=increment;
		(*player).circle.cx = cx;
		(*player).circle.cy = cy;
		(*movement).tetaCarG = teta;
		(*movement).tetaCarR = tetaR;
		return true;
	}
	return false;
}

bool itCollidesShotArena(std::vector<Shot>::iterator it, float increment, int dist){
	float teta = M_PI*((*it).tetaShotX)/180;
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
			float sx = (*it).circle.cx - config.arena.outsideCircle.cx + sin(movement.tetaCarR)*(*it).car.body.height/2 +  sin(movement.tetaCannonXR + movement.tetaCarR)* (*it).car.cannon.height/2;
			float sy = (*it).circle.cy - config.arena.outsideCircle.cy -
			cos(movement.tetaCarR)*(*it).car.body.height/2 - cos(movement.tetaCannonXR + movement.tetaCarR)*(*it).car.cannon.height/2;
			float sz =  -(*it).car.body.depth/2 - (*it).car.wheel.depth/4 + (*it).car.cannon.depth/2.0;
			float tetaShotX = movement.tetaCannonXG + movement.tetaCarG;
			float tetaCar = movement.tetaCarG;
			(*it).shots.push_back(createShot(sx,sy,sz, tetaShotX,0,tetaCar));
		}
	}
	float increment = - config.enemyConf.velShot;
	for(std::vector<Player>::iterator it1 = config.arena.enemies.begin(); it1 != config.arena.enemies.end(); it1++){
		for(std::vector<Shot>::iterator it = (*it1).shots.begin(); it != (*it1).shots.end();){
			float teta = M_PI*((*it).tetaShotX)/180;
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
		float teta = M_PI*((*it).tetaShotX)/180;
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
			float teta = M_PI*((*it).tetaShotX)/180;
			float dx = sin(teta)*((*it).increment);
			float dy = cos(teta)*((*it).increment);
			float cx = (*it).x - dx;
			float cy = (*it).y + dy;
			float euclid = euclidianDistancePointCircle2(cx, cy, player.circle);
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
		float tetaX = M_PI*((*it).tetaShotX)/180;
		float tetaZ = M_PI*((*it).tetaShotZ)/180;
		float dx = sin(tetaX)*((*it).increment);
		float dy = cos(tetaX)*((*it).increment);
		float dz = sin(tetaZ)*((*it).increment);
		float cx = (*it).x - dx;
		float cy = (*it).y + dy;
		float cz = (*it).z - dz;
		for(std::vector<Player>::iterator it1 = config.arena.enemies.begin(); it1 != config.arena.enemies.end();){
			float euclid = euclidianDistancePointCircle2(cx, cy, (*it1).circle);
			if(euclid < ((*it1).circle.r + player.car.ammo.r) && cz < (*it1).car.body.depth/2){
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
