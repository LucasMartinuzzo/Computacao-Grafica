#ifndef CONFIG_H
#define CONFIG_H
#include "tinyxml.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

class Color{
	public:
		double red;
		double green;
		double blue;
};

class Square{
	public:
		int size;
		double resized;
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

class Arena{
	public:
		char *path;
		Circle outsideCircle;
		Circle insideCircle;
		Rect line;
		std::vector<Circle> enemies;
		Circle player;
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
		Square square;
		char *filePath;
		int inicialize(void);
		Configuration(char*);
		Configuration();
		int readInsertionFile(void);
		Rect readLine(TiXmlElement*);
		Circle readCircle(TiXmlElement*);
};
/* Não utilizado neste trabalho.
class Moviment{
	public:
		bool squareStatus;
		bool leftButtonDown;
		float dx;
		float dy;
};
*/
#endif
