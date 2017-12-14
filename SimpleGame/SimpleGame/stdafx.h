#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>

#include <vector>

#define GLUT_STROKE_ROMAN
#define GLUT_STROKE_MONO_ROMAN
#define GLUT_BITMAP_9_BY_15   
#define GLUT_BITMAP_8_BY_13
#define GLUT_BITMAP_TIMES_ROMAN_10
#define GLUT_BITMAP_TIMES_ROMAN_24
#define GLUT_BITMAP_HELVETICA_10
#define GLUT_BITMAP_HELVETICA_12
#define GLUT_BITMAP_HELVETICA_18


#define WWIDTH 500
#define WHEIGHT 800

#define LEV_BACK 0.9
#define LEV_BUILD 0.1
#define LEV_CHARA 0.2
#define LEV_FLYCHARA 0.25
#define LEV_BULLE 0.3
#define LEV_ARROW 0.3	

#define DEBUG

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

inline float getDistance(const Position& myPos, const Position& tarPos)
{
	return (myPos.x - tarPos.x)*(myPos.x - tarPos.x) + (myPos.y - tarPos.y)*(myPos.y - tarPos.y);
}


namespace Vector {
	inline float Length(Vector2f vec2f)
	{
		return sqrt(vec2f.x*vec2f.x + vec2f.y*vec2f.y);
	}

	inline Vector2f Normalize(Vector2f vec2f)
	{
		float lenght = Length(vec2f);
		if (lenght == 0) return Vector2f(0.0f, 0.0f);
		return Vector2f(vec2f.x / lenght, vec2f.y / lenght);
	}
}