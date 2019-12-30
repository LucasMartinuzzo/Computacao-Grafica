#ifndef CONFIG_H
#define CONFIG_H
#include "tinyxml.h"
#include <stdlib.h>
#include <iostream>

class Color{
	public:
		double red;
		double green;
		double blue;
};


class Window{
	public:
		int width;
		int height;
		Color background;
		char* title;
		char* getTitle();
};

class Square{
	public:
		int size;
		double resized;
		Color color;
};

class Configuration{
	Window window;
	Square square;
	char *filePath;
	public:
		int inicialize(void);
		Configuration(char*);
		Configuration();
		Window getWindow();
		Square getSquare();
};
class Moviment{
	public:
		bool squareStatus;
		bool leftButtonDown;
		float dx;
		float dy;
};
#endif
