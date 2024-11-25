#include "stdafx.h"
#include <iostream>
#include "scene_clear_manager.h"
#include "SimpleGame.h"
#include "scene_clear.h"
#include "Wall.h"

SceneClearMGR::SceneClearMGR():Object()
{
	for (int i = 0; i < 30; ++i) {
		getSceneMGR()->addObj(new Wall(1, 1), 5.f, 5.8f, 0.5f,
			890, 300, 10,
			0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, CLEAR);
	}
	getSceneMGR()->addObj(new SceneClear(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_BILLBOARD, 1000, false,CLEAR);
}

SceneClearMGR::~SceneClearMGR()
{
}

void SceneClearMGR::init()
{
}

void SceneClearMGR::fetchImage()
{
}

void SceneClearMGR::update()
{
	
}

void SceneClearMGR::onCollision(Object *)
{
}

void SceneClearMGR::onTrigger()
{
}

void SceneClearMGR::animate()
{
}
