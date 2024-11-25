#include "stdafx.h"
#include "BackGround.h"
#include "SimpleGame.h"

GLuint BackGround::back_ground_image = 0;
bool BackGround::image = false;
BackGround* BackGround::instance = nullptr;

BackGround::BackGround()
{
	if(!image)	fetchImage();

	this->current_frame_image = &back_ground_image;
}

BackGround::~BackGround()
{
}

void BackGround::fetchImage()
{
	this->image = true;

	this->back_ground_image = getRenderer()->CreatePngTexture("assets/bg.png");
}

void BackGround::init()
{
	this->transform.setScale(1600, 1000, 0);
}

void BackGround::update()
{
}

void BackGround::onCollision(Object *)
{
}

void BackGround::onTrigger()
{
}

void BackGround::exitDo()
{
}

BackGround * BackGround::getInstance()
{
	if (instance != nullptr) return instance;

	instance = new BackGround();
	return instance;
}
