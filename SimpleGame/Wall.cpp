#include "stdafx.h"
#include "Wall.h"


Wall::Wall(float sizeX, float sizeY):Object(),sizeX(sizeX),sizeY(sizeY)
{
	this->tag = KIND_DEBUGGER_COLLISION;
}


Wall::~Wall()
{
}

void Wall::fetchImage()
{
}

void Wall::init()
{
	float sx, sy, sz;

	this->transform.getScale(sx, sy, sz);
	this->setCollisionParams(sx/100, sy/100, sz/100);
	Object::update();
}

void Wall::update()
{
	
}

void Wall::onCollision(Object *)
{
}

void Wall::onTrigger()
{
}

void Wall::exitDo()
{
}
