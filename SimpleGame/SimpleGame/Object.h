#include "stdafx.h"

class Object
{
	Position	pos;
	Vector2f	dir;
	Color		color;
	float		size;
	float		spd;

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

	void		Update();

	Position	GetPos();
	float		GetPosX() { return pos.x; }
	float		GetPosY() { return pos.y; }
	float		GetPosZ() { return pos.z; }
	Color		GetColor();
	Vector2f	GetDir();
	float		GetSize();

	void		SetPos(float x, float y, float z);
	void		SetColor(float r, float g, float b, float a);
	void		SetSize(float size);
	void		SetDir(float x, float y);

	bool		isOut();

	~Object();
};