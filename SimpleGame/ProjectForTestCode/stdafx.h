#pragma once

#define WWIDTH 500
#define WHEIGHT 800

struct Vector2f {
	float x, y;
	Vector2f() {
		x = y = 0;
	}
	Vector2f(float x, float y)
		: x(x), y(y)
	{

	}
};