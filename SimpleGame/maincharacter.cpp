#include "stdafx.h"
#include "maincharacter.h"
#include "Keyinput.h"
#include "Renderer.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "rptimer.h"
#include "explosion2.h"


const unsigned int kMaxAnimationFrame = 3;

GLuint MainCharacter::down_animation[3]{0,};
GLuint MainCharacter::right_animation[3]{0,};
GLuint MainCharacter::left_animation[3]{0,};
GLuint MainCharacter::up_animation[3]{0,};

int MainCharacter::sound_number;
int MainCharacter::sound_hit;


bool MainCharacter::image = false;
MainCharacter* MainCharacter::instances[2] = { nullptr, nullptr };

MainCharacter::MainCharacter(int playerIndex)
	: Object()
	, playerIndex(playerIndex)
{
	if (!MainCharacter::image)
	{
		fetchImage();
	}

	current_frame_image = &down_animation[1];
	
	for (int i = 0; i < 10; ++i)
	{
		hp[i] = new Heart();
	}
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::update()
{
	this->animate();
	this->definedKeyAct();
	this->prev_transform = this->transform;
	Object::update();
	this->updateCollisionArea();


	for (int i = 0; i < 10; ++i) {
		hp[i]->heal();
	}
	if (health_point < 10) {
		for (int i = this->health_point; i < 10; ++i) {
			this->hp[i]->modifyHeart();
		}
	}

	if (health_point <= 0) {
		getSceneMGR()->onSceneChange(GAMEOVER);
	}
}


void MainCharacter::onCollision(Object* other)
{
	using namespace std;
	if (other->getTag() == KIND_BUILDING) {
		//cout << "col with building" << endl;
	}

	if (other->getTag() == KIND_ENEMY) {
		if (this->overwhelming_timer > 1.0f) {
			float x, y, z;
			this->transform.getTransform(x, y, z);
			this->overwhelming_timer = 0;
			getSoundMGR()->PlaySoundW(this->sound_hit, false, 1.0f);
			getSceneMGR()->addObj(new Explosion2(), x, y, z, 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
			this->health_point--;
		}
	}

	if (other->getTag() == KIND_ENEMY_BULLET) {
		if (this->overwhelming_timer > 1.0f) {
			float x, y, z;
			this->transform.getTransform(x, y, z);
			this->overwhelming_timer = 0;
			getSoundMGR()->PlaySoundW(this->sound_hit, false, 1.0f);
			getSceneMGR()->addObj(new Explosion2(), x, y, z, 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);
			this->health_point--;
		}

	}

	if (other->getTag() == KIND_CLOSED_DOOR) {
		float x, y, z;
		other->transform.getTransform(x, y, z);
		
		this->transform = this->prev_transform;
		this->setVelocityZeroXY();
	}

	Object::onCollision(other);
}

void MainCharacter::updateCollisionArea()
{
	float sx, sy, sz;
	this->transform.getScale(sx, sy, sz);

	float x, y, z;
	this->transform.getTransform(x, y, z);
	this->collision_area_rect.max_x = x + sx/3;
	this->collision_area_rect.min_x = x - sx/3;
	this->collision_area_rect.max_y = y + (sy/2)-0.4;
	this->collision_area_rect.min_y = y - (sy/2)-0.4;

	this->collision_area_box.max_x = x + sx / 3;
	this->collision_area_box.max_y = y + (sy / 2) -0.4;
	this->collision_area_box.max_z = z + sz/2;

	this->collision_area_box.min_x = x - sx / 3;
	this->collision_area_box.min_y = y - (sy / 2) - 0.4;
	this->collision_area_box.min_z = z - sz/2;
}

void MainCharacter::definedKeyAct()
{
	constexpr static int definedKeys[2][8] = {
		{
			VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_SPACE, VK_RETURN, VK_ESCAPE, 'P',
		},
		{
			'D', 'A', 'W', 'S' , 'U'/*SPACE*/, 'I'/*RETURN*/, 'O'/*ESCAPE*/, 'T',
		}
	};

	this->timer += RP::RpTimer::getDeltaTime();
	this->overwhelming_timer+= RP::RpTimer::getDeltaTime();
	float Fx = 0;
	float Fy = 0;
	float Fz = 0;
	float amounts = 4;

	if (KeyIO::KeyState(definedKeys[playerIndex][0])) {
		Fx = amounts;
		this->dir = RIGHT;
	}
	if (KeyIO::KeyState(definedKeys[playerIndex][1])) {
		Fx = -amounts;
		this->dir = LEFT;
	}
	if (KeyIO::KeyState(definedKeys[playerIndex][2])) {
		Fy = amounts;
		this->dir = UP;
	}
	if (KeyIO::KeyState(definedKeys[playerIndex][3]))
	{
		Fy = -amounts;
		this->dir = DOWN;
	}
	if (KeyIO::KeyState(definedKeys[playerIndex][4]) && timer > 0.3f)
	{
		SceneManager* curScene = getSceneMGR();		
		if (curScene)
		{
			curScene->shoot(this->dir, *this);
		}	
		timer = 0;
	}

	if (KeyIO::KeyState(definedKeys[playerIndex][5]))// 점프
	{
		Fz = 30;
	}

	if (KeyIO::KeyState(definedKeys[playerIndex][6]))// 종료
	{
		exit(0);
	}

	if (KeyIO::KeyState(definedKeys[playerIndex][7]))// 무적
	{
		std::cout << "무적 동작" << std::endl;
		setHeathPoint(9999999999);

		if (playerIndex != 0)
		{
			setColor(1, 1, 0, 1);
		}
		else
		{
			setColor(0, 1, 1, 1);
		}
	}

	this->addForce(Fx, Fy, Fz);	
}

void MainCharacter::init()
{
	for (int i = 0; i < 10; ++i)
		getSceneMGR()->addObj(this->hp[i], -770+ i * 25, 450 - ( this->playerIndex * 900 ), 0.5, 1, 1, 1, 0, 0, 0, KIND_UI, 1, false);


	if (playerIndex != 0)
	{
		setColor(1, 0, 0, 1);
	}
	else
	{
		setColor(1, 1, 1, 1);
	}
}

MainCharacter * MainCharacter::getInstance(int index)
{
	if (index < 2)
	{
		if (instances[index])
		{
			return instances[index];
		}
		else
		{
			instances[index] = new MainCharacter(index);
		}

		return instances[index];
	}

	return nullptr;
}

void MainCharacter::animate()
{
	using namespace std;
	//1sec 3frame

	this->animation_timer += RP::RpTimer::getDeltaTime();
	if (this->animation_timer > 0.1)
	{
		this->animation_frame_number = (this->animation_frame_number + 1) % kMaxAnimationFrame;
		this->animation_timer = 0;
	}

	float vx, vy, vz;
	this->getVelocity(vx, vy, vz);
	//cout << vx << " " << vy << " " << vz << endl;
	if (0 == static_cast<int>(sqrtf(vx*vx +  vy * vy +  vz * vz))) {
		this->animation_frame_number = 1;
	}


	switch (this->dir) {
	case DOWN:
		this->current_frame_image = &MainCharacter::down_animation[this->animation_frame_number];
		break;
	case UP:
		this->current_frame_image = &MainCharacter::up_animation[this->animation_frame_number];
		break;
	case RIGHT:
		this->current_frame_image = &MainCharacter::right_animation[this->animation_frame_number];
		break;
	case LEFT:
		this->current_frame_image = &MainCharacter::left_animation[this->animation_frame_number];
		break;
	}
}

void MainCharacter::fetchImage() {

	
	this->sound_hit = getSoundMGR()->CreateSound("assets/sounds/isaachit.mp3");
	MainCharacter::down_animation[0] = getRenderer()->CreatePngTexture("assets/main_char/isaac_01.png");
	MainCharacter::down_animation[1] = getRenderer()->CreatePngTexture("assets/main_char/isaac_02.png");
	MainCharacter::down_animation[2] = getRenderer()->CreatePngTexture("assets/main_char/isaac_03.png");

	MainCharacter::left_animation[0] = getRenderer()->CreatePngTexture("assets/main_char/isaac_04.png");
	MainCharacter::left_animation[1] = getRenderer()->CreatePngTexture("assets/main_char/isaac_05.png");
	MainCharacter::left_animation[2] = getRenderer()->CreatePngTexture("assets/main_char/isaac_06.png");

	MainCharacter::right_animation[0] = getRenderer()->CreatePngTexture("assets/main_char/isaac_07.png");
	MainCharacter::right_animation[1] = getRenderer()->CreatePngTexture("assets/main_char/isaac_08.png");
	MainCharacter::right_animation[2] = getRenderer()->CreatePngTexture("assets/main_char/isaac_09.png");

	MainCharacter::up_animation[0] = getRenderer()->CreatePngTexture("assets/main_char/isaac_10.png");
	MainCharacter::up_animation[1] = getRenderer()->CreatePngTexture("assets/main_char/isaac_11.png");
	MainCharacter::up_animation[2] = getRenderer()->CreatePngTexture("assets/main_char/isaac_12.png");
	MainCharacter::image = true;
}