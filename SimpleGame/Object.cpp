#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "Const.h"
#include "Object.h"
#include "Keyinput.h"
#include "SimpleGame.h"
#include "SceneManager.h"
#include "rptimer.h"



Object::Object() :transform()
{
	float x, y, z;
	this->transform.getScale(x, y, z); 
	this->collision_half_depth = z / 2;
	this->collision_half_width = x / 2;
	this->collision_half_height = y / 2;
}

Object::Object(Transform & x):transform(x)
{
	float sx, sy, sz;
	this->transform.getScale(sx, sy, sz);
	this->collision_half_depth = sz / 2;
	this->collision_half_width = sx / 2;
	this->collision_half_height = sy / 2;
}

Object::Object(float x, float y, float z, float dgr, float sx, float sy,float sz)
	:transform(x, y, z, dgr, sx, sy,sz)
{
	float scx, scy, scz;
	this->transform.getScale(scx, scy, scz);
	this->collision_half_depth = scz / 2;
	this->collision_half_width = scx / 2;
	this->collision_half_height = scy / 2;
}

Object::~Object()
{
}

void Object::onCollision(Object* other)
{
	if (other->getTag() == KIND_DEBUGGER_COLLISION) {
		float x, y, z;
		other->transform.getTransform(x, y, z);
		this->transform = this->prev_transform;
		this->setVelocityZeroXY();
	}

	if (other->getTag() == KIND_NOT_PENETRATING_TILE) {
		float x, y, z;
		other->transform.getTransform(x, y, z);
		this->transform = this->prev_transform;
		this->setVelocityZeroXY();
	}
}

void Object::onTrigger()
{
}

void Object::exitDo()
{
}


GLuint* Object::getCurrentFrameImage()
{
	return this->current_frame_image;
}


void Object::init()
{
}

void Object::update()
{
	this->prev_transform = this->transform;
	this->move();
	this->updateComponet();
	this->updateCollisionArea();
}
void Object::move()
{

	using namespace std;
	this->setAccelation(this->forceX / mass, this->forceY / mass, this->forceZ / mass);
	this->setVelocity(this->accX* RP::RpTimer::getDeltaTime(), this->accY * RP::RpTimer::getDeltaTime(), this->accZ * RP::RpTimer::getDeltaTime());
	calcFrictionalForce(*this, RP::RpTimer::getDeltaTime());
	this->setVelocity(this->fricX* RP::RpTimer::getDeltaTime(), this->fricY * RP::RpTimer::getDeltaTime(), this->fricZ * RP::RpTimer::getDeltaTime());
	calcGravimetricUnit(*this, RP::RpTimer::getDeltaTime());

	this->transform.setTransform(this->velX * RP::RpTimer::getDeltaTime(), this->velY  * RP::RpTimer::getDeltaTime(), this->velZ * RP::RpTimer::getDeltaTime());
}
void Object::updateComponet() {
	using namespace std;
	float x, y, z;
	this->transform.getTransform(x, y, z);

	if (z < 0.5) {
		this->transform.setLocation(x, y, 0.5);
		this->velZ = 0;
		this->air = false;
	}
	else
	{
	
		this->air = true;
	}

	float sx, sy,sz;
	this->transform.getScale(sx, sy,sz);






}
void Object::updateCollisionArea()
{
	float x, y, z;
	this->transform.getTransform(x, y, z);


	float sx, sy, sz;
	this->transform.getScale(sx, sy, sz);

	this->collision_area_rect.max_x = x + collision_half_width;
	this->collision_area_rect.min_x = x - collision_half_width;
	this->collision_area_rect.max_y = y + collision_half_height;
	this->collision_area_rect.min_y = y - collision_half_height;

	this->collision_area_box.max_x = x + collision_half_width;
	this->collision_area_box.max_y = y + collision_half_height;
	this->collision_area_box.max_z = z + collision_half_depth;

	this->collision_area_box.min_x = x - collision_half_width;
	this->collision_area_box.min_y = y - collision_half_height;
	this->collision_area_box.min_z = z - collision_half_depth;
}
void calcFrictionalForce(Object& rhs,float time) {

	float fvxlength = sqrtf(rhs.velX*rhs.velX + rhs.velY * rhs.velY +rhs.velZ * rhs.velZ);
	if (fvxlength != 0) {
	
		float frictionalX = -rhs.velX / fvxlength * rhs.fricCoef;
		float frictionalY = -rhs.velY / fvxlength * rhs.fricCoef;
		float frictionalZ = -rhs.velZ / fvxlength * rhs.fricCoef;
		if ((frictionalX*time +  rhs.velX)*rhs.velX < CST::const_epsilon) {
			rhs.fricX = 0;
			rhs.velX = 0;
		}
		else
		{
			rhs.fricX = frictionalX * rhs.mass;
		}

		if ((frictionalY*time + rhs.velY)*rhs.velY  < CST::const_epsilon) {
			rhs.fricY = 0;
			rhs.velY = 0;
		}
		else {
			rhs.fricY = frictionalY * rhs.mass;
			
		}

		if ((frictionalZ*time + rhs.velZ)*rhs.velZ< CST::const_epsilon) {
			rhs.fricZ = 0;
			rhs.velZ = 0;
		}
		else {
			rhs.fricZ = 0;

		}
	}
	else {
		rhs.fricX = 0;
		rhs.fricY = 0;
		rhs.fricZ = 0;
	}
}

void calcGravimetricUnit(Object& rhs, float time)
{
	using namespace std;
	
	if (!rhs.isFlying())	return;


	float gunit = 9.8f;
	float az = 9.8f * time;
	rhs.setVelocity(0, 0, -az);
}
