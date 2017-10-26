#include "stdafx.h"

#define LIFETIME 60.0f
#define HP 1.0f
#define SPD 20.0f

class Object
{
private:
	Position	pos;
	Vector2f	dir;
	Color		color;
	float		size;
	float		spd;
	float		lifeTime;
	float			hp;
	bool		collided;
public:
	Object();
	Object(float x, float y, float z, float size)
		: pos(Position(x, y, z))
		, size(size)
		, color(Color(
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0), 
			(rand() % 255 / 255.0)
		))
		, dir(Vector2f((rand() % 5) - 2.5, (rand() % 5) - 2.5))
		, lifeTime(LIFETIME)
		, hp(HP)
	{
	}
	Object(
		float x, float y, float z, float size, 
		float r, float g, float b, float a, 
		float dirX, float dirY)
		: pos(Position(x, y, z))
		, size(size)
		, color(Color(r, g, b, a))
		, dir(Vector2f(dirX, dirY))
		, lifeTime(LIFETIME)
		, hp(HP)
	{
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

	void		setPos(float x, float y, float z);
	void		setColor(float r, float g, float b, float a);
	void		setSize(float size);
	void		setDir(float x, float y);
	void		setCollided(bool state) { collided = state; }

	bool		isOut();
	bool		isCollide(const Object &other);
	bool		isLifeTimeEnd();
	bool		isHpZero();

	~Object();
};