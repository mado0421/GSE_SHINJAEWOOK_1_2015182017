#include "stdafx.h"

#define LIFETIME 60.0f
#define HP 1.0f
#define SPD 20.0f

#define OBJECT_BUILDING		0x00
#define OBJECT_CHARACTER	0x01
#define OBJECT_BULLET		0x02
#define OBJECT_ARROW		0x03

class Object
{
private:
	Position	pos;
	Vector2f	dir;
	Color		color;
	float		size;
	float		spd;
	float		lifeTime;
	int			hp;
	int			type;

	float		flowTime;
	float		actInterval;
	bool		collided;
public:
	Object();
	//Object(float x, float y, float z, float size)
	//	: pos(Position(x, y, z))
	//	, size(size)
	//	, color(Color(
	//		(rand() % 255 / 255.0),
	//		(rand() % 255 / 255.0),
	//		(rand() % 255 / 255.0), 
	//		(rand() % 255 / 255.0)
	//	))
	//	, dir(Vector2f((rand() % 5) - 2.5, (rand() % 5) - 2.5))
	//	, lifeTime(LIFETIME)
	//	, hp(HP)
	//{
	//}
	Object(
		float x, float y, float z, float size, 
		float r, float g, float b, float a, 
		float lifeTime, int hp, float spd,
		float dirX, float dirY, int type)
		: pos(Position(x, y, z)), size(size)
		, color(Color(r, g, b, a))
		, lifeTime(lifeTime), hp(hp), spd(spd)
		, dir(Vector::Normalize(Vector2f(dirX, dirY))), type(type)
	{
		flowTime = 0.0f;
		if (type == OBJECT_BUILDING) actInterval = 0.5f;
		else actInterval = 0.0f;
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

		flowTime	= other.flowTime;
		actInterval = other.actInterval;
		collided	= other.collided;
	}

	void		update(float elapsedTime);

	Position	getPos();
	float		getPosX() { return pos.x; }
	float		getPosY() { return pos.y; }
	float		getPosZ() { return pos.z; }
	Color		getColor();
	Vector2f	getDir();
	float		getSize();
	bool		getCollided() { return collided; }
	int			getType() { return type; }
	int			getHp() { return hp; }
	float		getActInterval(){ return actInterval; }
	float		getFlowTime() { return flowTime; }

	void		setPos(float x, float y, float z);
	void		setColor(float r, float g, float b, float a);
	void		setSize(float size);
	void		setDir(float x, float y);
	void		setCollided(bool state) { collided = state; }
	void		setFlowTIme(float val) { flowTime = val; }

	void		setHp(int hp) { this->hp = hp; }
	void		addHp(int val) { hp += val; }

	bool		isOut();
	bool		isCollide(const Object &other);
	bool		isLifeTimeEnd();
	bool		isHpZero();

	~Object();
};