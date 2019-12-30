#ifndef GLUTFUNCTIONS_H
#define GLUTFUNCTIONS_H

extern bool keyStatus [256];
extern Configuration config;
extern Chrono chrono;
extern void *font1;
extern void *font2;

void display(void);
void init(void);
void keyPress(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void idle(void);
void mouse(int, int, int, int);
void mouseMovement (int, int);
void mousePassiveMovement (int, int);

#endif
