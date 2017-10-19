#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

void Object::update()
{
	/*
	float elapsedTime;

	Vector2f spd(dir.x * elapsedTime, dir.y * elapsedTime);
					or
	float spdX = dir.x * elapsedTime;
	float spdY = dir.y * elapsedTime;

	pos.x += spdX;
	pos.y += spdY;
	*/
	pos.x += dir.x;
	pos.y += dir.y;
}

Position Object::getPos()
{
	return pos;
}

Color Object::getColor()
{
	return color;
}

Vector2f Object::getDir()
{
	return dir;
}

float Object::getSize()
{
	return size;
}

void Object::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Object::setSize(float size)
{
	this->size = size;
}

void Object::setDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}

bool Object::isOut()
{
	return(pos.x + dir.x + size < -(WWIDTH / 2.0) || pos.x + dir.x - size > WWIDTH / 2.0 ||
			pos.y + dir.y + size < -(WHEIGHT / 2.0) || pos.y + dir.y - size > WHEIGHT / 2.0);
}

bool Object::isCollide(const Object &other)
{
	// �簢�� �浹üũ or ���� �浹üũ
	// ������ �������ϱ� ���� �浹üũ�� �н�
	// �� ���� ������ �Ÿ��� �� ������Ʈ�� �������� �պ��� �۰ų� ������ �浹�� ����
	return ((size + other.size)*(size + other.size) >=
		(pos.x - other.pos.x)*(pos.x - other.pos.x) +
		(pos.y - other.pos.y)*(pos.y - other.pos.y));
}

Object::~Object()
{
}
