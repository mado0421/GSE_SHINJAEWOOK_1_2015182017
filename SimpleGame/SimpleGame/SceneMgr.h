#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT 10

class SceneMgr
{
private:
	std::vector<Object> objList;
	std::vector<Object> tmpList;	// update() �� ���ο� ������ ���� �����迭
	Renderer *renderer = NULL;

	int num_character = 0;
	int charId = 0;

	GLuint texBuilding;
public:
	SceneMgr() {}
	~SceneMgr() { 
		objList.clear();
		delete renderer;
	}

	/*ĳ���� ������Ʈ�� ���� ������ ���� �Լ�*/
	void  getNumOfCharacter()
	{
		int num = 0;
		for (auto p = objList.begin(); p != objList.end(); p++)
			if (p->getType() == OBJECT_CHARACTER) num++;
		num_character = num;
	}

	/*�ʱ�ȭ �Լ�*/
	void initialize()
	{
		// Initialize Renderer
		renderer = new Renderer(WWIDTH, WHEIGHT);
		if (!renderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}

		texBuilding = renderer->CreatePngTexture("assets/image/�ܽ���.png");

	}

	void update(float elapsedTime)
	{
		for (auto p = objList.begin(); p != objList.end(); p++)
		{
			p->update(elapsedTime);
			int type = p->getType();

			if (p->isLifeTimeEnd() || p->isHpZero())
			{
				p = objList.erase(p);
				if (p == objList.end()) break;
				continue;
			}

			/*ȭ�� ������ ������ ���*/
			if (type == OBJECT_CHARACTER ||
				type == OBJECT_ARROW ||
				type == OBJECT_BULLET)
			{
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
			}

			/*���͹����� � �ൿ�� �ؾ��ϴ� ���*/
			if (type == OBJECT_BUILDING)
			{
				if (p->getFlowTime() > p->getActInterval())
				{
					p->setFlowTIme(0.0f);
					tmpList.emplace_back(
						p->getPosX(), p->getPosY(), 1, 1.0f,
						1.0f, 0.0f, 0.0f, 1.0f,
						3.0f, 20.0f, 600.0f,
						(rand() % 5) - 2.5, (rand() % 5) - 2.5, OBJECT_BULLET, 0);
				}
			}
			if (type == OBJECT_CHARACTER)
			{
				if (p->getFlowTime() > p->getActInterval())
				{
					p->setFlowTIme(0.0f);
					tmpList.emplace_back(
						p->getPosX(), p->getPosY(), 1, 1.0f,
						0.0f, 1.0f, 0.0f, 1.0f,
						5.0f, 10, 100.0f,
						(rand() % 5) - 2.5, (rand() % 5) - 2.5, OBJECT_ARROW, p->getTeam());
				}
			}

			/*�浹 �˻�*/
			for (auto p2 = objList.begin(); p2 != objList.end(); p2++)
			{
				/*�浹üũ�� ĳ���Ͱ� �������� �ϸ� �ȴ�.
				������ �� �ٸ� ������Ʈ�� ��?
				ĳ������ �� ������ ��?
				������ �� ���ϰԸ� �ϴ°� �� ������ ����.
				*/
				if (type == OBJECT_BUILDING)
				{
					if (p == p2) continue;
					if (p->isCollide(*p2))
					{
						if (p2->getType() == OBJECT_CHARACTER || p2->getType() == OBJECT_ARROW)
						{
							p->addHp(-1 * p2->getHp());
							std::cout << "�浹�� - ����ü��: " << p->getHp() << std::endl;
							p2 = objList.erase(p2);
							if (p2 == objList.end()) break;
							continue;
						}
					}
				}
				if (type == OBJECT_BULLET)
				{
					if (p == p2) continue;
					if (p->isCollide(*p2))
					{
						if (p2->getType() == OBJECT_CHARACTER)
						{
							p2->addHp(-1 * p->getHp());
							std::cout << "�浹��" << std::endl;
							/*���⼭ p�� erase �ع����� for���� �� ���� ������
							�����ϰ� for���� ���������� ����
							�״ϱ� �׳� ü�� 0���� ����� ���� update()���� ������.
							*/
							p->addHp(-1 * p->getHp());
						}
					}
				}
				if (type == OBJECT_ARROW)
				{
					if (p == p2) continue;
					if(p->getTeam() != p2->getTeam())
					{
						if (p->isCollide(*p2))
						{
							if (p2->getType() == OBJECT_CHARACTER)
							{
								p2->addHp(-1 * p->getHp());
								std::cout << "�浹��" << std::endl;
								/*���⼭ p�� erase �ع����� for���� �� ���� ������
								�����ϰ� for���� ���������� ����
								�״ϱ� �׳� ü�� 0���� ����� ���� update()���� ������.
								*/
								p->addHp(-1 * p->getHp());
							}
						}
					}
				}
			}
		}
		for (auto p = tmpList.begin(); p != tmpList.end(); p++)
		{
			objList.emplace_back(*p);
			p = tmpList.erase(p);
			if (p == tmpList.end()) break;
			continue;
		}
		getNumOfCharacter();
	}

	void render()
	{
		for (auto p = objList.begin(); p != objList.end(); p++)
		{
			Position	pos = p->getPos();
			Color		color = p->getColor();

			// size�� 2��� �� ������ ���� ��� ó���� size�� ���������� �����ϰ� �߱� ����.
			// �����Բ��� ����� DrawSolidRect()�� size�� �������� �����ϰ� �ִ�.
			float		size = p->getSize();
			if (p->getType() == OBJECT_BUILDING)
			{
				renderer->DrawTexturedRect(pos.x, pos.y, pos.z,
					size * 2, color.r, color.g, color.b, color.a,
					texBuilding);
			}
			else 
				renderer->DrawSolidRect(
				pos.x, pos.y, pos.z, size * 2, 
				color.r, color.g, color.b, color.a);
		}
	}

	void addObj(int x, int y, int type)
	{
		/*
		��缭:
		float x, float y, float z, float size,
		float r, float g, float b, float a,
		float lifeTime, float hp, float spd,
		float dirX, float dirY, int type
		*/
		switch (type)
		{
		case OBJECT_BUILDING:
			objList.emplace_back(
				x - 250, -y + 250, 1, 25.0f,
				1.0f, 1.0f, 0.0f, 1.0f,
				60.0f, 500.0f, 0.0f,
				(rand() % 5) - 2.5, (rand() % 5) - 2.5, type, 0);
			break;
		case OBJECT_CHARACTER:
			if (num_character < MAX_OBJECTS_COUNT)
			{
				objList.emplace_back(
					x - 250, -y + 250, 1, 5.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					60.0f, 10.0f, 300.0f,
					(rand() % 5) - 2.5, (rand() % 5) - 2.5, type, charId);
				num_character++;
				charId++;
			}
			break;
		case OBJECT_BULLET:
			objList.emplace_back(
				x - 250, -y + 250, 1, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f,
				60.0f, 20.0f, 600.0f,
				(rand() % 5) - 2.5, (rand() % 5) - 2.5, type, 0);
			break;
		case OBJECT_ARROW:
			objList.emplace_back(
				x - 250, -y + 250, 1, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f,
				60.0f, 10.0f, 100.0f,
				(rand() % 5) - 2.5, (rand() % 5) - 2.5, type, 0);
			break;
		default:
			break;
		}
	}

	void clearObj()
	{
		objList.clear();
	}
};