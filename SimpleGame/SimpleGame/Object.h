#include "stdafx.h"

class Object
{
private:
	Position	pos;
	Vector2f	dir;
	Color		color;
	float		size;
	float		spd;
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
	{
	}

	void		update();

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

	~Object();
};