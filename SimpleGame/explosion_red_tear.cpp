#include "stdafx.h"
#include <iostream>
#include <string>
#include "explosion_red_tear.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "RPtimer.h"

const unsigned int kMaxAnimationFrame = 17;
GLuint explosion_red_tear::tear_animation[17]{ 0, };
bool explosion_red_tear::image = false;

explosion_red_tear::explosion_red_tear(): Object()
{
	if (!explosion_red_tear::image)	this->fetchImage();

	this->current_frame_image = &this->tear_animation[2];
}


explosion_red_tear::~explosion_red_tear()
{
}

void explosion_red_tear::fetchImage()
{
	using namespace std;
		
	//getSoundMGR()->PlaySoundW(this->sound_number, true, 0.05f);

	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/redtear/r");
		path += to_string(i);
		path += (".png");
		explosion_red_tear::tear_animation[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}
	explosion_red_tear::image = true;
	cout << "Tear anim Fetching Tear Success" << endl;
}

void explosion_red_tear::update()
{
	this->animate();
}

void explosion_red_tear::onCollision(Object*)
{
}

void explosion_red_tear::onTrigger()
{
}

void explosion_red_tear::animate()
{
	this->animation_timer += RP::RpTimer::getDeltaTime();
	if (this->animation_timer > 0.05)
	{
		if (this->animation_frame_number == 16) {
			float x, y, z;
			this->transform.getTransform(x, y, z);
			this->onDelete();
		}
		this->animation_frame_number = (this->animation_frame_number + int(this->animation_timer/0.05)) % kMaxAnimationFrame;
		this->animation_timer = 0;
	}

	this->current_frame_image = &explosion_red_tear::tear_animation[this->animation_frame_number];
}
