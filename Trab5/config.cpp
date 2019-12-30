#include "tinyxml.h"
#include <stdlib.h>
#include <iostream>
#include "config.h"
#include <string.h>
using namespace std;

int Configuration::inicialize(void){
	TiXmlDocument doc;
	strcat(filePath,"config.xml");
	if(!doc.LoadFile(filePath)){
		cerr << doc.ErrorDesc() << endl;
		return -1;
	}
	TiXmlElement* aplication = doc.FirstChildElement();
	if(aplication == NULL){
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
		return -1;
	}
	char* nome;
	char* tipo;
	char *caminho;
	TiXmlElement* arquivoArena = aplication->FirstChildElement();
	nome = strdup(arquivoArena->Attribute("nome"));
	tipo = strdup(arquivoArena->Attribute("tipo"));
	caminho = strdup(arquivoArena->Attribute("caminho"));
	arena.path = caminho;
	strcat(arena.path,nome);
	strcat(arena.path,".");
	strcat(arena.path,tipo);
	TiXmlElement* carro = arquivoArena->NextSiblingElement();
	speed.carSpeed = atof(carro->Attribute("velCarro"));
	speed.shotSpeed = atof(carro->Attribute("velTiro"));
	TiXmlElement *enemy = carro->NextSiblingElement();
	enemyConf.freqShot = atof(enemy->Attribute("freqTiro"));
	enemyConf.velCar = atof(enemy->Attribute("velCarro"));
	enemyConf.velShot = atof(enemy->Attribute("velTiro"));
	doc.Clear();
	return 0;
}

int Configuration::readInsertionFile(void){
	TiXmlDocument doc;
	if(!doc.LoadFile(arena.path)){
		cerr << doc.ErrorDesc() << endl;
		return -1;
	}
	TiXmlElement* aplication = doc.FirstChildElement();
	if(aplication == NULL){
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
		return -1;
	}
	for(TiXmlElement* element = aplication->FirstChildElement();element != NULL; element = element->NextSiblingElement()){
		if(strcmp(element->Attribute("fill"),"black") == 0){
			arena.line = readLine(element);
		}
		else{
			Circle circle = readCircle(element);
			if(strcmp(circle.fill,"blue") == 0){
				arena.outsideCircle = circle;
				arena.outsideCircle.cz = 1;
				arena.outsideCircle.color.blue = 1;
			}else if(strcmp(circle.fill,"white") == 0){
				arena.insideCircle = circle;
				arena.insideCircle.cz = 0;
				arena.insideCircle.color.red = 1;
				arena.insideCircle.color.green = 1;
				arena.insideCircle.color.blue = 1;
			}else if(strcmp(circle.fill,"green") == 0){
				arena.player.circle = circle;
				arena.player.circle.color.green = 1;
			}else if(strcmp(circle.fill,"red") == 0){
				Player player;
				circle.color.red = 1;
				player.circle = circle;
				arena.enemies.push_back(player);
			}
		}
	}
	doc.Clear();
	return 0;
}

Color createColor (float red, float green, float blue, float range){
	Color color;
	color.red = red/range;
	color.green = green/range;
	color.blue = blue/range;
	return color;
}

Rect Configuration::readLine(TiXmlElement* element){
	float x = atof(element->Attribute("x"));
	float y = atof(element->Attribute("y"));
	int width = atoi(element->Attribute("width"));
	int height = atoi(element->Attribute("height"));
	char *fill = strdup(element->Attribute("fill"));
	Color color = createColor(0.0, 0.0, 0.0, 1.0);
	Rect line = createRect(x,y,width,height,fill,color);
	return line;
}

Circle Configuration::readCircle(TiXmlElement* element){
	Circle circle;
	circle.cx = atof(element->Attribute("cx"));
	circle.cy = atof(element->Attribute("cy"));
	circle.cz = 0;
	circle.r = atoi(element->Attribute("r"));
	circle.fill = strdup(element->Attribute("fill"));
	circle.color = createColor(0.0, 0.0, 0.0, 1.0);
	return circle;
}

Rect createRect(float width, float height, float depth, Color color){
	Rect rect;
	rect.width = width;
	rect.height = height;
	rect.depth = depth;
	rect.color = color;
	return rect;
}

Rect createRect(float x, float y, int width, int height, char* fill, Color color){
	Rect rect;
	rect.x = x;
	rect.y = y;
	rect.z = 0;
	rect.width = width;
	rect.height = height;
	//rect.fill = fill;
	rect.color = color;
	return rect;
}

Circle createCircle(int r, Color color){
	Circle circle;
	circle.r = r;
	circle.color = color;
	return circle;
}

Car createCar(Circle circle){
	Car car;
	int bodyH = 2*circle.r*0.7;
	float bodyW = 2*circle.r*0.55;
	float bodyD = 2*circle.r*0.4;
	Color bodyC = circle.color;
	car.body = createRect(bodyW, bodyH, bodyD, bodyC);
	float wheelH = bodyH*0.3;
	float wheelW = bodyW*0.3;
	float wheelD = bodyD*0.5;
	Color wheelC = createColor(0.1,0.1,0.1,1);
	car.wheel = createRect(wheelW, wheelH, wheelD, wheelC);
	float cannonH = bodyH*0.3;
	float cannonW = bodyW*0.2;
	float cannonD = bodyW*0.2;
	Color cannonC = createColor(circle.color.red/2,circle.color.green/2,circle.color.blue/2,1);
	car.cannon = createRect(cannonW, cannonH, cannonD, cannonC);
	//car.leftBotWheel = createRect()
	float ammoR = cannonW*0.475;
	Color ammoC = createColor(0.3, 0.3, 0.3, 1);
	car.ammo = createCircle(ammoR, ammoC);
	return car;
}

Shot createShot(float x, float y, float z, float tetaShotX, float tetaShotZ, float tetaCar){
	Shot shot;
	shot.x = x;
	shot.y = y;
	shot.z = z;
	shot.increment = 0;
	shot.status = true;
	shot.tetaShotX = tetaShotX;
	shot.tetaShotZ = tetaShotZ;
	//shot.tetaCar = tetaCar;
	return shot;
}

Configuration::Configuration(char *filePath){
	Configuration::filePath = filePath;
	inicialize();
	readInsertionFile();
	Color background = createColor(1,1,1,1);
	Window window;
	window.width = 2*arena.outsideCircle.r;
	window.height = 2*arena.outsideCircle.r;
	window.background = background;
	Configuration::window = window;
	Car car = createCar(arena.player.circle);
	arena.player.car = car;
	for(std::vector<Player>::iterator it = arena.enemies.begin(); it != arena.enemies.end(); it++){
		Car enemyCar = createCar((*it).circle);
		(*it).car = enemyCar;
	}

	//Configuration::window = Window(outsideCircle.r, outsideCircle.r,Color(1,1,1),"Trabalho 2");
}

Configuration::Configuration(){
}
