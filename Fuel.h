#pragma once

#ifndef _Fuel
#define _Fuel

#include "ofMain.h" //Agregamos los métodos y las clases de oF

class Fuel {

public: //Vista y acceso público de estos métodos

	struct bidon {
		ofImage fuel;
		int type;
		float x;
		float y;
	};

	Fuel(); //Constructor

	bidon bidones[4];

	//Métodos
	void setup();
	void drawFuel();

	//Constantes para ancho y alto de la pantalla en fullscreen
	const float width = 1920;
	const float height = 1080;
};

#endif //!Fuel
