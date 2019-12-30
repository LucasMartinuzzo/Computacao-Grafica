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
	TiXmlElement* windowXml = aplication->FirstChildElement();

	TiXmlElement* largura = windowXml->FirstChildElement();
	window.width = atoi(((largura->FirstChild())->ToText())->Value());

	TiXmlElement* altura = largura->NextSiblingElement();
	window.height = atoi(((altura->FirstChild())->ToText())->Value());

	TiXmlElement* fundo = altura->NextSiblingElement();
	window.background.red = atof(fundo->Attribute("corR"));
	window.background.green = atof(fundo->Attribute("corG"));
	window.background.blue = atof(fundo->Attribute("corB"));

	TiXmlElement* title = fundo->NextSiblingElement();
	window.title =  strdup(((title->FirstChild())->ToText())->Value());
	
	TiXmlElement* quadradoXml = windowXml->NextSiblingElement();
	square.size = atoi(quadradoXml->Attribute("tamanho"));
	square.color.red = atof(quadradoXml->Attribute("corR"));
	square.color.green = atof(quadradoXml->Attribute("corG"));
	square.color.blue = atof(quadradoXml->Attribute("corB"));
	
	
	square.resized = ((double) square.size)/window.height;
	doc.Clear();
	return 0;
}
Configuration::Configuration(char *filePath){
	Configuration::filePath = filePath;
	inicialize();
}
Configuration::Configuration(){
}

Square Configuration::getSquare(){
	return square;
}

Window Configuration::getWindow(){
	return window;
}
char* Window::getTitle(){
	return title;
}
