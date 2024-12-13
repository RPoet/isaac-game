#include "stdafx.h"
#include "GameScene2.h"
#include "maincharacter.h"
#include "BackGround.h"
#include "SimpleGame.h"
#include "Wall.h"
#include "Door.h"
#include "RPtimer.h"
#include "Duke.h"
#include "Tile.h"
#include "BlackFly.h"
#include "Keyinput.h"
GameScene2::GameScene2()
{
	this->sound = getSoundMGR()->CreateSound("assets/sounds/stage2.mp3");
	this->door = new Door(RIGHT, STAGE3);

	getSceneMGR()->addObj(this->door, 7.4, 0, 0.5f,
		0.7, 1, 1,
		0.f, 0.f, 0.0f, KIND_CLOSED_DOOR, 1000, false, STAGE2);
	
	this->closed_wall = new Wall(1, 1);
	getSceneMGR()->addObj(closed_wall, 8.2f, 0, 0.5f,
		300, 360, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE2);


	getSceneMGR()->addObj(new Door(DOWN, NONE) , -0.f, -4.38f, 0.5f,
		1, 0.7, 1,
		0.f, 0.f, 0.0f, KIND_CLOSED_DOOR, 1000, false, STAGE2);

///»óÇÏ///
	getSceneMGR()->addObj(new Wall(1, 1), 0, 5.0f, 0.5f,
		1600, 250, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE2);

	getSceneMGR()->addObj(new Wall(1, 1), 0, -5.0f, 0.5f,
		1600, 250, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE2);
///////////
	getSceneMGR()->addObj(new Wall(1,1), 8.2f, 2.5f, 0.5f,
		300, 360, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE2);


	getSceneMGR()->addObj(new Wall(1, 1), 8.2f, -2.5f, 0.5f,
		300, 350, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE2);

////////////////////////////////////////////////////////

	getSceneMGR()->addObj(new Wall(1, 1), -8.2f, 0.0f, 0.5f,
		300, 1000, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE2);


	this->enemy[1] = new Duke(mainchars[rand() % 2], this);
	this->enemy[2] = new BlackFly(mainchars[rand() % 2], this);
	this->enemy[3] = new BlackFly(mainchars[rand() % 2], this);
	this->enemy[4] = new BlackFly(mainchars[rand() % 2], this);
	this->enemy[5] = new BlackFly(mainchars[rand() % 2], this);
	this->enemy[6] = new BlackFly(mainchars[rand() % 2], this);
	this->enemy[7] = new BlackFly(mainchars[rand() % 2], this);
}


GameScene2::~GameScene2()
{
}

void GameScene2::fetchImage()
{
}

void GameScene2::init()
{
	getSoundMGR()->PlaySoundW(this->sound, true, 0.9f);
	this->back_ground = BackGround::getInstance();
	
	getSceneMGR()->addObj(this->back_ground, 0, 0.f, 0.5f,
		0, 0, 0,
		0.f, 0.f, 0.0f, KIND_BACKGROUND, 1000, false, STAGE2);

	this->mainchars[0] = MainCharacter::getInstance(0);
	this->mainchars[1] = MainCharacter::getInstance(1);

	for (int i = 0; i < 2; ++i)
	{
		this->mainchars[i]->transform.setLocation(10, -4, 0.5);
		this->mainchars[i]->init();

		int hp;
		this->mainchars[i]->getHealthPoint(hp);
		getSceneMGR()->addObj(this->mainchars[i], -0.f, -2.8, 0.5f,
			1, 1, 1,
			0.f, 0.f, 0.0f, KIND_HERO, hp, false, STAGE2);
		this->setCollisionParams(0, 0, 0);
	}



	this->enemy[0] = new Duke(this->mainchars[rand() %2], this);

	getSceneMGR()->addObj(this->enemy[0],6, 2, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 500, false, STAGE2);


	this->enemy[1] = new Duke(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[1], -6, 2, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 500, false, STAGE2);

	this->enemy[2] = new BlackFly(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[2], -3, -1, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE2);
	this->enemy[3] = new BlackFly(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[3], -3, -2, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE2);
	this->enemy[4] = new BlackFly(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[4], 3, -3, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE2);
	this->enemy[5] = new BlackFly(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[5], 5, -3, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE2);

	this->enemy[6] = new BlackFly(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[6], 5, 3, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE2);

	this->enemy[7] = new BlackFly(this->mainchars[rand() % 2], this);
	getSceneMGR()->addObj(this->enemy[7], 3,0, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 50, false, STAGE2);



	getSceneMGR()->addObj(new Tile(POOP2), -5.f, 0.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);

	getSceneMGR()->addObj(new Tile(POOP2), 1.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


	getSceneMGR()->addObj(new Tile(STONE5), 3.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);



	getSceneMGR()->addObj(new Tile(STONE1), 1.f, -1.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


	getSceneMGR()->addObj(new Tile(STONE2), 5.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


	getSceneMGR()->addObj(new Tile(STONE3), 4.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


	getSceneMGR()->addObj(new Tile(STONE4), 3.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);

	getSceneMGR()->addObj(new Tile(STONE1), 5.f, 1.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


	getSceneMGR()->addObj(new Tile(STONE4), 5.f, -0.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


	getSceneMGR()->addObj(new Tile(STONE4), 5.f, 1.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE2);


}

void GameScene2::update()
{
	this->timer += RP::RpTimer::getDeltaTime();

	if (KeyIO::KeyState('X'))
	{
		numOfEnemy = 0;
	}

	if (this->numOfEnemy == 0)
	{
		this->closed_wall->onDelete();
		this->door->onTrigger();
	}
}

void GameScene2::onCollision(Object *)
{
}

void GameScene2::onTrigger()
{
	this->numOfEnemy--;
}

void GameScene2::exitDo()
{
	this->mainchars[0] = nullptr;
	this->mainchars[1] = nullptr;
	this->back_ground = nullptr;

	getSoundMGR()->stopSounds();
}

void GameScene2::animate()
{
}
