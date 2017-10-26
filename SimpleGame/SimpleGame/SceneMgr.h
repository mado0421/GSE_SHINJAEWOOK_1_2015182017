#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT 10

class SceneMgr
{
private:
	std::vector<Object> objList;
	Renderer *renderer = NULL;

public:
	SceneMgr() {}
	~SceneMgr() { 
		objList.clear();
		delete renderer;
	}

	void initialize()
	{
		// Initialize Renderer
		renderer = new Renderer(WWIDTH, WHEIGHT);
		if (!renderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}

		//for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		//{
		//	objList.emplace_back(
		//		rand() % 500 - 250, rand() % 500 - 250, 1, 5.0f,
		//		1.0f, 1.0f, 1.0f, 1.0f,
		//		(rand() % 5) - 2.5, (rand() % 5) - 2.5);
		//}
	}

	void update(float elapsedTime)
	{
		for (auto p = objList.begin(); p != objList.end(); p++)
		{
			p->update(elapsedTime);

			if (p->isLifeTimeEnd() || p->isHpZero())
			{
				p = objList.erase(p);
				if (p == objList.end()) break;
				continue;
			}

			// 화면 밖으로 나가면
			if (p->isOut()) 
			{
				//충돌한 방향에 따라 벡터를 달리 바꿔야 함.
				Position pos = p->getPos();
				Vector2f dir = p->getDir();
				float size = p->getSize();
				if (pos.x + dir.x + size < -(WWIDTH / 2.0) ||
					pos.x + dir.x - size > WWIDTH / 2.0)
					dir.x *= -1;
				if (pos.y + dir.y + size < -(WHEIGHT / 2.0) ||
					pos.y + dir.y - size > WHEIGHT / 2.0)
					dir.y *= -1;
				p->setDir(dir.x, dir.y);
			}

			// 충돌체크는 객체가 하게 한다.
			// 한 객체가 다른 모든 객체와 충돌체크를 매번 하는가?
			// 귀찮으니까 걍 다 돌리자.
			// 다른 객체와 충돌하면
			p->setCollided(false);
			for (auto p2 = objList.begin(); p2 != objList.end(); p2++)
			{
				if (p == p2) continue;
				if (p->isCollide(*p2))
				{
					p->setCollided(true);
				}
			}
		}
	}

	void render()
	{
		for (auto p = objList.begin(); p != objList.end(); p++)
		{
			Position	pos = p->getPos();
			Color		color;

			if (p->getCollided()) color = Color(1.0f, 0.0f, 0.0f, 1.0f);
			else color = p->getColor();

			// size를 2배로 한 이유는 나는 모든 처리를 size를 반지름으로 생각하고 했기 때문.
			// 교수님께서 만드신 DrawSolidRect()는 size를 지름으로 생각하고 있다.
			float		size = p->getSize();
			renderer->DrawSolidRect(
				pos.x, pos.y, pos.z, size * 2, 
				color.r, color.g, color.b, color.a);
		}
	}
	
	void addObj(int x, int y)
	{
		if (objList.size() < MAX_OBJECTS_COUNT)
		{
			/*
				사양서:
				x, y, z, size,
				r, g, b, a,
				dirX, dirY
			*/
			objList.emplace_back(
				x - 250, -y + 250, 1, 15.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				(rand() % 5) - 2.5, (rand() % 5) - 2.5);
		}
	}

	void clearObj()
	{
		objList.clear();
	}


};