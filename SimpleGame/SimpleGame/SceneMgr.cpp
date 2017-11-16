#include "stdafx.h"
#include "SceneMgr.h"

void SceneMgr::initialize()
{		
	// Initialize Renderer
	renderer = new Renderer(WWIDTH, WHEIGHT);
	if (!renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	texBuilding[TEAM_1] = renderer->CreatePngTexture("assets/image/햄스터1.png");
	texBuilding[TEAM_2] = renderer->CreatePngTexture("assets/image/햄스터2.png");
}

void SceneMgr::update(float elapsedTime)
{
	for (auto p = buildList.begin(); p != buildList.end(); ++p)
	{
		p->update(elapsedTime);
		if (p->isHpZero())
		{
			p = buildList.erase(p);
			if (p == buildList.end()) break;
			continue;
		}
		if (p->getFlowTime() > p->getActInterval())
		{
			p->setFlowTIme(0.0f);
			bulletList.emplace_back(
				p->getPosX(), p->getPosY(), p->getTeam(),
				rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
			);
		}
	}
	for (auto p = charList.begin(); p != charList.end(); ++p)
	{
		p->update(elapsedTime);
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
		if (p->isHpZero())
		{
			p = charList.erase(p);
			if (p == charList.end()) break;
			continue;
		}
		if (p->getFlowTime() > p->getActInterval())
		{
			p->setFlowTIme(0.0f);
			arrowList.emplace_back(
				p->getPosX(), p->getPosY(), p->getTeam(),
				rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
			);
		}
	}
	for (auto p = bulletList.begin(); p != bulletList.end(); ++p)
	{
		p->update(elapsedTime);
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
		if (p->isHpZero())
		{
			p = bulletList.erase(p);
			if (p == bulletList.end()) break;
			continue;
		}

		int team = p->getTeam();

		for (auto bp = buildList.begin(); bp != buildList.end(); ++bp)
		{
			if (team != bp->getTeam())
			{
				if (p->isCollide(*bp))
				{
					bp->addHp(-1 * p->getHp());
					std::cout << bp->getTeam() << "팀의 건물이 " << p->getHp()
						<< "데미지를 입었습니다." << std::endl;
					p = bulletList.erase(p);
					if (p == bulletList.end()) goto BULLETRETURN;
				}
			}
		}
		for (auto cp = charList.begin(); cp != charList.end(); ++cp)
		{
			if (team != cp->getTeam())
			{
				if (p->isCollide(*cp))
				{
					cp->addHp(-1 * p->getHp());
					std::cout << cp->getTeam() << "팀의 캐릭터가 " << p->getHp()
						<< "데미지를 입었습니다." << std::endl;
					p = bulletList.erase(p);
					if (p == bulletList.end()) goto BULLETRETURN;
				}
			}
		}
	}
BULLETRETURN:
	for (auto p = arrowList.begin(); p != arrowList.end(); ++p)
	{
		p->update(elapsedTime);
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
		if (p->isHpZero())
		{
			p = arrowList.erase(p);
			if (p == arrowList.end()) break;
			continue;
		}

		int team = p->getTeam();

		for (auto bp = buildList.begin(); bp != buildList.end(); ++bp)
		{
			if (team != bp->getTeam())
			{
				if (p->isCollide(*bp))
				{
					bp->addHp(-1 * p->getHp());
					std::cout << bp->getTeam() << "팀의 건물이 " << p->getHp()
						<< "데미지를 입었습니다." << std::endl;
					p = arrowList.erase(p);
					if (p == arrowList.end()) goto ARROWRETURN;
				}
			}
		}
		for (auto cp = charList.begin(); cp != charList.end(); ++cp)
		{
			if (team != cp->getTeam())
			{
				if (p->isCollide(*cp))
				{
					cp->addHp(-1 * p->getHp());
					std::cout << cp->getTeam() << "팀의 캐릭터가 " << p->getHp()
						<< "데미지를 입었습니다." << std::endl;
					p = arrowList.erase(p);
					if (p == arrowList.end()) goto ARROWRETURN;
				}
			}
		}
	}
ARROWRETURN:

	return;
}

void SceneMgr::render()
{
	for (auto p = buildList.cbegin(); p != buildList.cend(); ++p)
	{
		Position	pos = p->getPos();
		float		size = p->getSize();

		renderer->DrawTexturedRect(pos.x, pos.y, pos.z,
			size * 2, 1.0f, 1.0f, 1.0f, 1.0f,
			texBuilding[p->getTeam()]);
	}
	for (auto p = charList.cbegin(); p != charList.cend(); ++p)
	{
		Position	pos = p->getPos();
		float		size = p->getSize();
		Color		color = p->getColor();

		renderer->DrawSolidRect(
			pos.x, pos.y, pos.z, size * 2,
			color.r, color.g, color.b, color.a);
	}
	for (auto p = bulletList.cbegin(); p != bulletList.cend(); ++p)
	{
		Position	pos = p->getPos();
		float		size = p->getSize();
		Color		color = p->getColor();

		renderer->DrawSolidRect(
			pos.x, pos.y, pos.z, size * 2,
			color.r, color.g, color.b, color.a);
	}
	for (auto p = arrowList.cbegin(); p != arrowList.cend(); ++p)
	{
		Position	pos = p->getPos();
		float		size = p->getSize();
		Color		color = p->getColor();

		renderer->DrawSolidRect(
			pos.x, pos.y, pos.z, size * 2,
			color.r, color.g, color.b, color.a);
	}
}

void SceneMgr::addObj(int x, int y, int type, int team)
{
	switch (type)
	{
	case OBJECT_BUILDING:
		buildList.emplace_back(
			x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team);
		break;
	case OBJECT_CHARACTER:
		charList.emplace_back(
			x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team,
			rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
		);
		break;
	case OBJECT_BULLET:
		bulletList.emplace_back(
			x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team,
			rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
		);
		break;
	case OBJECT_ARROW:
		arrowList.emplace_back(
			x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team,
			rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
		);
		break;
	default:
		break;
	}
}
