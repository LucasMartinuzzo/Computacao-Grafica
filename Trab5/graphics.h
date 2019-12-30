#ifndef GRAPHICS_H
#define GRAPHICS_H

void drawCircle(Circle, float, float);

void drawCircle(Circle);

void drawCircleDislocated(Circle, float, float);

void drawRect(Rect, float, float);

void drawRectCannon(Rect);

void drawRect(Rect);

void drawLine(Rect, int);

void printText(char *, void *, GLfloat, GLfloat);

void drawShot(Player, Shot);

void drawCylinderBase(Rect);

void drawCylinder(Rect);

void drawCylinderCannon(Rect);

void switchCamera(int);

void drawScene(void);

void drawBody(Player);

void drawCar(Player, float, float);

float euclidianDistancePointCircle (float, float, Circle);

float euclidianDistancePointCircle2 (float, float, Circle);

float euclidianDistancePointOrigin(float, float);

bool itCollides(float, float, int, bool);

void updateTime(int);

void itCollidesShotPlayers(void);

bool moveX(Movement*, float);

void win(float, int);

bool moveY(Player *, Movement*, float, bool);

bool itCollidesShotArena(std::vector<Shot>::iterator, float, int);

void enemyShots(float);

void moveShot(float);

void enemyMovement(float);

#endif
