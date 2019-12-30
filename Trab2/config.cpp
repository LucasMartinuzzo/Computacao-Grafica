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
				arena.outsideCircle.color.blue = 1;
			}else if(strcmp(circle.fill,"white") == 0){
				arena.insideCircle = circle;
				arena.insideCircle.color.red = 1;
				arena.insideCircle.color.green = 1;
				arena.insideCircle.color.blue = 1;
			}else if(strcmp(circle.fill,"green") == 0){
				arena.player = circle;
				arena.player.color.green = 1;
			}else if(strcmp(circle.fill,"red") == 0){
				circle.color.red = 1;
				arena.enemies.push_back(circle);
			}
		}
	}
	doc.Clear();
	return 0;
}

Rect Configuration::readLine(TiXmlElement* element){
	Rect line;
	line.x = atof(element->Attribute("x"));
	line.y = atof(element->Attribute("y"));
	line.width = atoi(element->Attribute("width"));
	line.height = atoi(element->Attribute("height"));
	line.fill = strdup(element->Attribute("fill"));
	line.color.red = 0;
	line.color.green = 0;
	line.color.blue = 0;
	return line;
}

Circle Configuration::readCircle(TiXmlElement* element){
	Circle circle;
	circle.cx = atof(element->Attribute("cx"));
	circle.cy = atof(element->Attribute("cy"));
	circle.r = atoi(element->Attribute("r"));
	circle.fill = strdup(element->Attribute("fill"));
	circle.color.red = 0;
	circle.color.green = 0;
	circle.color.blue = 0;
	return circle;
}

Configuration::Configuration(char *filePath){
	Configuration::filePath = filePath;
	inicialize();
	readInsertionFile();
	Color background;
	background.red = 1;
	background.green = 1;
	background.blue = 1;
	Window window;
	window.width = 2*arena.outsideCircle.r;
	window.height = 2*arena.outsideCircle.r;
	window.background = background;
	Configuration::window = window;
	//Configuration::window = Window(outsideCircle.r, outsideCircle.r,Color(1,1,1),"Trabalho 2");
}

Configuration::Configuration(){
}
