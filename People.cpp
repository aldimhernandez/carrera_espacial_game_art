#include "People.h" //Referencia al header donde se declaran los métodos

People::People() {

}

void People::setup() { //Cargamos las imagenes en un for.

	humanos[0].humano.load("img/human1.png");
	humanos[1].humano.load("img/human2.png");
	humanos[2].humano.load("img/human3.png");
	humanos[3].humano.load("img/human4.png");
	humanos[4].humano.load("img/human5.png");
	humanos[5].humano.load("img/human6.png");

	for (int i = 0; i < 6; i++) {
		humanos[i].x = ofRandom(490, 1200);
		humanos[i].y = ofRandom(-100, -200);
		humanos[i].speed = ofRandom(2, 10);
	}
}

void People::update() {

	for (int i = 0; i < 6; i++) {
		humanos[i].y += humanos[i].speed;

		if (humanos[i].y > height) {
			humanos[i].x = ofRandom(490, 1200);
			humanos[i].y = ofRandom(-100, -200);
			humanos[i].speed = ofRandom(2, 10);
		}
	}
}

void People::drawPeople() { //dibujamos las imagenes
	for (int i = 0; i < 6; i++) {
		humanos[i].humano.setAnchorPercent(0.5, 0.5);
		humanos[i].humano.draw(humanos[i].x, humanos[i].y);
	}
}