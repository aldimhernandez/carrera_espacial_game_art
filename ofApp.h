#pragma once

#include "ofMain.h"
#include "Player.h"
#include "People.h"
#include "Fuel.h"

class ofApp : public ofBaseApp {

public:
	//Funciones OF
	void setup();
	void update();
	void draw();

	//Callbacks
	void timer();
	void scenery();
	void soundSettings();
	void playerCrash();
	void fuelCollector();
	void keyPressed(int key);
	void keyReleased(int key);

	//Constantes para ancho y alto de la pantalla en fullscreen
	const float width = 1920;
	const float height = 1080;

	//Booleanos
	bool fullScreen, jetOn, alienOn, plane1On, plane2On, pause, agree, gameover;
	//Variables de tipo entero
	int resources, peopleMax, x, y;
	//Variables de tipo decimal
	float speed, initialWidthTimeBar, timeBarWidth, timeBarHeight, totalTime;
	//Imagenes
	ofImage bg, jet, plane1, plane2, alien, loose, win, introImage;
	//Vector para guardar 2 valores, en este caso de posiciones.
	ofVec2f jetPos, plane1Pos, plane2Pos, alienPos, messageTextPos, timeBarPosition;
	//Fuentes
	ofTrueTypeFont resourceFT, messageFT;
	//Textos
	string resource_text, message_text;
	//Sonidos
	ofSoundPlayer intro, normal, fast, muerte, malbidon, ecobidon;

	Player player;
	People people;
	//People people[6];
	Fuel fuel;
};
