#pragma once
#include "Object.h"
class Wall :
	public Object
{

	float sizeX;
	float sizeY;
public:
	Wall(float sizeX, float sizeY);
	virtual ~Wall();

	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;

};

