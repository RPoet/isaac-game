#pragma once
#include "Object.h"
class GameScene1 :
	public Object
{
	int numOfEnemy = 10;

	Object* mainchar;
	Object* back_ground;
	Object* door;
	Object* enemy[10];

	int sound = -1;

public:
	GameScene1();
	virtual ~GameScene1();
	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;
	void animate();
};


