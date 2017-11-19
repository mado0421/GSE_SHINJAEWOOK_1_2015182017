#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

void Object::update(float elapsedTime)
{
	float spdX = m_dir.x * elapsedTime * m_spd;
	float spdY = m_dir.y * elapsedTime * m_spd;

	m_pos.x += spdX;
	m_pos.y += spdY;

	m_tFlow += elapsedTime;
	m_tLife -= elapsedTime;
}

void Object::setPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Object::setColor(float r, float g, float b, float a)
{
	m_col.r = r;
	m_col.g = g;
	m_col.b = b;
	m_col.a = a;
}

void Object::setSize(float size)
{
	this->m_size = size;
}

void Object::setDir(float x, float y)
{
	m_dir.x = x;
	m_dir.y = y;
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
	m_tFlow += elapsedTime;
}

Character::Character()
{
}

Character::~Character()
{
}

void Character::update(float elapsedTime)
{
	float spdX = m_dir.x * elapsedTime * m_spd;
	float spdY = m_dir.y * elapsedTime * m_spd;

	m_pos.x += spdX;
	m_pos.y += spdY;

	m_tFlow += elapsedTime;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(float elapsedTime)
{
	float spdX = m_dir.x * elapsedTime * m_spd;
	float spdY = m_dir.y * elapsedTime * m_spd;

	m_pos.x += spdX;
	m_pos.y += spdY;

	m_tFlow += elapsedTime;
}

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::update(float elapsedTime)
{
	float spdX = m_dir.x * elapsedTime * m_spd;
	float spdY = m_dir.y * elapsedTime * m_spd;

	m_pos.x += spdX;
	m_pos.y += spdY;

	m_tFlow += elapsedTime;
}
