#include "stdafx.h"
#include <string>
#include <random>

#include "enemy_red.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "rptimer.h"
#include "explosion.h"
#include "explosion2.h"
#include "redtear.h"
const unsigned int kMaxAnimationFrame = 3;
GLuint EnemyHost::animation_idle[3]{ 0, };
bool EnemyHost::image = false;
int EnemyHost::sound_num = -1;
EnemyHost::EnemyHost(Object* other, Object* mgr):Object()
{
	if (!EnemyHost::image)	this->fetchImage();

	this->current_frame_image = &this->animation_idle[0];
	this->target = other;
	this->manager = mgr;
}


EnemyHost::~EnemyHost()
{
	if(this->manager!= nullptr)
	this->manager->onTrigger();
	std::uniform_real_distribution<> urd(-0.5, 0.5);
	std::default_random_engine dre;
	

	float x, y, z;
	this->transform.getTransform(x, y, z);
	getSceneMGR()->addObj(new Explosion(), x+ urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	getSceneMGR()->addObj(new Explosion(), x + urd(dre), y + urd(dre), z + urd(dre), 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);

}

void EnemyHost::fetchImage()
{
	using namespace std;
	cout << "Fetching Tear Success" << endl;
	this->sound_num = getSoundMGR()->CreateSound("assets/sounds/monsterhit1.mp3");
	for (int i = 0; i < kMaxAnimationFrame; ++i) {
		string path("assets/enemy_red/RedHost");
		path += to_string(i);
		path += (".png");
		EnemyHost::animation_idle[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}
	EnemyHost::image = true;
}

void EnemyHost::update()
{
	bool flag = false;
	this->dir = rand() % 4;


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

	float amounts_jump = 0;
	
	if (jump_timer > 1.0f) {
		amounts_jump = 200;
		jump_timer = 0;
	}

	if (targeted_tear_timer > 1.0f) {
		float i = atan2f(ty - y, tx - x);
		getSceneMGR()->addObj(new RedTear(i), x, y, z, 0.2+urd(dre), 0.2 + urd(dre), 0.2 + urd(dre), 3 * cosf(i), 3 * sinf(i), 0, KIND_ENEMY_BULLET, 1, false);
	}
	if (targeted_tear_timer > 1.02f) {
		targeted_tear_timer = 0;
	}

	if (flag == false && dir == 0) {
		this->addForce(5 * -cosf(urd(dre)), 5 * sinf(urd(dre)), amounts_jump);
	}
	else if (flag == false && dir == 1) {
		this->addForce(5 * cosf(urd(dre)), 5 * -sinf(urd(dre)), amounts_jump);
	}
	else if (flag == false && dir == 2) {
		this->addForce(5 * -cosf(urd(dre)), 5 * -sinf(urd(dre)), amounts_jump);
	}
	else if (flag == false && dir == 3) {
		this->addForce(5 * cosf(urd(dre)), 5 * sinf(urd(dre)), amounts_jump);
	}


	this->animate();
	if (flag == true) {
		this->addForce(3 * cosf(this->dir), 3 * sinf(this->dir), amounts_jump);
	}

	Object::update();
}

void EnemyHost::onCollision(Object* Gobj)
{
	using namespace std;
	switch (Gobj->getTag())
	{
	case KIND_BULLET:
	{
		float x, y, z;
		Gobj->transform.getTransform(x, y, z);
		//getSceneMGR()->addObj(new Explosion(), x, y, z, 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
		Gobj->onTrigger();
		int hp;
		Gobj->getHealthPoint(hp);
		this->health_point -= hp;
		if (resound_timer > 1.0f) {
			getSoundMGR()->PlaySoundW(this->sound_num, false, 0.2f);
			resound_timer = 0;
		}
		getSceneMGR()->addObj(new Explosion2(), x, y , z , 0.3, 0.3, 0.3, 0, 0, 0, KIND_EFFECT, 1, false);


	}

		break;
	case KIND_HERO:

	{
		float x, y, z;
		Gobj->transform.getTransform(x, y, z);
		//getSceneMGR()->addObj(new Explosion(), x, y, z, 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
	}
		break;

	}

	Object::onCollision(Gobj);


}

void EnemyHost::onTrigger()
{
}

void EnemyHost::animate()
{
	this->animation_timer += RP::RpTimer::getDeltaTime();
	this->resound_timer += RP::RpTimer::getDeltaTime();
	this->jump_timer += RP::RpTimer::getDeltaTime();
	targeted_tear_timer += RP::RpTimer::getDeltaTime();

	if (this->animation_timer > 0.33)
	{
		this->animation_frame_number = (this->animation_frame_number + 1) % kMaxAnimationFrame;
		this->animation_timer = 0;
	}

	this->current_frame_image = &EnemyHost::animation_idle[this->animation_frame_number];
}
