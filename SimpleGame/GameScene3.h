#pragma once
#include "Object.h"
class GameScene3 :
	public Object
{
	int numOfEnemy = 2;

	Object* mainchar;
	Object* back_ground;
	Object* door;
	Object* closed_wall;
	Object* enemy[2];

	int sound;

public:
	GameScene3();
	virtual ~GameScene3();
	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;
	void animate();
};


