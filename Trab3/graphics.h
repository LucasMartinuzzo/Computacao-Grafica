#ifndef GRAPHICS_H
#define GRAPHICS_H

extern GLfloat gx, gy, movX, movY;
extern bool keyStatus [256];
extern Configuration config;
extern Movement movement;

void drawCircle(Circle, float, float);

void drawCircle(Circle);

void drawCircleDislocated(Circle, float, float);

void drawRect(Rect, float, float);

void drawRectCannon(Rect);

void drawRect(Rect);

void drawLine(Rect, int);

void drawShot(Player, Shot);

void drawCar(Player, Movement, float, float);

void display(void);

void init(void);

void keyPress(unsigned char, int, int);

void keyUp(unsigned char, int, int);

float euclidianDistancePointCircle (float, float, Circle);

float euclidianDistancePointOrigin(float, float);

bool itCollides(float, float, int);

void moveX(float);

void moveY(float);

void moveShot(float);

void idle(void);

void mouse(int, int, int, int);

void mouseMovement (int, int);

//bool isInsideSquare(float, float);

#endif
