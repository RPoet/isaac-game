#include "stdafx.h"
#include "scene_gameover.h"
#include "SimpleGame.h"
#include "RPtimer.h"
#include "Const.h"
#include "Keyinput.h"
#include "Wall.h"

SceneGameOver::SceneGameOver() :Object()
{
	this->animation = getRenderer()->CreatePngTexture("assets/gameover.png");
	this->current_frame_image = &this->animation;
	this->timer = 0;
	this->sound = getSoundMGR()->CreateSound("assets/sounds/gameover.mp3");
}


SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::init()
{
	getSoundMGR()->PlaySoundW(this->sound, true, 1.0f);
}

void SceneGameOver::fetchImage()
{
}


void SceneGameOver::update()
{
	this->timer += RP::RpTimer::getDeltaTime();
	this->transform.setScale(1600, 1000, 0);

	float r, g, b, a;
	this->getColor(r, g, b, a);
	if (this->timer >= 1.0f) {
		this->setColor(r, g, b, 1 - (this->timer-1) / 4);
	}

	if (this->timer >= 5.0f) exit(0);
}


void SceneGameOver::onCollision(Object *)
{
}

void SceneGameOver::onTrigger()
{
}

void SceneGameOver::animate()
{
}
