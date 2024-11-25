#include "stdafx.h"
#include <iostream>
#include <string>
#include "explosion_tear.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "RPtimer.h"

const unsigned int kMaxAnimationFrame = 16;
GLuint explosion_tear::tear_animation[16]{ 0, };
bool explosion_tear::image = false;

explosion_tear::explosion_tear():Object()
{
	if (!explosion_tear::image)	this->fetchImage();

	this->current_frame_image = &this->tear_animation[0];
}


explosion_tear::~explosion_tear()
{
}

void explosion_tear::fetchImage()
{
	using namespace std;
		
	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/tear/t");
		path += to_string(i);
		path += (".png");
		explosion_tear::tear_animation[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}
	explosion_tear::image = true;
	cout << "Tear anim Fetching Tear Success" << endl;
}

void explosion_tear::update()
{
	this->animate();
}

void explosion_tear::onCollision(Object*)
{
}

void explosion_tear::onTrigger()
{
}

void explosion_tear::animate()
{
	this->animation_timer += RP::RpTimer::getDeltaTime();
	if (this->animation_timer > 0.05)
	{
		if (this->animation_frame_number == 15) {
			float x, y, z;
			this->transform.getTransform(x, y, z);
			this->onDelete();
		}
		this->animation_frame_number = (this->animation_frame_number + int(this->animation_timer/0.05)) % kMaxAnimationFrame;
		this->animation_timer = 0;
	}

	this->current_frame_image = &explosion_tear::tear_animation[this->animation_frame_number];
}
