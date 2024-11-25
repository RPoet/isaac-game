#include "stdafx.h"
#include "HealthItem.h"
#include "SimpleGame.h"

 GLuint HealthItem::tile;
 bool HealthItem::resource = false;
 int HealthItem::sound = -99;

HealthItem::HealthItem()
{
	if (!resource) this->fetchImage();

	this->current_frame_image = &this->tile;
	this->sound = getSoundMGR()->CreateSound("assets/sounds/eatitem.mp3");
}


HealthItem::~HealthItem()
{
}

void HealthItem::init()
{
}

void HealthItem::fetchImage()
{
	this->sound = getSoundMGR()->CreateSound("assets/sounds/eatitem.mp3");
	HealthItem::tile= getRenderer()->CreatePngTexture("assets/Heart/h2.png");//±øÅë
}

void HealthItem::update()
{
	float sx, sy, sz;

	this->transform.getScale(sx, sy, sz);
	this->setCollisionParams(sx / 100, sy / 100, sz / 100);
	Object::update();
}

void HealthItem::onCollision(Object* other)
{
	if(other->getTag() == KIND_HERO) {
		this->onDelete();
		int hp;
		other->getHealthPoint(hp);

		hp++;
		other->setHeathPoint(hp);
		getSoundMGR()->PlaySoundW(this->sound, false, 1.0f);
	}
}

void HealthItem::onTrigger()
{
}

void HealthItem::animate()
{
}
