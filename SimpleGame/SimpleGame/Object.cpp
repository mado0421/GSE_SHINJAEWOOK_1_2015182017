#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

void Object::Update()
{
//	float time;
	pos.x += dir.x;
	pos.y += dir.y;
}

Position Object::GetPos()
{
	return pos;
}

Color Object::GetColor()
{
	return color;
}

Vector2f Object::GetDir()
{
	return dir;
}

float Object::GetSize()
{
	return size;
}

void Object::SetPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::SetColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Object::SetSize(float size)
{
	this->size = size;
}

void Object::SetDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}

Object::~Object()
{
}
