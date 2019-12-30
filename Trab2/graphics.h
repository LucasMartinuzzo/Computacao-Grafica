#ifndef GRAPHICS_H
#define GRAPHICS_H

extern GLfloat gx, gy, movX, movY;
extern bool keyStatus [256];
extern Configuration config;
//extern Moviment moviment; //Não utilizado neste trabalho.

void drawCircle(Circle, float, float);

void drawRect(Rect, float, float);

bool isInsideSquare(double, double);

void display(void);

void init(void);

void keyPress(unsigned char, int, int);

void keyUp(unsigned char, int, int);

float euclidianDistancePointCircle (float, float, Circle);

bool itCollides(float, float, int);

void moveX(float);

void moveY(float);

void idle(void);

/* Não utilizados neste trabalho.
void mouse(int, int, int, int);
void mouseMoviment (int, int);
*/
#endif
