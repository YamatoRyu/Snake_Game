#include <iostream>
#include <raylib.h>

#include "Game.h"

using namespace std;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque) {
	for (Vector2 part : deque) {
		if (Vector2Equals(part, element)) {
			return true;
		}
	}
	return false;
}

bool eventTriggered(double interval) {
	double currentTime = GetTime();

	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;

		return true;
	}

	return false;
}

int main() {
	Color green = { 173, 204, 96, 255 };
	Color darkGreen = { 43, 51, 24, 255 };

	int cellSize = 30;
	int cellCount = 25;
	int offset = 75;

	cout << "Starting the game" << endl;
	InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake Game");
	SetTargetFPS(60);

	Game game = Game();

	while (!WindowShouldClose()) {
		BeginDrawing();

		if (eventTriggered(0.2)) {
			game.Update();
		}

		if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.direction.y != 1) {
			game.snake.direction = { 0, -1 };
			game.running = true;
		}

		else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.direction.y != -1) {
			game.snake.direction = { 0, 1 };
			game.running = true;
		}

		else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.direction.x != 1) {
			game.snake.direction = { -1, 0 };
			game.running = true;
		}

		else if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.direction.x != -1) {
			game.snake.direction = { 1, 0 };
			game.running = true;
		}

		ClearBackground(green);
		DrawRectangleLinesEx(Rectangle{ (float) offset - 5, (float) offset - 5, (float) cellSize 
				* cellCount + 10, (float) cellSize * cellCount + 10 }, 5, darkGreen);

		DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
		DrawText(TextFormat("Score: %i", game.score), offset - 5, offset + cellSize * 
				cellCount + 10, 40, darkGreen);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();
	cout << "Quitting the game" << endl;
}