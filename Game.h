#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

#include "Food.h"
#include "Snake.h"

using namespace std;

class Game
{
private:
	int cellSize = 30;
	int cellCount = 25;

	bool ElementInDeque(Vector2 element, deque<Vector2> deque) {
		for (Vector2 part : deque) {
			if (Vector2Equals(part, element)) {
				return true;
			}
		}
		return false;
	}

public:
	int score = 0;

	Food food = Food(snake.body);
	Snake snake = Snake();
	bool running = true;

	void Draw() {
		food.Draw();
		snake.Draw();
	}

	void Update() {
		if (running)
		{
			snake.Update();
			CheckCollisionWithFood();
			CheckCollisionWithEdges();
			CheckCollisionWithTail();
		}
	}

	void CheckCollisionWithFood() {
		if (Vector2Equals(snake.body[0], food.position)) {
			food.position = food.GenerateRandomPos(snake.body);
			snake.addSegment = true;
			score++;
		}
	}

	void CheckCollisionWithEdges() {
		if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
			GameOver();
		}

		if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
			GameOver();
		}
	}

	void GameOver() {
		snake.Reset();
		food.position = food.GenerateRandomPos(snake.body);
		running = false;
		score = 0;
	}

	void CheckCollisionWithTail() {
		deque<Vector2> headlessBody = snake.body;
		headlessBody.pop_front();

		if (ElementInDeque(snake.body[0], headlessBody)) {
			GameOver();
		}
	}
};