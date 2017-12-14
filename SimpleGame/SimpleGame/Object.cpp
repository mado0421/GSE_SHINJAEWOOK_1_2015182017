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

void Building::setTarget(Object * target)
{
	m_pTarget = target;
}

Object * Building::getTarget()
{
	return m_pTarget;
}

Character::Character()
{
}

Character::~Character()
{
}

void Character::update(float elapsedTime)
{
	float spdX, spdY;
	if (m_pTarget == nullptr)
	{
		spdX = m_dir.x * elapsedTime * m_spd;
		spdY = m_dir.y * elapsedTime * m_spd;

		m_pos.x += spdX;
		m_pos.y += spdY;
	}
	else
	{
		if (getDistance(m_pos, m_pTarget->getPos()) > m_range)
		{
			Vector2f pos(
				m_pTarget->getPosX() - m_pos.x,
				m_pTarget->getPosY() - m_pos.y);
			pos = Vector::Normalize(pos);

			m_pos.x += pos.x * elapsedTime * m_spd;
			m_pos.y += pos.y * elapsedTime * m_spd;
			m_dir.x = pos.x;
		}
	}


	m_tFlow += elapsedTime;
}

void Character::setTarget(Object *target)
{
	m_pTarget = target;
}

Object * Character::getTarget()
{
	return m_pTarget;
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
