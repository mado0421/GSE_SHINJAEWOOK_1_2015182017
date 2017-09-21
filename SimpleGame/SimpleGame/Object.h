#include "stdafx.h"

class Object
{
	Position	pos;
	Color		color;
	float		size;

public:
	Object();
	Object(float x, float y, float z, float size)
		: pos(Position(x, y, z))
		, size(size)
	{
		Color(
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0)
		);
	}
	Object(Position pos, float size)
		: pos(pos)
		, size(size)
	{
		Color(
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0),
			(rand() % 255 / 255.0)
		);
	}

	Position	GetPos();
	float		GetPosX() { return pos.x; }
	float		GetPosY() { return pos.y; }
	float		GetPosZ() { return pos.z; }
	Color		GetColor();
	float		GetSize();

	void	SetPos(float x, float y, float z);
	void	SetColor(float r, float g, float b, float a);
	void	SetSize(float size);

	~Object();
};