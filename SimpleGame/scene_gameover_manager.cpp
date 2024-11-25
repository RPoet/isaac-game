#include "stdafx.h"
#include <iostream>
#include "scene_gameover_manager.h"
#include "SimpleGame.h"
#include "scene_gameover.h"
#include "Wall.h"

SceneGameOverMGR::SceneGameOverMGR() : Object()
{	
	for (int i = 0; i < 50; ++i) {
		getSceneMGR()->addObj(new Wall(1, 1), 5.f, 5.8f, 0.5f,
			890, 300, 10,
			0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, GAMEOVER);
	}
	getSceneMGR()->addObj(new SceneGameOver(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_BILLBOARD, 1000, false,GAMEOVER);

}


SceneGameOverMGR::~SceneGameOverMGR()
{
}

void SceneGameOverMGR::init()
{
}

void SceneGameOverMGR::fetchImage()
{
}

void SceneGameOverMGR::update()
{
	
}

void SceneGameOverMGR::onCollision(Object *)
{
}

void SceneGameOverMGR::onTrigger()
{
}

void SceneGameOverMGR::animate()
{
}
