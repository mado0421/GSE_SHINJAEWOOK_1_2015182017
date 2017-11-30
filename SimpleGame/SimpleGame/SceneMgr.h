#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_TEAM 2

#define NUMOFTIMER 2
#define HPBARHEIGHT 5.0f

enum Timer {
	NorthAutoCreate = 0,
	SouthCreateCooldown = 1,

	NorthAutoCreateTime = 5,
	SouthCreateCooldownTime = 1
};

class SceneMgr
{
private:
	std::vector<Building> buildList;
	std::vector<Character> charList;
	std::vector<Bullet> bulletList;
	std::vector<Arrow> arrowList;

	Renderer *renderer = NULL;

	GLuint texBuilding[MAX_TEAM];
	GLuint texture[3];
	GLuint backTexture[1];
	GLuint particleTexture[1];
	GLuint characterTexture[1];

	Color teamColor[2] =
	{
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};
	float		m_tFlow[NUMOFTIMER];
	int			animationFrame;
public:
	SceneMgr() {}
	~SceneMgr() { 
		delete renderer;
	}

	/*초기화 함수*/
	void initialize();

	void update(float elapsedTime);

	void render();

	void addObj(int x, int y, int type, int team);
};