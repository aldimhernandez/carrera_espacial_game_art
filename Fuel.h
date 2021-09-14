#pragma once

#ifndef _Fuel
#define _Fuel

#include "ofMain.h" //Agregamos los m�todos y las clases de oF

class Fuel {

public: //Vista y acceso p�blico de estos m�todos

	struct bidon {
		ofImage fuel;
		int type;
		float x;
		float y;
	};

	Fuel(); //Constructor

	bidon bidones[4];

	//M�todos
	void setup();
	void drawFuel();

	//Constantes para ancho y alto de la pantalla en fullscreen
	const float width = 1920;
	const float height = 1080;
};

#endif //!Fuel
