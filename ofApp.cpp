#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(960, 540); //Tamaño de la ventana por default

	ofSetFrameRate(60); //Seteamos el framerate en 60
	ofHideCursor(); //Ocultamos el cursor
	ofSetWindowTitle("Carrera Espacial. Lograras sobrevivir?");

	//Las variables boolenas
	fullScreen = false;
	pause = true;
	agree = false;
	jetOn = false;
	alienOn = false;
	plane1On = false;
	plane2On = false;
	gameover = false;

	//Cargamos las imagenes
	bg.load("img/background.png");
	jet.load("img/jet.png");
	alien.load("img/alien.png");
	plane1.load("img/plane1.png");
	plane2.load("img/plane2.png");
	loose.load("img/loose.png");
	win.load("img/win.png");
	introImage.load("img/intro.png");

	//Cargamos los sonidos
	intro.load("audio/intro.wav");
	intro.play();
	normal.load("audio/juegonormal.wav");
	fast.load("audio/juegorapido.wav");
	muerte.load("audio/muerte.wav");
	malbidon.load("audio/malbidon.wav");
	ecobidon.load("audio/ecobidon.wav");

	//Cargamos las fuentes
	resourceFT.load("lucon.ttf", 20);
	//Cargamos los textos
	resource_text = "Recursos = 0";

	//Inicializamos las variables de tipo enteras
	resources = 0;
	peopleMax = 6;
	//barra de tiempo
	timeBarHeight = 20;
	initialWidthTimeBar = 1000;
	timeBarWidth = initialWidthTimeBar;
	//Posicionamos la barra de tiempo
	timeBarPosition.set(width / 2 - initialWidthTimeBar / 2, height - height / 16);
	totalTime = 6.0f; //Tiempo total

	//Cargamos el setup de la clase Player
	player.setup();
	//People
	people.setup();
	//Objeto Fuel
	fuel.setup();
}

//--------------------------------------------------------------
void ofApp::update() {

	//Si el juego no esta en PAUSA
	if (!pause && gameover == false) {

		//Timer
		timer();

		//Colisión personaje y personas
		playerCrash();

		//Colisión personaje y fuel
		fuelCollector();

		//Escenario/Paisaje
		scenery();

		//Actualizar personas
		people.update();

		soundSettings();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	//Si el usuario presiona f/F escalamos todo para la pantalla completa
	if (fullScreen)
		ofScale(ofGetScreenWidth() / width, ofGetScreenHeight() / height);
	else
		ofScale(ofGetWidth() / width, ofGetHeight() / height);

	//Dibujamos las imagenes con sus respectivas posiciones dinamicas

	bg.draw(0, 0, width, height);//fondo
	//bidones
	fuel.drawFuel();
	//Personas
	people.drawPeople();
	//Jugador
	player.draw();
	jet.draw(jetPos);//jet
	alien.draw(alienPos);
	plane1.draw(plane1Pos);
	plane2.draw(plane2Pos);

	//Color de la barra de tiempo
	ofSetColor(ofColor::red);
	ofDrawRectangle(timeBarPosition, timeBarWidth, timeBarHeight);

	//Color del texto de recursos
	ofSetColor(ofColor::white);
	resourceFT.drawString(resource_text, 20, 60);

	//Si esta en pausa muestra el texto "Presiona ENTER para jugar"
	if (pause) {
		introImage.draw(0, 0);
	}

	for (int i = 0; i < 6; i++) {
		if ((people.humanos[i].y > player.y - 25) && (people.humanos[i].y < player.y + 25) && (people.humanos[i].x > player.x - 25) && (people.humanos[i].x < player.x + 25)) {
			loose.draw(0, 0);
		}
	}

	if (resources >= 100) {
		win.draw(0, 0);
		pause = !pause;
	}

	//Si el tiempo se termina
	if (timeBarWidth <= 0.0f)
	{
		loose.draw(0, 0);
	}

	
}
 
//--- CALLBACK, esta escuchando si el usuario presiona determinada tecla ---------------
void ofApp::keyPressed(int key) {

	//Si presiona f/F
	if (key == 'f' || key == 'F') {
		fullScreen = !fullScreen;
		ofToggleFullscreen(); //fullscreen
	}

	//Si presiona ENTER
	if (key == OF_KEY_RETURN) {

		//Reseteamos recursos y tiempo
		resources = 0;
		totalTime = 6.0f;
		ofResetElapsedTimeCounter();
		//Pausa se vuelve false
		pause = !pause;
		//Volvemos a posicionar al jugador en la posición de origen.
		player.x = width / 2;
		player.y = height - 200;

		//Reseteamos las posiciones de las personas
		for (int i = 0; i < 6; i++) {
			people.humanos[i].x = ofRandom(500, 1200);
			people.humanos[i].y = ofRandom(-1, -20);
		}

		//Reseteamos las posiciones de los bidones
		for (int i = 0; i < 4; i++) {
			fuel.bidones[i].x = ofRandom(500, 1200);
			fuel.bidones[i].y = ofRandom(100, 950);
		}

		//Las teclas de movimiento responden
		agree = true;

		soundSettings();
	}

	//Si no esta en pausa estas teclas responden
	if (agree) {
		//Si presiona flecha derecha
		if (key == OF_KEY_RIGHT && player.x < 1380) {
			//El juegador se mueve a la derecha en de 25 en 25
			player.x += 25;
			totalTime += 0.1;
			agree = false;
		}

		//Si presiona flecha izquierda
		if (key == OF_KEY_LEFT && player.x > 490) {

			player.x -= 25;
			totalTime += 0.1;
			agree = false;
		}

		//Si presiona flecha arriba
		if (key == OF_KEY_UP) {

			player.y -= 25;
			totalTime += 0.1;
			agree = false;
		}

		//Si presiona flecha abajo
		if (key == OF_KEY_DOWN && player.y < height - 100) {

			player.y += 25;
			totalTime += 0.1;
			agree = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	//Si no esta en pausa, agree es true.
	if (!pause) {
		agree = true;
	}
}

//--------------------------------------------------------------
void ofApp::timer() {
	//La barra de tiempo se ira actualizando segun el tiempo va pasando
	timeBarWidth = initialWidthTimeBar - initialWidthTimeBar * (ofGetElapsedTimef() / totalTime);

	//Si el tiempo se termina
	if (timeBarWidth <= 0.0f)
	{
		pause = true; //Se pausa el juego
		muerte.play();
	}

	if (timeBarWidth <= 2.0f) {
	
	}
}

//--------------------------------------------------------------
void ofApp::scenery() {
	//Si los elementos estan en false
	if (!jetOn) {
		speed = ofRandom(1, 2); //velocidad random para cada uno
		jetPos.set(ofRandom(200), -400); //comienza fuera de la pantalla
		jetOn = true; //inicia el movimiento
	}
	else { //cuando esta en estado true
		jetPos.y += speed; //la posicion aumenta en relación a la velocidad
		if (jetPos.y > height + ofRandom(500)) jetOn = false; //Si sale de la pantalla vuelve a iniciar el ciclo
	}

	if (!alienOn) {
		speed = ofRandom(1, 3);
		alienPos.set(ofRandom(1300, 1900), -900);
		alienOn = true;
	}
	else {
		alienPos.y += speed;
		if (alienPos.y > height + ofRandom(500)) alienOn = false;
	}

	if (!plane1On) {
		speed = ofRandom(1, 4);
		plane1Pos.set(ofRandom(1600, 1900), -900);
		plane1On = true;
	}
	else {
		plane1Pos.y += speed;
		if (plane1Pos.y > height + ofRandom(500)) plane1On = false;
	}

	if (!plane2On) {
		speed = ofRandom(3, 6);
		plane2Pos.set(ofRandom(1700, 1900), ofRandom(-200));
		plane2On = true;
	}
	else {
		plane2Pos.y += speed;
		if (plane2Pos.y > height + ofRandom(-500)) plane2On = false;
	}
}

void ofApp::soundSettings() {
	if (OF_KEY_RETURN) {

		if (pause) {
			normal.stop();
			intro.setLoop(true);
			intro.play();
		}

		if (!pause) {
			
			if (intro.isPlaying()) {
				intro.stop();
				normal.setLoop(true);
				normal.play();
			}
		}
		else if (pause && normal.isPlaying()) {
			normal.stop();
			intro.setLoop(true);
			intro.play();
		}
	}
}

//Colisión entre personaje y personas --------------------------
void ofApp::playerCrash() {
	for (int i = 0; i < 6; i++) {

		if ((people.humanos[i].y > player.y - 25) && (people.humanos[i].y < player.y + 25) && (people.humanos[i].x > player.x - 25) && (people.humanos[i].x < player.x + 25)) {
			pause = true;
			agree = false;

			muerte.play();
		}
	}
}

//Colisión entre personaje y combustible -----------------------
void ofApp::fuelCollector() {
	//Texto que muestra el estado de los recursos recolectados
	resource_text = "Recursos = " + ofToString(resources);

	//PP agarra combustible contaminante de tipo 1
	for (int i = 0; i < 4; i++) {
		if ((fuel.bidones[i].y > player.y - 25) && (fuel.bidones[i].y < player.y + 25) && (fuel.bidones[i].x > player.x - 25) && (fuel.bidones[i].x < player.x + 25) && fuel.bidones[i].type == 1) {
			resources += 5;
			totalTime -= 5;

			malbidon.play();

			fuel.bidones[i].x = ofRandom(500, 1200);
			fuel.bidones[i].y = ofRandom(100, 950);
		}
		else if ((fuel.bidones[i].y > player.y - 25) && (fuel.bidones[i].y < player.y + 25) && (fuel.bidones[i].x > player.x - 25) && (fuel.bidones[i].x < player.x + 25) && fuel.bidones[i].type == 2) {
			resources += 10;
			totalTime += 10;

			ecobidon.play();

			fuel.bidones[i].x = ofRandom(500, 1200);
			fuel.bidones[i].y = ofRandom(100, 950);
		}
	} 
}