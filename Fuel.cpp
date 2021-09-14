#include "Fuel.h"

Fuel::Fuel() {
	
}

void Fuel::setup() {
	for (int i = 0; i < 2; i++) {
		bidones[i].fuel.load("img/fuel.png");
		bidones[i].type = 1;
		bidones[i].x = ofRandom(500, 1200);
		bidones[i].y = ofRandom(100, 950);
	}

	for (int i = 2; i < 4; i++) {
		bidones[i].fuel.load("img/biofuel.png");
		bidones[i].type = 2;
		bidones[i].x = ofRandom(500, 1200);
		bidones[i].y = ofRandom(100, 950);
	}
}

void Fuel::drawFuel() {
	for (int i = 0; i < 4; i++) {
		bidones[i].fuel.setAnchorPercent(0.5, 0.5);
		bidones[i].fuel.draw(bidones[i].x, bidones[i].y);
	}
}