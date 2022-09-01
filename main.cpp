#include "main.h"

void WorldDraw() {
	for (int i = 0; i < GAMEHEIGHT; i++) {
		for (int j = 0; j < GAMEWIDTH; j++) {
			particles[i][j].Draw();
		}
	}
}

void WorldGenerate() {
	for (int i = 0; i < GAMEHEIGHT; i++) {
		for (int j = 0; j < GAMEWIDTH; j++) {
			particles[i][j].SetPosition(Vector2{ (float)j, (float)i });
			particles[i][j].SetColor(BLACK);
		}
	}
}

void WorldMove() { // priority sand > water > air
	for (int i = GAMEHEIGHT; i > 0; i--) {
		for (int j = GAMEWIDTH; j > 0; j--) {
			// sand
			if (particles[i][j].IsColor(YELLOW)) {

				if (particles[i][j].IsColor(YELLOW) && particles[i + 1][j].IsColor(BLACK) && i < GAMEHEIGHT) { // some sand can get off screen what?
					particles[i][j].SetColor(BLACK);
					particles[i + 1][j].SetColor(YELLOW);
				}
				else if (particles[i][j].IsColor(YELLOW) && particles[i + 1][j - 1].IsColor(BLACK) && i < GAMEHEIGHT && j < GAMEWIDTH - 1 && j>0) { // left
					particles[i][j].SetColor(BLACK);
					particles[i + 1][j - 1].SetColor(YELLOW);
				}
				else if (particles[i][j].IsColor(YELLOW) && particles[i + 1][j + 1].IsColor(BLACK) && i < GAMEHEIGHT && j < GAMEWIDTH - 1) { // right
					particles[i][j].SetColor(BLACK);
					particles[i + 1][j + 1].SetColor(YELLOW);
				}
				else if (particles[i][j].IsColor(YELLOW) && particles[i + 1][j].IsColor(BLUE) && i < GAMEHEIGHT) {
					particles[i][j].SetColor(BLUE);
					particles[i + 1][j].SetColor(YELLOW);
				}
				else if (particles[i][j].IsColor(YELLOW) && particles[i + 1][j - 1].IsColor(BLUE) && i < GAMEHEIGHT && j < GAMEWIDTH - 1 && j>0) { // left
					particles[i][j].SetColor(BLUE);
					particles[i + 1][j - 1].SetColor(YELLOW);
				}
				else if (particles[i][j].IsColor(YELLOW) && particles[i + 1][j + 1].IsColor(BLUE) && i < GAMEHEIGHT && j < GAMEWIDTH - 1) { // right
					particles[i][j].SetColor(BLUE);
					particles[i + 1][j + 1].SetColor(YELLOW);
				}
			}
			// water
			if (particles[i][j].IsColor(BLUE)) {
				if (particles[i][j].IsColor(BLUE) && particles[i + 1][j].IsColor(BLACK) && i < GAMEHEIGHT) {
					particles[i][j].SetColor(BLACK);
					particles[i + 1][j].SetColor(BLUE);
				}
				for (int k = 0; k < GAMEWIDTH; k++) {
					if (particles[i][j].IsColor(BLUE) && particles[i + 1][j - k].IsColor(BLACK) && i < GAMEHEIGHT && j < GAMEWIDTH - 1 && j>0) { // left
						particles[i][j].SetColor(BLACK);
						particles[i + 1][j - k].SetColor(BLUE);
					}
					else if (particles[i][j].IsColor(BLUE) && particles[i + 1][j + k].IsColor(BLACK) && i < GAMEHEIGHT && j < GAMEWIDTH - 1) { // right
						particles[i][j].SetColor(BLACK);
						particles[i + 1][j + k].SetColor(BLUE);
					}
				}
			}
		}
	}
}

int main() {
	InitWindow(800, 800, "Sandbox");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	WorldGenerate();

	while (!WindowShouldClose()) {
		
		mousePos = GetMousePosition();

		// drawing 
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			if (mousePos.x < WINDOWWIDTH && mousePos.y < WINDOWHEIGHT && mousePos.x > 0 && mousePos.y > 0) {
				for (int i = 1 - scrollY; i < scrollY; i++) {
					for (int j = 1 - scrollY; j < scrollY; j++) {
						if (floor(mousePos.x) + j * PARTICLESIZE < WINDOWWIDTH && floor(mousePos.y) + i * PARTICLESIZE < WINDOWHEIGHT
							&& floor(mousePos.x) - i * PARTICLESIZE > 0 && floor(mousePos.y) - i * PARTICLESIZE > 0) {
							particles[(int)(mousePos.y / PARTICLESIZE) + i][(int)(mousePos.x / PARTICLESIZE) + j].SetColor(typeC);
						}
					}
				}
			}
		}

		// changing type
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			type++;
			if (type > 3) {
				type = 0;
			}

			if (type == 0) {
				typeC = BLACK;
				typeN = "Air";
			}
			else if (type == 1) {
				typeC = YELLOW;
				typeN = "Sand";
			}
			else if (type == 2) {
				typeC = BLUE;
				typeN = "Water";
			}
			else if (type == 3) {
				typeC = GRAY;
				typeN = "Solid";
			}
		}

		// scrolling 
		scrollY += GetMouseWheelMove();

		if (scrollY < 1) {
			scrollY = 1;
		}

		BeginDrawing();
		ClearBackground(WHITE);

		WorldMove();

		WorldDraw();

		// cursor
		for (int i = 1 - scrollY; i < scrollY; i++) {
			for (int j = 1 - scrollY; j < scrollY; j++) {
				if (i == 1 - scrollY || i == scrollY - 1 || j == 1 - scrollY || j == scrollY - 1) {
					DrawRectangle(mousePos.x + PARTICLESIZE * i, mousePos.y + PARTICLESIZE * j, PARTICLESIZE, PARTICLESIZE, WHITE);
				}
			}
		}
		DrawText(typeN, mousePos.x - MeasureText(typeN, 20)/2, mousePos.y-20, 20, typeC);

		DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}