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

			// ȭ�� ������ ������
			if (p->isOut()) 
			{
				//�浹�� ���⿡ ���� ���͸� �޸� �ٲ�� ��.
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

			// �浹üũ�� ��ü�� �ϰ� �Ѵ�.
			// �� ��ü�� �ٸ� ��� ��ü�� �浹üũ�� �Ź� �ϴ°�?
			// �������ϱ� �� �� ������.
			// �ٸ� ��ü�� �浹�ϸ�
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

			// size�� 2��� �� ������ ���� ��� ó���� size�� ���������� �����ϰ� �߱� ����.
			// �����Բ��� ����� DrawSolidRect()�� size�� �������� �����ϰ� �ִ�.
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
				��缭:
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