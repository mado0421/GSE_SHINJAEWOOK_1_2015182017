#pragma once
#include "stdafx.h"

class Object
{
protected:
	Vector2f	m_pos;
	float		m_size;
	float		m_tFlow;
	float		m_tInterval;
	int			m_hp;
	int			m_team;

public:
	Object();
	~Object();

public:
	Vector2f	getPos() const			{ return m_pos; }
	float		getSize() const			{ return m_size; }
	float		getFlowTime() const		{ return m_tFlow; }
	float		getIntervalTime() const	{ return m_tInterval; }
	int			getHp() const			{ return m_hp; }
	int			getTeam() const			{ return m_team; }

	void setPos(const Vector2f& pos)	{ m_pos = pos; }
	void setPos(float x, float y)		{ m_pos.x = x; m_pos.y = y; }
	void setSize(float size)			{ m_size = size; }
	void setFlowTime(float time)		{ m_tFlow = time; }
	void setIntervalTime(float time)	{ m_tInterval = time; }
	void setHp(int hp)					{ m_hp = hp; }
	void setTeam(int team)				{ m_team = team; }

	void addHp(int val)					{ m_hp += val; }

public:
	virtual void render() const;
	virtual void update();

public:
	bool isHpZero() const { return m_hp <= 0; }

	virtual bool isDead() const {
		if (isHpZero()) return true;
		return false;
	}

};

class MovingObject : public Object
{
protected:
	Vector2f	m_dir;
	float		m_spd;

public:
	MovingObject();
	~MovingObject();

public:
	Vector2f getDir() const			{ return m_dir; }
	float getSpd() const			{ return m_spd; }

	void setDir(Vector2f dir)		{ m_dir = dir; }
	void setDir(float x, float y)	{ m_dir.x = x; m_dir.y = y; }
	void setSpd(float spd)			{ m_spd = spd; }

public:
	void move();

public:
	bool isOut() const {
		if (m_pos.x < WWIDTH)	return true;
		if (m_pos.x > 0)		return true;
		if (m_pos.y < WHEIGHT)	return true;
		if (m_pos.y > 0)		return true;
		return false;
	}
};

class Bullet : public MovingObject
{

};