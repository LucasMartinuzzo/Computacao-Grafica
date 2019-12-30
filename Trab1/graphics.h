#ifndef GRAPHICS_H
#define GRAPHICS_H

extern GLfloat gx, gy;
extern bool keyStatus [256];
extern Configuration config;
extern Moviment moviment;

bool isInsideSquare(double, double);

void display(void);

void init(void);

void keyPress(unsigned char, int, int);

void keyUp(unsigned char, int, int);

void idle(void);
void mouse(int, int, int, int);

void mouseMoviment (int, int);

#endif
