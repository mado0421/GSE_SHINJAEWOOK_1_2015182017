/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"

SceneMgr	*sceneMgr = NULL;
bool		mouseLeftDowned;
float		startTime;
float		curTime;

void RenderScene(void)
{
	startTime = (float)timeGetTime() * 0.001f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// ObjList Rendering
	sceneMgr->render();
	
	curTime = (float)timeGetTime() * 0.001f;

	glutSwapBuffers();
}

void Idle(void)
{
	// elapsedTime�� update()�� ����������.
	sceneMgr->update(curTime - startTime);

//	std::cout << curTime - startTime << std::endl;

	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	/*
		��ũ�� ��ǥ�� �»��(-250, 250)���� ���ϴ�(250, -250)�̹Ƿ�
		x�� 250�� ���ְ� y�� �������Ѽ� 250�� ������� �Ѵ�.
	*/
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseLeftDowned = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (mouseLeftDowned)
		{
			sceneMgr->addObj(x, y, OBJECT_CHARACTER, TEAM_1);
			mouseLeftDowned = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		/*for Test*/
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WWIDTH, WHEIGHT);
	glutCreateWindow("Game Software Engineering KPU");


	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	
	sceneMgr = new SceneMgr();
	sceneMgr->initialize();
	sceneMgr->addObj(1 * (WWIDTH / 4.0), WHEIGHT / 4.0, OBJECT_BUILDING, TEAM_1);
	sceneMgr->addObj(2 * (WWIDTH / 4.0), WHEIGHT / 4.0, OBJECT_BUILDING, TEAM_1);
	sceneMgr->addObj(3 * (WWIDTH / 4.0), WHEIGHT / 4.0, OBJECT_BUILDING, TEAM_1);
	sceneMgr->addObj(1 * (WWIDTH / 4.0), 3 * (WHEIGHT / 4.0), OBJECT_BUILDING, TEAM_2);
	sceneMgr->addObj(2 * (WWIDTH / 4.0), 3 * (WHEIGHT / 4.0), OBJECT_BUILDING, TEAM_2);
	sceneMgr->addObj(3 * (WWIDTH / 4.0), 3 * (WHEIGHT / 4.0), OBJECT_BUILDING, TEAM_2);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete sceneMgr;

    return 0;
}

