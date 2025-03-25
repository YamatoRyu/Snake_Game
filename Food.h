#include <iostream>
#include <raylib.h>

using namespace std;

class Food
{
private:
	int cellSize = 30;
	int cellCount = 25;
	int offset = 75;

	Texture2D texture;

	bool ElementInDeque(Vector2 element, deque<Vector2> deque) {
		for (Vector2 part : deque) {
			if (Vector2Equals(part, element)) {
				return true;
			}
		}
		return false;
	}

public:
	Vector2 position;

	Food(deque<Vector2> snakeBody) {
		Image image = LoadImage("Graphics/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos(snakeBody);
	}

	~Food() {
		UnloadTexture(texture);
	}

	void Draw() {
		DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
	}

	Vector2 GenerateRandomCell() {
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);

		return Vector2{ x, y };
	}

	Vector2 GenerateRandomPos(deque<Vector2> snakeBody) {
		Vector2 position = GenerateRandomCell();

		while (ElementInDeque(position, snakeBody)) {
			position = GenerateRandomCell();
		}

		return position;
	}
};