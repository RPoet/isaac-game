#include "stdafx.h"
#include "GameScene3.h"
#include "maincharacter.h"
#include "BackGround.h"
#include "SimpleGame.h"
#include "Wall.h"
#include "Door.h"
#include "RPtimer.h"
#include "FinalBoss.h"
#include "Duke.h"
#include "Tile.h"
#include "Keyinput.h"

GameScene3::GameScene3()
{
	this->sound = getSoundMGR()->CreateSound("assets/sounds/stage3.mp3");
}


GameScene3::~GameScene3()
{
}

void GameScene3::fetchImage()
{
}

void GameScene3::init()
{
	getSoundMGR()->PlaySoundW(this->sound, true, 1.0f);
	this->back_ground = BackGround::getInstance();

	getSceneMGR()->addObj(this->back_ground, 0, 0.f, 0.5f,
		0, 0, 0,
		0.f, 0.f, 0.0f, KIND_BACKGROUND, 1000, false, STAGE3);



	this->mainchars[0] = MainCharacter::getInstance(0);
	this->mainchars[1] = MainCharacter::getInstance(1);


	for (int i = 0; i < 2; ++i)
	{
		int hp;
		this->mainchars[i]->getHealthPoint(hp);
		getSceneMGR()->addObj(mainchars[i], -6.2f, 0.2f, 0.5f,
			1, 1, 1,
			0.f, 0.f, 0.0f, KIND_HERO, hp, false, STAGE3);
		mainchars[i]->prev_transform.setLocation(-6.2f, 0.2f, 0.5f);
		mainchars[i]->init();
	}

	getSceneMGR()->addObj(new Door(LEFT, NONE), -7.4, 0, 0.5f,
		0.7, 1, 1,
		0.f, 0.f, 0.0f, KIND_CLOSED_DOOR, 1000, false, STAGE3);



	getSceneMGR()->addObj(new Wall(1, 1), 8.2f, 0.0f, 0.5f,
		300, 1000, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), -8.2f, 0.0f, 0.5f,
		300, 1000, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);


	getSceneMGR()->addObj(new Wall(1, 1), 0.f, -5.2f, 0.5f,
		1600, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), 0.f, -5.2f, 0.5f,
		1000, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), -5.f, 5.8f, 0.5f,
		890, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), 5.f, 5.8f, 0.5f,
		890, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);



	/**********************************************/

	getSceneMGR()->addObj(new Wall(1, 1), 0.f, -5.2f, 0.5f,
		1600, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), 0.f, -5.2f, 0.5f,
		1000, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), -5.f, 5.8f, 0.5f,
		890, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	getSceneMGR()->addObj(new Wall(1, 1), 5.f, 5.8f, 0.5f,
		890, 300, 10,
		0.f, 0.f, 0.0f, KIND_DEBUGGER_COLLISION, 1000, false, STAGE3);

	//씬이 배열로 이뤄져 있어서 충돌 중 변환이 일어나면 다음 씬의 해당 오브젝트 번호부터 검사를하게 되는데, 이 배열이 비어있으면 빈공간 참조로 에러.
	//지금 구조상 해결이 어렵다고 생각 함. 따라서 더미 Wall을 집어넣었다.
	/**********************************************************************/

	this->door = new Door(UP, CLEAR);
	getSceneMGR()->addObj(this->door, -0.f, 4.38f, 0.5f,
		1, 0.7, 1,
		0.f, 0.f, 0.0f, KIND_CLOSED_DOOR, 1000, false, STAGE3);

////////////////////////////////////ENEMY///////////////////////////////////////////////////////


	this->enemy[0] = new FinalBoss(this->mainchars[ rand() % 2], this);

	getSceneMGR()->addObj(this->enemy[0], -5, -3, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 700, false, STAGE3);


	this->enemy[1] = new Duke(this->mainchars[rand() % 2], this);

	getSceneMGR()->addObj(this->enemy[1], -2, 3, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 500, false, STAGE3);


	getSceneMGR()->addObj(new Tile(POOP2), -5.f, 2.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);

	getSceneMGR()->addObj(new Tile(POOP2), 2.f, 3.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);


	getSceneMGR()->addObj(new Tile(STONE5), 2.f, 2.4f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);



	getSceneMGR()->addObj(new Tile(STONE1), 4.f, -1.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);


	getSceneMGR()->addObj(new Tile(STONE2), 3.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);


	getSceneMGR()->addObj(new Tile(STONE5), 1.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);


	getSceneMGR()->addObj(new Tile(STONE5), 2.f, -2.f, 0.5f,
		0.5, 0.5, 0.5,
		0.f, 0.f, 0.0f, KIND_NOT_PENETRATING_TILE, 3, false, STAGE3);






}

void GameScene3::update()
{
	this->timer += RP::RpTimer::getDeltaTime();

	if (KeyIO::KeyState('X'))
	{
		numOfEnemy = 0;
	}

	if (numOfEnemy == 0) {
		this->door->onTrigger();
	}
}

void GameScene3::onCollision(Object *)
{
}

void GameScene3::onTrigger()
{
	this->numOfEnemy--;
}

void GameScene3::exitDo()
{
	getSoundMGR()->stopSounds();
}

void GameScene3::animate()
{
}
