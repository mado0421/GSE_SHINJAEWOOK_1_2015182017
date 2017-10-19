#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <vector>

#define WWIDTH 500
#define WHEIGHT 500
#define MAX_OBJECTS_COUNT 150

struct Vector3f {
	float x, y, z;
	Vector3f() {
		x = y = z = 0;
	}
	Vector3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}
};
typedef Vector3f Position;

struct Color {
	float r, g, b, a;
	Color() {
		r = g = b = a = 0;
	}
	Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{

	}
};

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