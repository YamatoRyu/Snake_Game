#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

class Snake
{
private:
	int cellSize = 30;
	int cellCount = 25;
	int offset = 75;

	Color darkGreen = { 43, 51, 24, 255 };

public:
	deque<Vector2> body = { Vector2{6, 9}, Vector2{5, 9} };
	Vector2 direction = Vector2{ 1, 0 };
	bool addSegment = false;

	void Draw() {
		for (Vector2 part : body) {
			unsigned int x = part.x;
			unsigned int y = part.y;
			Rectangle rect = Rectangle{ (float) offset + x * cellSize, 
					(float) offset + y * cellSize, (float) cellSize, (float) cellSize };

			DrawRectangleRounded(rect, 0.5, 6, darkGreen);
		}
	}

	void Update() {
		body.push_front(Vector2Add(body[0], direction));

		if (addSegment) {
			addSegment = false;
		}

		else {
			body.pop_back();
		}
	}

	void Reset() {
		body = { Vector2{6, 9}, Vector2{5, 9} };
		direction = { 1, 0 };
	}
};