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

	texture[Tex::NorthBulid] = renderer->CreatePngTexture("assets/image/햄스터1.png");
	texture[Tex::SouthBulid] = renderer->CreatePngTexture("assets/image/햄스터2.png");
	texture[Tex::NorthChara] = renderer->CreatePngTexture("assets/image/Char_runnig-Sheet.png");
	texture[Tex::SouthChara] = renderer->CreatePngTexture("assets/image/Char_runnig-Sheet.png");
	texture[Tex::BgImg] = renderer->CreatePngTexture("assets/image/배경텍스처.png");
	texture[Tex::Particle] = renderer->CreatePngTexture("assets/image/파티클텍스처.png");

	animationFrame = 0;

	addObj(1 * (WWIDTH / 4.0), 1.5 * (WHEIGHT / 8.0), OBJECT_BUILDING, TEAM_1);
	addObj(2 * (WWIDTH / 4.0), 1 * (WHEIGHT / 8.0), OBJECT_BUILDING, TEAM_1);
	addObj(3 * (WWIDTH / 4.0), 1.5 * (WHEIGHT / 8.0), OBJECT_BUILDING, TEAM_1);
	addObj(1 * (WWIDTH / 4.0), 6.5 * (WHEIGHT / 8.0), OBJECT_BUILDING, TEAM_2);
	addObj(2 * (WWIDTH / 4.0), 7 * (WHEIGHT / 8.0), OBJECT_BUILDING, TEAM_2);
	addObj(3 * (WWIDTH / 4.0), 6.5 * (WHEIGHT / 8.0), OBJECT_BUILDING, TEAM_2);

	m_pSound = new Sound();
	m_soundIdx[Snd::bg] = m_pSound->CreateSound("./assets/sound/ophelia.mp3");
	m_soundIdx[Snd::fire] = m_pSound->CreateSound("./assets/sound/gun_fire.wav");
	//m_soundIdx[Snd::destroy] = m_pSound->CreateSound("./assets/sound/ophelia.mp3");

	m_pSound->PlaySoundW(m_soundIdx[Snd::bg], true, 0.2f);
}

void SceneMgr::update(float elapsedTime)
{
	if (animationFrame >= 16) animationFrame = 0;
	else animationFrame += 1;

	for (int i = 0; i < NUMOFTIMER; ++i) m_tFlow[i] += elapsedTime;

	if (m_tFlow[Timer::NorthAutoCreate] >= Timer::NorthAutoCreateTime)
	{
		m_tFlow[Timer::NorthAutoCreate] = 0;
		addObj((rand() % WWIDTH), rand() % (WHEIGHT / 2), OBJECT_CHARACTER, TEAM_1, rand()%char_kind::num_char_kind);

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
			int team = p->getTeam();
			float dis = RANBUIL;
			for (auto cp = charList.begin(); cp != charList.end(); ++cp)
			{
				if (team != cp->getTeam())
				{
					if (dis > getDistance(p->getPos(), cp->getPos()))
					{
						dis = getDistance(p->getPos(), cp->getPos());
						p->setTarget(&(*cp));
					}
				}
			}
			if (dis == RANBUIL) p->setTarget(nullptr);
			if (p->getTarget() != nullptr)
			{
				p->setFlowTIme(0.0f);
				bulletList.emplace_back(
					p->getPosX(), p->getPosY(), p->getTeam(),
					p->getTarget()->getPosX() - p->getPosX(), p->getTarget()->getPosY() - p->getPosY()
				);
				m_pSound->PlaySoundW(m_soundIdx[Snd::fire], false, 0.2f);

			}
		}
	}
	for (auto p = charList.begin(); p != charList.end(); ++p)
	{


		int team = p->getTeam();
		int char_kind = p->getKind();
		float dis = SIGHTCHAR;

		//화면 밖으로 나가면
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

		if (char_kind == char_kind::GroundBuild)
		{
			for (auto bp = buildList.begin(); bp != buildList.end(); ++bp)
			{
				if (team != bp->getTeam())
				{
					if (dis > getDistance(p->getPos(), bp->getPos()))
					{
						dis = getDistance(p->getPos(), bp->getPos());
						p->setTarget(&(*bp));
					}
				}
			}
		}
		else if (char_kind == char_kind::GroundAll || char_kind == char_kind::AirAll)
		{
			for (auto bp = buildList.begin(); bp != buildList.end(); ++bp)
			{
				if (team != bp->getTeam())
				{
					if (dis > getDistance(p->getPos(), bp->getPos()))
					{
						dis = getDistance(p->getPos(), bp->getPos());
						p->setTarget(&(*bp));
					}
				}
			}
			for (auto cp = charList.begin(); cp != charList.end(); ++cp)
			{
				if (team != cp->getTeam())
				{
					if (dis > getDistance(p->getPos(), cp->getPos()))
					{
						dis = getDistance(p->getPos(), cp->getPos());
						p->setTarget(&(*cp));
					}
				}
			}
		}

		if (dis == SIGHTCHAR) p->setTarget(nullptr);



		if (p->getFlowTime() > p->getActInterval())
		{
			if (p->getTarget() != nullptr)
			{
				
				if (p->getRange() > getDistance(p->getPos(), p->getTarget()->getPos()))
				{
					p->setFlowTIme(0.0f);
					arrowList.emplace_back(
						p->getPosX(), p->getPosY(), p->getTeam(),
						p->getTarget()->getPosX() - p->getPosX(), p->getTarget()->getPosY() - p->getPosY()
					);
					m_pSound->PlaySoundW(m_soundIdx[Snd::fire], false, 0.2f);
				}
			}
		}

		//for (auto bp = buildList.begin(); bp != buildList.end(); ++bp)
		//{
		//	if (team != bp->getTeam())
		//	{
		//		if (p->isCollide(*bp))
		//		{
		//			bp->addHp(-1 * p->getHp());
		//			std::cout << bp->getTeam() << "팀의 건물이 " << p->getHp()
		//				<< "데미지를 입었습니다." << std::endl;
		//			p = charList.erase(p);
		//			if (p == charList.end()) goto CHARRETURN;
		//		}
		//	}
		//}

		p->update(elapsedTime);
	}
CHARRETURN:
	for (auto p = bulletList.begin(); p != bulletList.end(); ++p)
	{
		p->update(elapsedTime);
		if (p->isHpZero() || p->isOut() || p->isTimeOut())
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
	int			kind;
	Color		color;
	Vector2f	dir;

	renderer->DrawTexturedRect(0, 0, 0,
		WHEIGHT, 1.0f, 1.0f, 1.0f, 1.0f,
		texture[Tex::BgImg], LEV_BACK);

	for (auto p = buildList.cbegin(); p != buildList.cend(); ++p)
	{
		pos = p->getPos();
		size = p->getSize();
		renderer->DrawTexturedRect(pos.x, pos.y, pos.z,
			size * 2, 1.0f, 1.0f, 1.0f, 1.0f,
			texture[Tex::NorthBulid+p->getTeam()], LEV_BUILD);
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
		dir = p->getDir();
		kind = p->getKind();

		//renderer->DrawSolidRect(
		//	pos.x, pos.y, pos.z, size * 2,
		//	color.r, color.g, color.b, color.a, LEV_CHARA);
		//renderer->DrawTexturedRect(pos.x, pos.y, pos.z,
		//	size * 2, 1.0f, 1.0f, 1.0f, 1.0f,
		//	texture[2], LEV_CHARA);
		renderer->DrawTexturedRectSeq(pos.x, pos.y, pos.z,
			size * 3, 1.0f, 1.0f, 1.0f, 1.0f,
			texture[Tex::NorthChara + p->getTeam()], animationFrame/2, (dir.x < 0), 8, 2, LEV_CHARA);

		switch (p->getKind())
		{
		case char_kind::GroundAll:
			renderer->DrawSolidRectGauge(pos.x, pos.y + SIZCHAR + HPBARHEIGHT, pos.z,
				size * 2, HPBARHEIGHT,
				teamColor[p->getTeam()].r,
				teamColor[p->getTeam()].g,
				teamColor[p->getTeam()].b,
				teamColor[p->getTeam()].a,
				((float)p->getHp() / HPCHAR), 0);
			break;

		case char_kind::GroundBuild:
			renderer->DrawSolidRectGauge(pos.x, pos.y + SIZCHAR + HPBARHEIGHT, pos.z,
				size * 2, HPBARHEIGHT,
				teamColor[p->getTeam()].r,
				teamColor[p->getTeam()].g,
				teamColor[p->getTeam()].b,
				teamColor[p->getTeam()].a,
				((float)p->getHp() / HPGIAN), 0);
			break;

		case char_kind::AirAll:
			renderer->DrawSolidRectGauge(pos.x, pos.y + SIZCHAR + HPBARHEIGHT, pos.z,
				size * 2, HPBARHEIGHT,
				teamColor[p->getTeam()].r,
				teamColor[p->getTeam()].g,
				teamColor[p->getTeam()].b,
				teamColor[p->getTeam()].a,
				((float)p->getHp() / HPFLY), 0);
			break;
		default:
			break;
		}


	}
	for (auto p = bulletList.cbegin(); p != bulletList.cend(); ++p)
	{
		pos = p->getPos();
		size = p->getSize();
		color = p->getColor();
		dir = p->getDir();

		renderer->DrawSolidRect(
			pos.x, pos.y, pos.z, size * 2,
			color.r, color.g, color.b, color.a, LEV_BULLE);
		renderer->DrawParticle(pos.x, pos.y, pos.z, SIZPART,
			1, 1, 1, 1, -dir.x * 4, -dir.y * 4,
			texture[Tex::Particle], p->getFlowTime());
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

#ifdef DEBUG
	renderer->DrawTextW(0, 0, GLUT_BITMAP_9_BY_15, 1.0f, 1.0f, 1.0f, "(0, 0)   ");
	renderer->DrawTextW(WWIDTH*0.5, WHEIGHT*0.5, GLUT_BITMAP_9_BY_15, 1.0f, 1.0f, 1.0f, "(0.5,0.5)");
	renderer->DrawTextW(-WWIDTH*0.5, WHEIGHT*0.5, GLUT_BITMAP_9_BY_15, 1.0f, 1.0f, 1.0f, "(-0.5,0.5)");
	renderer->DrawTextW(-WWIDTH*0.5, -WHEIGHT*0.5, GLUT_BITMAP_9_BY_15, 1.0f, 1.0f, 1.0f, "(-0.5,-0.5)");
	renderer->DrawTextW(WWIDTH*0.5, -WHEIGHT*0.5, GLUT_BITMAP_9_BY_15, 1.0f, 1.0f, 1.0f, "(0.5,-0.5)");
#endif
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

void SceneMgr::addObj(int x, int y, int type, int team, int char_kind)
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
					rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0,
					char_kind
				);
			}
		}
		else
		{
			charList.emplace_back(
				x - WWIDTH / 2.0, -y + WHEIGHT / 2.0, team,
				rand() % 100 / 50.0 - 1.0, rand() % 100 / 50.0 - 1.0,
				char_kind
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

