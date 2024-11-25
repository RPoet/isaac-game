/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneManager.h"
#include "Keyinput.h"
#include "RPtimer.h"
#include "SimpleGame.h"

extern SceneManager* SceneMGR = nullptr;
extern Renderer* renderer = nullptr;
extern Sound* soundMGR = nullptr;
int dir = NONE;
void RenderScene(void);
void Idle(void);
void MouseInput(int button, int state, int x, int y);
void KeyInput(unsigned char key, int x, int y);
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void SpecialKeyInput(int key, int x, int y);

int main(int argc, char **argv)
{
	std::cout << "Scene in main" << &SceneMGR << std::endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1600, 1000);
	glutCreateWindow("Firmware isaac team");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	RP::RpTimer::init();
	KeyIO::Initialize();

	soundMGR = new Sound();
	renderer = new Renderer(1600, 1000);
	SceneMGR = new SceneManager();
	SceneMGR->init();

	srand(time(nullptr));


	//all callback have each threads.
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop(); // call render scene.
					//this application is managed by this loop if this loop call return; this program will be terminated.

	delete SceneMGR;
	delete soundMGR;
	delete renderer;
    return 0;
}

void RenderScene(void)
{
	using namespace std;
	RP::RpTimer::update();
	while (RP::RpTimer::getDeltaTime() > RP::RpTimer::getTick()) {
		SceneMGR->update();
		
		//std::cout << 1 / RP::RpTimer::getDeltaTime() << endl;
		SceneMGR->renderScene();
		glutSwapBuffers();
	
		RP::RpTimer::resetDeltaTime();
	}
}

void Idle(void)
{

	RenderScene();

}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void KeyDown(unsigned char key, int x, int y)
{
	RenderScene();
}

void KeyUp(unsigned char key, int x, int y)
{
	RenderScene();
}
void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

SceneManager* getSceneMGR() {
	if (nullptr != SceneMGR) {

		return SceneMGR;
	}
	else {
		std::cout << "Scene MGR is null" << std::endl;
	}

}

Renderer * getRenderer()
{
	return renderer;
}

Sound * getSoundMGR()
{
	return soundMGR;
}
