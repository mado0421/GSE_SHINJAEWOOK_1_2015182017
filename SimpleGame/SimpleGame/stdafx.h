#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <vector>

struct Position {
	float x, y, z;
	Position() {
		x = y = z = 0;
	}
	Position(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}
};

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