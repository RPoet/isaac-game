#include "stdafx.h"
#include "scene_credit.h"
#include "SimpleGame.h"
#include "RPtimer.h"
#include "Const.h"
#include "Keyinput.h"

SceneCredit::SceneCredit() : Object()
{
	this->animation = getRenderer()->CreatePngTexture("assets/credit.png");
	this->current_frame_image = &this->animation;
	this->timer = 0;
}

SceneCredit::~SceneCredit()
{
}

void SceneCredit::init()
{
	this->setCollisionParams(0, 0, 0);
	Object::update();
}

void SceneCredit::fetchImage()
{
}

void SceneCredit::update()
{
	this->timer += RP::RpTimer::getDeltaTime();
	this->transform.setScale(1600, 1000, 0);

	float r, g, b, a;
	this->getColor(r, g, b, a);
	if (this->timer >= 1.0f) {
		this->setColor(r, g, b, 1 - (this->timer-1) / 4);
	}
	if (this->timer >= 5.0f)getSceneMGR()->onSceneChange(TITLE);


}


void SceneCredit::onCollision(Object *)
{
}

void SceneCredit::onTrigger()
{
}

void SceneCredit::animate()
{
}
