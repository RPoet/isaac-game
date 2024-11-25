#include "stdafx.h"
#include <stdlib.h>
#include <random>
#include "BlackFly.h"
#include "SimpleGame.h"
#include "RPtimer.h"
#include "explosion2.h"

const unsigned int kMaxAnimationFrame = 2;
GLuint BlackFly::left[2]{ 0, };
GLuint BlackFly::right[2]{ 0, };
bool BlackFly::image = false;
int BlackFly::sound_num = -1;


BlackFly::BlackFly(Object* other, Object* mgr)
{
	if (!image) fetchImage();


	int animation_frame_number = 0;
	float animation_timer = 0;
	this->current_frame_image = &this->left[0];

	this->target = other;
	this->dir = (rand() % 3)-1;

	this->manager = mgr;
}


BlackFly::~BlackFly()
{
	float x, y, z;
	this->transform.getTransform(x, y, z);
	getSceneMGR()->addObj(new Explosion2(), x+0.03, y, z, 0.25, 0.25, 0.25, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion2(), x-0.03, y, z, 0.25, 0.25, 0.25, 0, 0, 0, KIND_EFFECT, 1, false);
	getSoundMGR()->PlaySoundW(this->sound_num, false, 0.35);

	if(this->manager!=nullptr)this->manager->onTrigger();
}

void BlackFly::fetchImage()
{
	using namespace std;
	cout << "Fetching Tear Success" << endl;
	this->sound_num = getSoundMGR()->CreateSound("assets/sounds/flydie.mp3");
	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/enemy_fly_black/Left/BlackFly");
		path += to_string(i);
		path += (".png");
		BlackFly::left[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}

	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/enemy_fly_black/Right/BlackFly");
		path += to_string(i);
		path += (".png");
		BlackFly::right[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}
	BlackFly::image = true;
}

void BlackFly::init()
{
	this->transform.setScale(0.28, 0.28, 0.28);
	this->setCollisionParams(0.25, 0.3, 0.3);
}

void BlackFly::update()
{
	bool flag = false;
	this->dir = rand() % 4;
	//std::cout << (rand() % 3) - 1 << std::endl;
	float x, y, z;
	this->transform.getTransform(x, y, z);
	float tx, ty, tz;
	target->transform.getTransform(tx, ty, tz);
	
	if ((tx - x) * (tx - x) + (ty - y) * (ty - y) < distance*distance) {
		this->dir = atan2f(ty - y, tx - x);
		flag = true;
		//std::cout << dir << std::endl;
	}
	
	std::uniform_real_distribution<> urd;
	std::default_random_engine dre;

	if (flag == false && dir == 0) {
		this->addForce(25 * -cosf(urd(dre)), 25 * sinf(urd(dre)), 0);
	}
	else if (flag == false && dir == 1) {
		this->addForce(25 * cosf(urd(dre)), 25 * -sinf(urd(dre)), 0);
	}
	else if (flag == false && dir == 2) {
		this->addForce(25 * -cosf(urd(dre)), 25 * -sinf(urd(dre)), 0);
	}
	else if (flag == false && dir == 3) {
		this->addForce(25 * cosf(urd(dre)), 25 * sinf(urd(dre)), 0);
	}
	this->animate();
	if (flag == true) {
		this->addForce(5 * cosf(this->dir), 5 * sinf(this->dir), 0);
	}
	Object::update();
	
}

void BlackFly::onCollision(Object* other)
{


	if (KIND_HERO == other->getTag()) {//씬매니저에서 검사하는 콜리전은 sight 용도

	}

	if (KIND_BULLET == other->getTag()) {//씬매니저에서 검사하는 콜리전은 sight 용도
		other->onTrigger();
		int hp;
		other->getHealthPoint(hp);
		this->health_point -= hp;

	}
	Object::onCollision(other);
	
}

void BlackFly::onTrigger()
{
}

void BlackFly::animate()
{
	this->animation_timer += RP::RpTimer::getDeltaTime();
	if (this->animation_timer > 0.1)
	{
		this->animation_frame_number = (this->animation_frame_number + 1) % kMaxAnimationFrame;
		this->animation_timer = 0;
	}

	float x, y, z;
	this->getVelocity(x, y, z);
	if (x < 0) {
		this->current_frame_image = &BlackFly::left[this->animation_frame_number];
	}
	else if (x > 0) {
		this->current_frame_image = &BlackFly::right[this->animation_frame_number];
	}
}

void BlackFly::wander()
{
}
