#include "stdafx.h"
#include "Heart.h"
#include "SimpleGame.h"

bool  Heart::image = false;
GLuint Heart::heart_image[2];

Heart::Heart():Object()
{
	if (!Heart::image)	this->fetchImage();

	animation_frame_number = 0;

	this->current_frame_image = &this->heart_image[animation_frame_number];
	this->setCollisionParams(0, 0, 0);
}


Heart::~Heart()
{
}

void Heart::fetchImage()
{
	Heart::heart_image[0] = getRenderer()->CreatePngTexture("assets/Heart/h0.png");//º»Ã¼
	Heart::heart_image[1] = getRenderer()->CreatePngTexture("assets/Heart/h1.png");//±øÅë

	this->image = true;
}

void Heart::init()
{
}

void Heart::update()
{
	this->current_frame_image = &this->heart_image[animation_frame_number];
}

void Heart::onCollision(Object *)
{
}

void Heart::onTrigger()
{

}

void Heart::exitDo()
{
}

void Heart::animate()
{
}

void Heart::modifyHeart()
{
	
	//animation_frame_number = (animation_frame_number+1)%2;
	animation_frame_number = 1;
}

void Heart::heal()
{
	animation_frame_number = 0;
}
