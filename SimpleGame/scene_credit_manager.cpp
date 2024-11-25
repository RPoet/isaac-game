#include "stdafx.h"
#include <iostream>
#include "scene_credit_manager.h"
#include "SimpleGame.h"
#include "scene_credit.h"

SceneCreditMGR::SceneCreditMGR(): Object()
{
	getSceneMGR()->addObj(new SceneCredit(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_BILLBOARD, 1000, false);
}

SceneCreditMGR::~SceneCreditMGR()
{
}

void SceneCreditMGR::update()
{
	
}

void SceneCreditMGR::onCollision(Object *)
{
}

void SceneCreditMGR::onTrigger()
{
}
