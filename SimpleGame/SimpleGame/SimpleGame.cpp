/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"


//ObjectManager ObjManager;
//std::vector<Object> ObjList;
SceneMgr sceneMgr;
Renderer *g_Renderer = NULL;
bool		mouseLeftDowned;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

	// ObjList Rendering
	sceneMgr.render(g_Renderer);
	
	glutSwapBuffers();
}

void Idle(void)
{
	sceneMgr.update();

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
		//if (mouseLeftDowned)
		//{
		//	//std::cout << "(x, y) is " << x << ", " << y << std::endl;
		//	std::cout << "created" << std::endl;
		//	ObjList.emplace_back(x - 250, -y + 250, 1, rand() % 10 + 5);
		//	mouseLeftDowned = false;
		//}
		if (mouseLeftDowned)
		{
			// pass
			mouseLeftDowned = false;
		}
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

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

