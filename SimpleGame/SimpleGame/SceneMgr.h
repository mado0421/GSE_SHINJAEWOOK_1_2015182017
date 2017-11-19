#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_TEAM 2

#define NUMOFTIMER 2

enum Timer {
	NorthAutoCreate = 0,
	SouthCreateCooldown = 1,

	NorthAutoCreateTime = 5,
	SouthCreateCooldownTime = 7
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

	float		m_tFlow[NUMOFTIMER];
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