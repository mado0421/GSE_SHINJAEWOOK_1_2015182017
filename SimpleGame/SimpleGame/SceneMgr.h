#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_TEAM 2

#define NUMOFTIMER 2
#define HPBARHEIGHT 5.0f

enum Timer {
	NorthAutoCreate = 0,
	SouthCreateCooldown = 1,

	NorthAutoCreateTime = 2,
	SouthCreateCooldownTime = 1
};

enum Tex {
	BgImg=0,
	Particle,
	NorthBulid,
	SouthBulid,
	NorthChara,
	SouthChara,

	NumOfTex
};

class SceneMgr
{
private:
	std::vector<Building> buildList;
	std::vector<Character> charList;
	std::vector<Bullet> bulletList;
	std::vector<Arrow> arrowList;

	Renderer *renderer = NULL;

	GLuint texture[Tex::NumOfTex];

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

	/*�ʱ�ȭ �Լ�*/
	void initialize();

	void update(float elapsedTime);

	void render();

	void addObj(int x, int y, int type, int team);
	/*�Ÿ� ���ؼ� Ư�� ������Ʈ ã��
	����:�� ��ġ, ��� ��ġ
	��ȯ ��: �Ÿ�
	*/
	float getDistance(const Position& myPos, const Position& tarPos);
};