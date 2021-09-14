#pragma once

#ifndef _People
#define _People

#include "ofMain.h" //Agregamos los métodos y las clases de oF

class People {

public: //Vista y acceso público de estos métodos

	struct human {
		ofImage humano;
		float x;
		float y;
		float speed;
	};

	//Atributos
	human humanos[6];

	People(); //Constructor

	//Métodos
	void setup();
	void update();
	void drawPeople();

	//Constantes para ancho y alto de la pantalla en fullscreen
	const float width = 1920;
	const float height = 1080;
};

#endif //!People


