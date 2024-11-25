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

	this->mainchar = MainCharacter::getInstance();

	int hp;
	this->mainchar->getHealthPoint(hp);
	getSceneMGR()->addObj(this->mainchar, -6.2f, 0.2f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_HERO, hp, false, STAGE3);
	this->mainchar->prev_transform.setLocation(-6.2f, 0.2f, 0.5f);


	this->mainchar->init();


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

	//���� �迭�� �̷��� �־ �浹 �� ��ȯ�� �Ͼ�� ���� ���� �ش� ������Ʈ ��ȣ���� �˻縦�ϰ� �Ǵµ�, �� �迭�� ��������� ����� ������ ����.
	//���� ������ �ذ��� ��ƴٰ� ���� ��. ���� ���� Wall�� ����־���.
	/**********************************************************************/

	this->door = new Door(UP, CLEAR);
	getSceneMGR()->addObj(this->door, -0.f, 4.38f, 0.5f,
		1, 0.7, 1,
		0.f, 0.f, 0.0f, KIND_CLOSED_DOOR, 1000, false, STAGE3);

////////////////////////////////////ENEMY///////////////////////////////////////////////////////









	this->enemy[0] = new FinalBoss(this->mainchar, this);

	getSceneMGR()->addObj(this->enemy[0], -5, -3, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_ENEMY, 700, false, STAGE3);


	this->enemy[1] = new Duke(this->mainchar, this);

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

	if (numOfEnemy == 0) {
		this->door->onTrigger();
		//this->closed_wall->onTrigger();

		//this->closed_wall->onDelete();

		//getSceneMGR()->onSceneChange(GAMEOVER);
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