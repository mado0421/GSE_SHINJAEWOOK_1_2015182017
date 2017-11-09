#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT 10

class SceneMgr
{
private:
	std::vector<Object> objList;
	std::vector<Object> tmpList;	// update() 중 새로운 생성을 위한 동적배열
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

	/*캐릭터 오브젝트의 갯수 제한을 위한 함수*/
	void  getNumOfCharacter()
	{
		int num = 0;
		for (auto p = objList.begin(); p != objList.end(); p++)
			if (p->getType() == OBJECT_CHARACTER) num++;
		num_character = num;
	}

	/*초기화 함수*/
	void initialize()
	{
		// Initialize Renderer
		renderer = new Renderer(WWIDTH, WHEIGHT);
		if (!renderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}

		texBuilding = renderer->CreatePngTexture("assets/image/햄스터.png");

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

			/*화면 밖으로 나가는 경우*/
			if (type == OBJECT_CHARACTER ||
				type == OBJECT_ARROW ||
				type == OBJECT_BULLET)
			{
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
			}

			/*인터벌마다 어떤 행동을 해야하는 경우*/
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

			/*충돌 검사*/
			for (auto p2 = objList.begin(); p2 != objList.end(); p2++)
			{
				/*충돌체크는 캐릭터가 빌딩에만 하면 된다.
				빌딩일 때 다른 오브젝트와 비교?
				캐릭터일 때 빌딩과 비교?
				빌딩일 때 비교하게만 하는게 더 적을거 같다.
				*/
				if (type == OBJECT_BUILDING)
				{
					if (p == p2) continue;
					if (p->isCollide(*p2))
					{
						if (p2->getType() == OBJECT_CHARACTER || p2->getType() == OBJECT_ARROW)
						{
							p->addHp(-1 * p2->getHp());
							std::cout << "충돌함 - 현재체력: " << p->getHp() << std::endl;
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
							std::cout << "충돌함" << std::endl;
							/*여기서 p를 erase 해버리면 for문이 두 개라서 터진다
							완전하게 for문이 끝나버리지 않음
							그니까 그냥 체력 0으로 만들고 다음 update()에서 없에자.
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
								std::cout << "충돌함" << std::endl;
								/*여기서 p를 erase 해버리면 for문이 두 개라서 터진다
								완전하게 for문이 끝나버리지 않음
								그니까 그냥 체력 0으로 만들고 다음 update()에서 없에자.
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

			// size를 2배로 한 이유는 나는 모든 처리를 size를 반지름으로 생각하고 했기 때문.
			// 교수님께서 만드신 DrawSolidRect()는 size를 지름으로 생각하고 있다.
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
		사양서:
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