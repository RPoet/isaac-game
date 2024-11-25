#include "stdafx.h"
#include <iostream>
#include "explosion2.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "rptimer.h"
const unsigned int kMaxAnimationFrame = 19;
GLuint Explosion2::effect_explosion_animation[19]{ 0, };
bool Explosion2::image = false;

int Explosion2::sound_num = -1;
Explosion2::Explosion2():Object()
{
	if (!Explosion2::image)	this->fetchImage();

	this->current_frame_image = &this->effect_explosion_animation[0];
	
	getSoundMGR()->PlaySoundW(this->sound_num, false, 2.5f);
}


Explosion2::~Explosion2()
{
}

void Explosion2::fetchImage()
{
	using namespace std;
	cout << "Fetching Tear Success" << endl;
	this->sound_num = getSoundMGR()->CreateSound("assets/sounds/grenade.mp3");

	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/effect/explosion/ex");
		path += to_string(i);
		path += (".png");
		Explosion2::effect_explosion_animation[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}

	Explosion2::image = true;
}

void Explosion2::update()
{
	Explosion2::animate();
}

void Explosion2::onCollision(Object* Gobj)
{
	using namespace std;

}

void Explosion2::onTrigger()
{
}

void Explosion2::animate()
{
	this->animation_timer += RP::RpTimer::getDeltaTime();
	if (this->animation_timer > 0.05)
	{
		if (this->animation_frame_number== kMaxAnimationFrame - 1) {
			this->onDelete();
		}
		this->animation_frame_number = (this->animation_frame_number + 1) % kMaxAnimationFrame;
		this->animation_timer = 0;
	}

	this->current_frame_image = &Explosion2::effect_explosion_animation[this->animation_frame_number];
}
