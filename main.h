#pragma once

#include "raylib.h"
#include <string>
#include <cmath>


const int GAMEWIDTH = 40;
const int GAMEHEIGHT = 40;

const int PARTICLESIZE = 20;

class Particle {
private:
	Vector2 position;
	Color color;

public:
	Particle() {
		color = BLACK;
	}

	void SetColor(Color c) {
		color = c;
	}

	void Draw() {
		DrawRectangle((int)position.x * 20, (int)position.y * 20, PARTICLESIZE, PARTICLESIZE, color);
	}
};
Particle particles[GAMEHEIGHT][GAMEWIDTH];