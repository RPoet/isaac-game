#pragma once
#include "Object.h"
class GameScene2 :
	public Object
{
	int numOfEnemy = 8;

	Object* mainchars[2];

	Object* back_ground;
	Object* door;
	Object* closed_wall;
	Object* enemy[8];

	int sound;

public:
	GameScene2();
	virtual ~GameScene2();
	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;
	void animate();
};


