#include "stdafx.h"
#include "GameScene1.h"
#include "maincharacter.h"
#include "BackGround.h"
#include "SimpleGame.h"
#include "Wall.h"
#include "Door.h"
#include "RPtimer.h"
#include "enemy_red.h"
#include "BlackFly.h"
#include "Tile.h"

GameScene1::GameScene1()
{
	this->sound = getSoundMGR()->CreateSound("assets/sounds/fisrtbgm.mp3");
	this->mainchar = MainCharacter::getInstance();
	this->back_ground = BackGround::getInstance();


	getSceneMGR()->addObj(this->back_ground, 0, 0.f, 0.0f,
		0, 0, 0,
		0.f, 0.f, 0.0f, KIND_BACKGROUND, 1000, false, STAGE1);


	getSceneMGR()->addObj(new Wall(1,1), 8.2f, 0.0f, 0.5f,
		300, 1000, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE1);

	getSceneMGR()->addObj(new Wall(1, 1), -8.2f, 0.0f, 0.5f,
		300, 1000, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE1);


	getSceneMGR()->addObj(new Wall(1, 1), 0.f, -5.2f, 0.5f,
		1600, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE1);

	getSceneMGR()->addObj(new Wall(1, 1), 0.f, -5.2f, 0.5f,
		1000, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE1);

	getSceneMGR()->addObj(new Wall(1, 1), -5.f, 5.8f, 0.5f,
		890, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE1);

	getSceneMGR()->addObj(new Wall(1, 1), 5.f, 5.8f, 0.5f,
		890, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE1);


	this->door = new Door(UP, STAGE2);
	getSceneMGR()->addObj(this->door, -0.f, 4.38f, 0.5f,
		1, 0.7, 1,
		0.f, 0.f, 0.0f, KIND_CLOSED_DOOR, 1000, false, STAGE1);




	getSceneMGR()->addObj(this->mainchar, 0.f, -2.8f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_HERO, 10, false, STAGE1);


	this->enemy[0] = new EnemyHost(mainchar, this);

	getSceneMGR()->addObj(this->enemy[0], 4.f, 3.f, 0.5f,
			1, 1, 1,
			0.f,0.f,0.0f, KIND_ENEMY,250, false, STAGE1);	


	this->enemy[1] = new EnemyHost(mainchar, this);

	getSceneMGR()->addObj(this->enemy[1], -4.f, 3.f, 0.5f,
		0.7, 0.7, 0.7,
		0.f, 0.f, 0.0f, KIND_ENEMY, 250, false, STAGE1);


	this->enemy[2] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[2], 4.f, -3.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);



	this->enemy[3] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[3], 2.f, 3.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);



	this->enemy[4] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[4], 3.f, 4.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);

	this->enemy[5] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[5], 3.f, 2.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);

	this->enemy[6] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[6], 2.f, 0, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);

	this->enemy[7] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[7], 0.f,- 3.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);

	this->enemy[8] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[8], 3.f, 2.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);

	this->enemy[9] = new BlackFly(mainchar, this);

	getSceneMGR()->addObj(this->enemy[9], -3.f, -3.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE1);

}


GameScene1::~GameScene1()
{
}

void GameScene1::fetchImage()
{
}

void GameScene1::init()
{
	getSceneMGR()->addObj(new Tile(POOP1), -3.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);


	getSceneMGR()->addObj(new Tile(POOP2), -2.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);



	getSceneMGR()->addObj(new Tile(POOP3), -1.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);

	getSceneMGR()->addObj(new Tile(POOP4), 0.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);


	getSceneMGR()->addObj(new Tile(POOP5), 1.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);



	getSceneMGR()->addObj(new Tile(STONE1), 2.f, -0.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);


	getSceneMGR()->addObj(new Tile(STONE2), 2.f, -1.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);


	getSceneMGR()->addObj(new Tile(STONE3), 3.f, -3.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);


	getSceneMGR()->addObj(new Tile(STONE4), 5.f, -3.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE1);


	getSoundMGR()->PlaySoundW(this->sound, true, 0.8f);
}

void GameScene1::update()
{
	this->timer += RP::RpTimer::getDeltaTime();


	if (numOfEnemy == 0) this->door->onTrigger();
}

void GameScene1::onCollision(Object *)
{
}

void GameScene1::onTrigger()
{
	--this->numOfEnemy;
}

void GameScene1::exitDo()
{
	this->mainchar = nullptr;
	getSoundMGR()->stopSounds();
}

void GameScene1::animate()
{
}
