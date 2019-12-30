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

class Rect{
	public:
		float x;
		float y;
		float z;
		float width;
		float height;
		float depth;
		char *fill;
		Color color;
};

class Circle{
	public:
		float cx;
		float cy;
		float cz;
		int r;
		char *fill;
		Color color;
};

class Shot{
	public:
		float x;
		float y;
		float z;
		bool status;
		float tetaShotX;
		float tetaShotZ;
		float increment;
		//float tetaCar;
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

class Movement{
	public:
		//bool movementStatus;
		bool rightButtonDown;
	 	float tetaCannonXG;
		float tetaCannonXR;
		float tetaCannonZG;
		float tetaCannonZR;
		float increment;
		float tetaWheelsG;
		float tetaWheelsR;
		float tetaCarG;
		float tetaCarR;
		int mouseX;
		int mouseY;
		bool checkpoint;
		int direction;
		int camX;
		int camY;
		float tetaCamXG;
		float tetaCamXR;
		float tetaCamZG;
		float tetaCamZR;
};

class Player{
	public:
		Circle circle;
		Car car;
		std::vector<Shot> shots;
		Movement movement;
};

class Arena{
	public:
		char *path;
		Circle outsideCircle;
		Circle insideCircle;
		Rect line;
		std::vector<Player> enemies;
		Player player;
};

class Window{
	public:
		int width;
		int height;
		Color background;
		char* title;
};

class Enemy{
	public:
		float freqShot;
		float velCar;
		float velShot;
		float nShots;
};

class Configuration{
	public:
		int win;
		int cam;
		bool nightMode;
		bool killAll;
		Arena arena;
		Window window;
		Speed speed;
		Enemy enemyConf;
		char *filePath;
		int inicialize(void);
		Configuration(char*);
		Configuration();
		int readInsertionFile(void);
		Rect readLine(TiXmlElement*);
		Circle readCircle(TiXmlElement*);
};

class Chrono{
	public:
		float seconds;
		float init;
		bool hasStarted;
		float final;
};

Color createColor(float, float, float, float);
Rect createRect(float, float, int, int, char*, Color);
Rect createRect(float, float, float, Color);
Circle createCircle(int, Color);
Car createCar(Circle);
Shot createShot(float, float, float, float, float, float);

#endif
