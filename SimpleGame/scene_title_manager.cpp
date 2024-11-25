#include "stdafx.h"
#include <iostream>
#include "SimpleGame.h"
#include "scene_title_manager.h"
#include "scene_title.h"

SceneTitleMGR::SceneTitleMGR() : Object()
{	
	getSceneMGR()->addObj(new SceneTitle(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_BILLBOARD, 1000, false,TITLE);


	std::cout << "title" << std::endl;

}


SceneTitleMGR::~SceneTitleMGR()
{
}

void SceneTitleMGR::update()
{
	
}

void SceneTitleMGR::onCollision(Object *)
{
}

void SceneTitleMGR::onTrigger()
{
}

void SceneTitleMGR::exitDo()
{
	getSoundMGR()->stopSounds();

}
