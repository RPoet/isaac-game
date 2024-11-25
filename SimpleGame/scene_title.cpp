#include "stdafx.h"
#include "scene_title.h"
#include "SimpleGame.h"
#include "RPtimer.h"
#include "Keyinput.h"
#include "Const.h"
#include "Sound.h"

SceneTitle::SceneTitle() : Object()
{
	this->animation[0] = getRenderer()->CreatePngTexture("assets/title.png");
	this->animation[1] = getRenderer()->CreatePngTexture("assets/title1.png");
	this->current_frame_image = &this->animation[0];
	this->timer = 0;

	this->sound_slot = getSoundMGR()->CreateSound("assets/sounds/bgm1.mp3");
}


SceneTitle::~SceneTitle()
{
}

void SceneTitle::init()
{
	this->setCollisionParams(0, 0, 0);
	Object::update();
	getSoundMGR()->PlaySoundW(this->sound_slot, true, 1);
}


void SceneTitle::fetchImage()
{
}


void SceneTitle::update()
{
	//std::cout << "hi" << std::endl;
	this->transform.setScale(1600, 1000, 0);

	if (!flag) 	this->timer += RP::RpTimer::getDeltaTime();	
	else		this->timer -= RP::RpTimer::getDeltaTime();

	if (this->timer >=2.0f) 	this->timer = 2;
	
	if (this->timer < -0.1f) getSceneMGR()->onSceneChange(STAGE1);

	float r, g, b, a;
	this->getColor(r, g, b, a);
	this->setColor(r,g,b,0+this->timer/2);


	this->animation_timer += RP::RpTimer::getDeltaTime();

	if (this->animation_timer > 0.5f) {
		this->animation_frame_number = (this->animation_frame_number + 1) % 2;
		this->animation_timer = 0;
		this->current_frame_image = &this->animation[this->animation_frame_number];
	}

	
	if (KeyIO::getAnyKeyDown()) {
		flag = true;
	}



}


void SceneTitle::onCollision(Object *)
{
}

void SceneTitle::onTrigger()
{
}

void SceneTitle::exitDo()
{
	getSoundMGR()->DeleteSound(this->sound_slot);
}

void SceneTitle::animate()
{
}
