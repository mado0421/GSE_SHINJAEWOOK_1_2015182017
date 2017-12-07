#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"

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

enum Snd {
	bg=0,
	fire,
	destroy,

	NumOfSnd
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

	Sound *m_pSound = NULL;
	int m_soundIdx[NumOfSnd];

	float		m_tFlow[NUMOFTIMER];
	int			animationFrame;
public:
	SceneMgr() {}
	~SceneMgr() { 
		delete renderer;
		delete m_pSound;
	}

	/*초기화 함수*/
	void initialize();

	void update(float elapsedTime);

	void render();

	void addObj(int x, int y, int type, int team);
	/*거리 비교해서 특정 오브젝트 찾기
	인자:내 위치, 상대 위치
	반환 값: 거리
	*/
	float getDistance(const Position& myPos, const Position& tarPos);
};