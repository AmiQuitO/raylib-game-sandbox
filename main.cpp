#include "main.h"

void WorldDraw() {
	for (int i = 0; i < GAMEHEIGHT; i++) {
		for (int j = 0; j < GAMEWIDTH; j++) {
			particles[i][j].Draw();
		}
	}
}


int main() {
	InitWindow(800, 800, "Sandbox");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {


		BeginDrawing();
		ClearBackground(BLACK);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();
			particles[(int)mousePos.y][(int)mousePos.x].SetColor(YELLOW); // sand for now
		}
		WorldDraw();

		DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}