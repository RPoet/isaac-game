#include "stdafx.h"
#include <string>
#include "tear.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "RPtimer.h"
#include "explosion.h"
#include "explosion_tear.h"

const unsigned int kMaxAnimationFrame = 16;
GLuint Tear::tear_animation[16]{0,};
bool Tear::resource = false;
int Tear::sound_number[2];

Tear::Tear() : Object()
{
	if (!resource)	this->fetchImage();

	this->current_frame_image = &this->tear_animation[0];
	getSoundMGR()->PlaySoundW(this->sound_number[0], false, 0.5f);
}


Tear::~Tear()
{
}

void Tear::fetchImage()
{
	using namespace std;


	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/tear/t");
		path += to_string(i);
		path += (".png");
		Tear::tear_animation[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}
	this->sound_number[0] = getSoundMGR()->CreateSound("assets/sounds/throwing.mp3");
	this->sound_number[1] = getSoundMGR()->CreateSound("assets/sounds/tearsplat.mp3");
	this->resource = true;
}

void Tear::update()
{
	
	Object::update();
	this->animate();
}

void Tear::onCollision(Object* other)
{
	using namespace std;
	if (other->getTag() == KIND_NOT_PENETRATING_TILE || other->getTag() == KIND_PENETRATING_TILE ) {
		this->onTrigger();
	}

}

void Tear::onTrigger()
{
	this->setCollisionParams(0, 0, 0);
	this->isBombed = true;
	getSoundMGR()->PlaySoundW(this->sound_number[1], false, 0.5f);
}

void Tear::animate()
{
	if (this->isBombed)
	{
		//this->animation_timer += RP::RpTimer::getDeltaTime();
		//if (this->animation_timer > 0.05)
		//{
		//	if (this->animation_frame_number == 15) {
		//		float x, y, z;
		//		this->transform.getTransform(x, y, z);
		//		this->onDelete();
		//	}
		//	this->animation_frame_number = (this->animation_frame_number + 1) % kMaxAnimationFrame;
		//	this->animation_timer = 0;
		//}
		float x, y, z;
		this->transform.getTransform(x, y, z);
		float sx, sy, sz;
		this->transform.getScale(sx, sy, sz);
		getSceneMGR()->addObj(new explosion_tear(), x, y, z, sx, sy, sz, 0, 0, 0, KIND_EFFECT, 1, false);
		this->onDelete();
		float vx, vy, vz;
		this->getVelocity(vx, vy,vz);


	}


	float x, y, z;
	this->transform.getTransform(x, y, z);
	float vx, vy, vz;
	this->getVelocity(vx, vy, vz);

	getRenderer()->DrawParticle(
		x*100.0f, y*100.0f, 0, 5.0f,
		1, 1, 1, 1,
		-vx, -vy,
		getSceneMGR()->snow_texture,
		RP::RpTimer::getPlayTime()
	);
	this->current_frame_image = &Tear::tear_animation[this->animation_frame_number];
}

