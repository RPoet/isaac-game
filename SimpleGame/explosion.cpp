#include "stdafx.h"
#include <iostream>
#include "explosion.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "rptimer.h"
const unsigned int kMaxAnimationFrame = 11;
GLuint Explosion::effect_explosion_animation[11]{ 0, };
bool Explosion::image = false;

int Explosion::sound_num = -1;

Explosion::Explosion():Object()
{
	if (!Explosion::image)	this->fetchImage();

	this->current_frame_image = &this->effect_explosion_animation[0];
	
	getSoundMGR()->PlaySoundW(this->sound_num, false, 0.5f);
}


Explosion::~Explosion()
{
}

void Explosion::fetchImage()
{
	using namespace std;
	cout << "Fetching Tear Success" << endl;
	this->sound_num = getSoundMGR()->CreateSound("assets/sounds/explosion.mp3");
	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/effect/explosion/Explosion");
		path += to_string(i);
		path += (".png");
		Explosion::effect_explosion_animation[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}
	Explosion::image = true;
}

void Explosion::update()
{
	Explosion::animate();
}

void Explosion::onCollision(Object* Gobj)
{
	using namespace std;

}

void Explosion::onTrigger()
{
}

void Explosion::animate()
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

	this->current_frame_image = &Explosion::effect_explosion_animation[this->animation_frame_number];
}
