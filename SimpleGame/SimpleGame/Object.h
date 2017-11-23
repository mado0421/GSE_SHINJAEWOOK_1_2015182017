#include "stdafx.h"

#define LIFETIME 60.0f
#define HP 1.0f
#define SPD 20.0f

#define OBJECT_BUILDING		0x00
#define OBJECT_CHARACTER	0x01
#define OBJECT_BULLET		0x02
#define OBJECT_ARROW		0x03

#define TEAM_1 0x00
#define TEAM_2 0x01

#define SIZBUIL 50.0f
#define HPBUIL 500

#define SIZCHAR 15.0f
#define HPCHAR 100
#define SPDCHAR 300.0f

#define SIZBULL 2.0f
#define HPBULL 15
#define SPDBULL 600.0f

#define SIZARRO 2.0f
#define HPARRO 10
#define SPDARRO 100.0f

class Object
{
protected:
	Position	m_pos;
	Vector2f	m_dir;
	Color		m_col;
	float		m_size;
	float		m_spd;
	float		m_tLife;
	float		m_tFlow;
	float		m_tInterval;
	int			m_hp;
	int			m_team;
	bool		m_collide;

public:
	Object();
	Object(
		float x, float y, float z, float size,
		float r, float g, float b, float a,
		float lifeTime, int hp, float spd,
		float dirX, float dirY, int team)
		: m_pos(Position(x, y, z)), m_size(size)
		, m_col(Color(r, g, b, a))
		, m_tLife(lifeTime), m_hp(hp), m_spd(spd)
		, m_dir(Vector::Normalize(Vector2f(dirX, dirY)))
		, m_team(team)
	{
		m_tFlow = 0.0f;
		m_tInterval = 0.0f;
		m_collide = false;
	}
	Object(const Object& other)
	{
		m_pos			=other.m_pos;
		m_dir			=other.m_dir;
		m_col			=other.m_col;
		m_size			=other.m_size;
		m_spd			=other.m_spd;
		m_tLife			=other.m_tLife;
		m_tFlow			=other.m_tFlow;
		m_tInterval		=other.m_tInterval;
		m_hp			=other.m_hp;
		m_team			=other.m_team;
		m_collide		=other.m_collide;
	}


	virtual void	update(float elapsedTime);

	virtual Position	getPos() const			{ return m_pos;}
	virtual float		getPosX() const			{ return m_pos.x; }
	virtual float		getPosY() const			{ return m_pos.y; }
	virtual float		getPosZ() const			{ return m_pos.z; }
	virtual Color		getColor()const			{ return m_col;}
	virtual Vector2f	getDir()const			{ return m_dir;}
	virtual float		getSize()const			{ return m_size;}
	virtual bool		getCollided() const		{ return m_collide; }
	virtual int			getHp() const			{ return m_hp; }
	virtual float		getActInterval()const	{ return m_tInterval; }
	virtual float		getFlowTime()const		{ return m_tFlow; }
	virtual int			getTeam() const			{ return m_team; }

	virtual void		setPos(float x, float y, float z);
	virtual void		setColor(float r, float g, float b, float a);
	virtual void		setSize(float size);
	virtual void		setDir(float x, float y);
	virtual void		setCollided(bool state) { m_collide = state; }
	virtual void		setFlowTIme(float val) { m_tFlow = val; }

	virtual void		setHp(int hp) { this->m_hp = hp; }
	virtual void		addHp(int val) { m_hp += val; }

	bool isOut() const
	{
		return (m_pos.x + (m_dir.x * m_spd) - m_size * 2 <= -(WWIDTH / 2.0) || m_pos.x + (m_dir.x * m_spd) + m_size * 2 >= WWIDTH / 2.0 ||
			m_pos.y + (m_dir.y * m_spd) - m_size * 2 <= -(WHEIGHT / 2.0) || m_pos.y + (m_dir.y * m_spd) + m_size * 2 >= WHEIGHT / 2.0);
	};
	bool isCollide(const Object &other) const
	{
		return ((m_size + other.m_size)*(m_size + other.m_size) >=
			(m_pos.x - other.m_pos.x)*(m_pos.x - other.m_pos.x) +
			(m_pos.y - other.m_pos.y)*(m_pos.y - other.m_pos.y));
	};
	bool isLifeTimeEnd() const { return m_tLife <= 0; };
	bool isHpZero() const { return m_hp <= 0; };

	const bool isDead() const
	{
		if (isLifeTimeEnd()) return true;
		if (isHpZero()) return true;
		return false;
	}

	~Object();
};

class Building : public Object
{
public:
	Building();
	Building(
		float x, float y, int team)
		:Object(x, y, 0, SIZBUIL,
			0, 0, 0, 1, 0, HPBUIL,
			0, 0, 0, team)
	{
		m_tInterval = 10.0f;
	}
	~Building();
public:
	virtual void	update(float elapsedTime);
};
class Character : public Object
{
public:
	Character();
	Character(float x, float y,
		int team,
		float dirX, float dirY)
		:Object(x, y, 0, SIZCHAR,
			0, 0, 0, 1, 0, HPCHAR,
			SPDCHAR, dirX, dirY, team)
	{
		m_tInterval = 3.0f;
		if (team == TEAM_1) m_col = Color(1.0f, 0.0f, 0.0f, 1.0f);
		if (team == TEAM_2) m_col = Color(0.0f, 0.0f, 1.0f, 1.0f);
	}
	~Character();
public:
	virtual void	update(float elapsedTime);

};
class Bullet : public Object
{
public:
	Bullet();
	Bullet(float x, float y,
		int team,
		float dirX, float dirY)
		:Object(x, y, 0, SIZBULL,
			0, 0, 0, 1, 0, HPBULL,
			SPDBULL, dirX, dirY, team)
	{
		if (team == TEAM_1) m_col = Color(1.0f, 0.0f, 0.0f, 1.0f);
		if (team == TEAM_2) m_col = Color(0.0f, 0.0f, 1.0f, 1.0f);
	}
	~Bullet();
public:
	virtual void	update(float elapsedTime);

};
class Arrow : public Object
{
public:
	Arrow();
	Arrow(float x, float y,
		int team,
		float dirX, float dirY)
		:Object(x, y, 0, SIZARRO,
			0, 0, 0, 1, 0, HPARRO,
			SPDARRO, dirX, dirY, team)
	{
		if (team == TEAM_1) m_col = Color(0.5f, 0.2f, 0.7f, 1.0f);
		if (team == TEAM_2) m_col = Color(1.0f, 1.0f, 0.0f, 1.0f);
	}
	~Arrow();
public:
	virtual void	update(float elapsedTime);

};