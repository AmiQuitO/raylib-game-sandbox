#pragma once

#include "raylib.h"
#include <string>
#include <cmath>
#include <cstring>


const int GAMEWIDTH = 160;
const int GAMEHEIGHT = 160;

const int WINDOWWIDTH = 800;
const int WINDOWHEIGHT = 800;

const int PARTICLESIZE = 5;

Vector2 mousePos;
int scrollY = 1;

int type = 1; //0 = air, 1 = sand, 2 = water, 3 = solid
Color typeC = YELLOW;
const char* typeN = "Sand";

class Particle {
private:
	Vector2 position;
	Color color;
	bool hasMoved = false;

public:
	void SetPosition(Vector2 pos) {
		position = pos;
	}

	void SetColor(Color c) {
		color = c;
	}

	bool IsColor(Color c) {
		return color.r == c.r && color.g == c.g && color.b == c.b;
	}

	void Draw() {
		DrawRectangle((int)position.x * PARTICLESIZE, (int)position.y * PARTICLESIZE, PARTICLESIZE, PARTICLESIZE, color);
	}
};
Particle particles[GAMEHEIGHT][GAMEWIDTH];