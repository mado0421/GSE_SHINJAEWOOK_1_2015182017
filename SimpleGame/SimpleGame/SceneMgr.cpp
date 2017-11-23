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

	m_tFlow[NorthAutoCreate] = NorthAutoCreateTime;
	m_tFlow[SouthCreateCooldown] = SouthCreateCooldownTime;

	texBuilding[TEAM_1] = renderer->CreatePngTexture("assets/image/�ܽ���1.png");
	texBuilding[TEAM_2] = renderer->CreatePngTexture("assets/image/�ܽ���2.png");
	texture[0] = renderer->CreatePngTexture("assets/image/�ܽ���1.png");
	texture[1] = renderer->CreatePngTexture("assets/image/�ܽ���2.png");
	texture[2] = renderer->CreatePngTexture("assets/image/�عٶ�⾾.png");


	addObj(1 * (WWIDTH / 4.0), WHEIGHT / 4.0, OBJECT_BUILDING, TEAM_1);
	addObj(2 * (WWIDTH / 4.0), WHEIGHT / 4.0, OBJECT_BUILDING, TEAM_1);
	addObj(3 * (WWIDTH / 4.0), WHEIGHT / 4.0, OBJECT_BUILDING, TEAM_1);
	addObj(1 * (WWIDTH / 4.0), 3 * (WHEIGHT / 4.0), OBJECT_BUILDING, TEAM_2);
	addObj(2 * (WWIDTH / 4.0), 3 * (WHEIGHT / 4.0), OBJECT_BUILDING, TEAM_2);
	addObj(3 * (WWIDTH / 4.0), 3 * (WHEIGHT / 4.0), OBJECT_BUILDING, TEAM_2);
}

void SceneMgr::update(float elapsedTime)
{
	for (int i = 0; i < NUMOFTIMER; ++i) m_tFlow[i] += elapsedTime;

	if (m_tFlow[Timer::NorthAutoCreate] >= Timer::NorthAutoCreateTime)
	{
		m_tFlow[Timer::NorthAutoCreate] = 0;
		addObj(1 * (WWIDTH / 4.0), rand() % (WHEIGHT / 2), OBJECT_CHARACTER, TEAM_1);

	}

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
		//ȭ�� ������ ������
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

		int team = p->getTeam();

		for (auto bp = buildList.begin(); bp != buildList.end(); ++bp)
		{
			if (team != bp->getTeam())
			{
				if (p->isCollide(*bp))
				{
					bp->addHp(-1 * p->getHp());
					std::cout << bp->getTeam() << "���� �ǹ��� " << p->getHp()
						<< "�������� �Ծ����ϴ�." << std::endl;
					p = charList.erase(p);
					if (p == charList.end()) goto CHARRETURN;
				}
			}
		}
	}
CHARRETURN:
	for (auto p = bulletList.begin(); p != bulletList.end(); ++p)
	{
		p->update(elapsedTime);
		if (p->isHpZero() || p->isOut())
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
					std::cout << bp->getTeam() << "���� �ǹ��� " << p->getHp()
						<< "�������� �Ծ����ϴ�." << std::endl;
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
					std::cout << cp->getTeam() << "���� ĳ���Ͱ� " << p->getHp()
						<< "�������� �Ծ����ϴ�." << std::endl;
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
		if (p->isHpZero()|| p->isOut())
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
					std::cout << bp->getTeam() << "���� �ǹ��� " << p->getHp()
						<< "�������� �Ծ����ϴ�." << std::endl;
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
					std::cout << cp->getTeam() << "���� ĳ���Ͱ� " << p->getHp()
						<< "�������� �Ծ����ϴ�." << std::endl;
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
	Position	pos;
	float		size;
	Color		color;
	for (auto p = buildList.cbegin(); p != buildList.cend(); ++p)
	{
		pos = p->getPos();
		size = p->getSize();
		renderer->DrawTexturedRect(pos.x, pos.y, pos.z,
			size * 2, 1.0f, 1.0f, 1.0f, 1.0f,
			texBuilding[p->getTeam()], LEV_BUILD);
		renderer->DrawSolidRectGauge(pos.x, pos.y + SIZBUIL + HPBARHEIGHT, pos.z,
			SIZBUIL*2, HPBARHEIGHT,
			teamColor[p->getTeam()].r,
			teamColor[p->getTeam()].g, 
			teamColor[p->getTeam()].b, 
			teamColor[p->getTeam()].a,
			((float)p->getHp()/HPBUIL), 0);

	}
	for (auto p = charList.cbegin(); p != charList.cend(); ++p)
	{
		pos = p->getPos();
		size = p->getSize();
		color = p->getColor();

		//renderer->DrawSolidRect(
		//	pos.x, pos.y, pos.z, size * 2,
		//	color.r, color.g, color.b, color.a, LEV_CHARA);
		renderer->DrawTexturedRect(pos.x, pos.y, pos.z,
			size * 2, 1.0f, 1.0f, 1.0f, 1.0f,
			texture[2], LEV_CHARA);
		renderer->DrawSolidRectGauge(pos.x, pos.y + SIZCHAR + HPBARHEIGHT, pos.z,
			SIZCHAR * 2, HPBARHEIGHT,
			teamColor[p->getTeam()].r,
			teamColor[p->getTeam()].g,
			teamColor[p->getTeam()].b,
			teamColor[p->getTeam()].a,
			((float)p->getHp() / HPCHAR), 0);
	}
	for (auto p = bulletList.cbegin(); p != bulletList.cend(); ++p)
	{
		pos = p->getPos();
		size = p->getSize();
		color = p->getColor();

		renderer->DrawSolidRect(
			pos.x, pos.y, pos.z, size * 2,
			color.r, color.g, color.b, color.a, LEV_BULLE);
	}
	for (auto p = arrowList.cbegin(); p != arrowList.cend(); ++p)
	{
		pos = p->getPos();
		size = p->getSize();
		color = p->getColor();

		renderer->DrawSolidRect(
			pos.x, pos.y, pos.z, size * 2,
			color.r, color.g, color.b, color.a, LEV_ARROW);
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
		if (team == TEAM_2)
		{
			if (y >= 400.0 && m_tFlow[Timer::SouthCreateCooldown] >= Timer::SouthCreateCooldownTime)
			{
				m_tFlow[Timer::SouthCreateCooldown] = 0;
				charList.emplace_back(
					x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team,
					rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
				);
			}
		}
		else
		{
			charList.emplace_back(
				x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team,
				rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0
			);
		}
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
