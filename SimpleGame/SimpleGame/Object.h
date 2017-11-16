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

#define SIZCHAR 5.0f
#define HPCHAR 10
#define SPDCHAR 300.0f

#define SIZBULL 2.0f
#define HPBULL 20
#define SPDBULL 600.0f

#define SIZARRO 2.0f
#define HPARRO 10
#define SPDARRO 100.0f

class Object
{
protected:
	Position	pos;
	Vector2f	dir;
	Color		color;
	float		size;
	float		spd;
	float		lifeTime;
	int			hp;
	int			type;
	int			team;

	float		flowTime;
	float		actInterval;
	bool		collided;
public:
	Object();
	Object(
		float x, float y, float z, float size, 
		float r, float g, float b, float a, 
		float lifeTime, int hp, float spd,
		float dirX, float dirY, int type, int team)
		: pos(Position(x, y, z)), size(size)
		, color(Color(r, g, b, a))
		, lifeTime(lifeTime), hp(hp), spd(spd)
		, dir(Vector::Normalize(Vector2f(dirX, dirY)))
		, type(type)
		, team(team)
	{
		flowTime = 0.0f;
		actInterval = 0.0f;
		collided = false;
	}
	Object(const Object& other)
	{
		pos			= other.pos;
		dir			= other.dir;
		color		= other.color;
		size		= other.size;
		spd			= other.spd;
		lifeTime	= other.lifeTime;
		hp			= other.hp;
		type		= other.type;
		team		= other.team;

		flowTime	= other.flowTime;
		actInterval = other.actInterval;
		collided	= other.collided;
	}

	virtual void	update(float elapsedTime);

	virtual Position	getPos() const;
	virtual float		getPosX() const{ return pos.x; }
	virtual float		getPosY() const{ return pos.y; }
	virtual float		getPosZ() const{ return pos.z; }
	virtual Color		getColor()const;
	virtual Vector2f	getDir()const;
	virtual float		getSize()const;
	virtual bool		getCollided() const { return collided; }
	virtual int			getType()const { return type; }
	virtual int			getHp() const { return hp; }
	virtual float		getActInterval()const { return actInterval; }
	virtual float		getFlowTime()const { return flowTime; }
	virtual int			getTeam() const { return team; }

	virtual void		setPos(float x, float y, float z);
	virtual void		setColor(float r, float g, float b, float a);
	virtual void		setSize(float size);
	virtual void		setDir(float x, float y);
	virtual void		setCollided(bool state) { collided = state; }
	virtual void		setFlowTIme(float val) { flowTime = val; }

	virtual void		setHp(int hp) { this->hp = hp; }
	virtual void		addHp(int val) { hp += val; }
	
	virtual bool		isOut();
	virtual bool		isCollide(const Object &other);
	virtual bool		isLifeTimeEnd();
	virtual bool		isHpZero();

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
			0, 0, 0, OBJECT_BUILDING, team)
	{
		actInterval = 10.0f;
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
			SPDCHAR, dirX, dirY, OBJECT_CHARACTER, team)
	{
		actInterval = 3.0f;
		if (team == TEAM_1) color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		if (team == TEAM_2) color = Color(0.0f, 0.0f, 1.0f, 1.0f);
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
			SPDBULL, dirX, dirY, OBJECT_BULLET, team)
	{
		if (team == TEAM_1) color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		if (team == TEAM_2) color = Color(0.0f, 0.0f, 1.0f, 1.0f);
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
			SPDARRO, dirX, dirY, OBJECT_ARROW, team)
	{
		if (team == TEAM_1) color = Color(0.5f, 0.2f, 0.7f, 1.0f);
		if (team == TEAM_2) color = Color(1.0f, 1.0f, 0.0f, 1.0f);
	}
	~Arrow();
public:
	virtual void	update(float elapsedTime);

};