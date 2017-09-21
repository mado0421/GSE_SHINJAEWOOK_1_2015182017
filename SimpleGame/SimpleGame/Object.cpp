#include "Object.h"

Object::Object()
{
}

Position Object::GetPos()
{
	return pos;
}

Color Object::GetColor()
{
	return color;
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

Object::~Object()
{
}
