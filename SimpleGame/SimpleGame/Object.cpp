#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

void Object::update(float elapsedTime)
{
	float spdX = dir.x * elapsedTime * spd;
	float spdY = dir.y * elapsedTime * spd;

	pos.x += spdX;
	pos.y += spdY;

	flowTime += elapsedTime;
	lifeTime -= elapsedTime;
}

Position Object::getPos()const
{
	return pos;
}

Color Object::getColor()const
{
	return color;
}

Vector2f Object::getDir()const
{
	return dir;
}

float Object::getSize()const
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
	return(pos.x + dir.x - size < -(WWIDTH / 2.0) || pos.x + dir.x + size > WWIDTH / 2.0 ||
			pos.y + dir.y - size < -(WHEIGHT / 2.0) || pos.y + dir.y + size > WHEIGHT / 2.0);
}

bool Object::isCollide(const Object &other)
{
	// 사각형 충돌체크 or 원형 충돌체크
	// 지금은 귀찮으니까 원형 충돌체크로 패스
	// 두 원점 사이의 거리가 두 오브젝트의 사이즈의 합보다 작거나 같으면 충돌로 판정
	return ((size + other.size)*(size + other.size) >=
		(pos.x - other.pos.x)*(pos.x - other.pos.x) +
		(pos.y - other.pos.y)*(pos.y - other.pos.y));
}

bool Object::isLifeTimeEnd()
{
	return (lifeTime <= 0);
}

bool Object::isHpZero()
{
	return (hp <= 0);
}

Object::~Object()
{
}

Building::Building()
{
}

Building::~Building()
{
}

void Building::update(float elapsedTime)
{
	flowTime += elapsedTime;
}

Character::Character()
{
}

Character::~Character()
{
}

void Character::update(float elapsedTime)
{
	float spdX = dir.x * elapsedTime * spd;
	float spdY = dir.y * elapsedTime * spd;

	pos.x += spdX;
	pos.y += spdY;

	flowTime += elapsedTime;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(float elapsedTime)
{
	float spdX = dir.x * elapsedTime * spd;
	float spdY = dir.y * elapsedTime * spd;

	pos.x += spdX;
	pos.y += spdY;

	flowTime += elapsedTime;
}

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::update(float elapsedTime)
{
	float spdX = dir.x * elapsedTime * spd;
	float spdY = dir.y * elapsedTime * spd;

	pos.x += spdX;
	pos.y += spdY;

	flowTime += elapsedTime;
}
