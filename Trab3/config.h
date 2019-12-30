#ifndef CONFIG_H
#define CONFIG_H
#include "tinyxml.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

class Color{
	public:
		float red;
		float green;
		float blue;
};

class Square{
	public:
		int size;
		float resized;
		Color color;
};

class Rect{
	public:
		float x;
		float y;
		int width;
		int height;
		char *fill;
		Color color;
};

class Circle{
	public:
		float cx;
		float cy;
		int r;
		char *fill;
		Color color;
};

class Shot{
	public:
		float x;
		float y;
		bool status;
		float tetaCannon;
		float increment;
		float tetaCar;
};

class Car{
	public:
		Rect wheel;
		Rect body;
		Rect cannon;
		Circle ammo;
};

class Speed{
	public:
		float shotSpeed;
		float carSpeed;
};

class Player{
	public:
		Circle circle;
		Car car;
		std::vector<Shot> shots;
};

class Arena{
	public:
		char *path;
		Circle outsideCircle;
		Circle insideCircle;
		Rect line;
		std::vector<Circle> enemies;
		Player player;
};

class Window{
	public:
		int width;
		int height;
		Color background;
		char* title;
};

class Configuration{
	public:
		Arena arena;
		Window window;
		Speed speed;
		char *filePath;
		int inicialize(void);
		Configuration(char*);
		Configuration();
		int readInsertionFile(void);
		Rect readLine(TiXmlElement*);
		Circle readCircle(TiXmlElement*);
};

class Movement{
	public:
		//bool movementStatus;
		//bool leftButtonDown;
	 	float tetaCannonG;
		float tetaCannonR;
		float increment;
		float tetaWheelsG;
		float tetaWheelsR;
		float tetaCarG;
		float tetaCarR;
		int mouse;
};

Color createColor(float, float, float, float);
Rect createRect(float, float, int, int, char*, Color);
Rect createRect(int, int, Color);
Circle createCircle(int, Color);
Car createCar(Circle);
Shot createShot(float, float, float, float);

#endif
