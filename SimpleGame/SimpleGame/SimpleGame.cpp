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
DWORD		prevTime;
DWORD		curTime;
float		elapsedTime;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	// ObjList Rendering
	sceneMgr->render();

	curTime = timeGetTime();

	elapsedTime = (curTime - prevTime)*0.001;
	if (elapsedTime > (1.0 / 60))
	{
		// elapsedTime을 update()로 전달해주자.
		sceneMgr->update(elapsedTime);

//		std::cout << elapsedTime << std::endl;

		prevTime = timeGetTime();
	}

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	/*
		스크린 좌표가 좌상단(-250, 250)에서 우하단(250, -250)이므로
		x는 250을 빼주고 y는 반전시켜서 250을 더해줘야 한다.
	*/
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseLeftDowned = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (mouseLeftDowned)
		{
			sceneMgr->addObj(x, y, OBJECT_CHARACTER, TEAM_2);
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

	prevTime = timeGetTime();

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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete sceneMgr;

    return 0;
}

