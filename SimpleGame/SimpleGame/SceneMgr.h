#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_TEAM 2

class SceneMgr
{
private:
	std::vector<Building> buildList;
	std::vector<Character> charList;
	std::vector<Bullet> bulletList;
	std::vector<Arrow> arrowList;

	Renderer *renderer = NULL;

	GLuint texBuilding[MAX_TEAM];
public:
	SceneMgr() {}
	~SceneMgr() { 
		delete renderer;
	}

	/*�ʱ�ȭ �Լ�*/
	void initialize();

	void update(float elapsedTime);

	void render();

	void addObj(int x, int y, int type, int team);
};