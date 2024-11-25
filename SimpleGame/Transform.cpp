#include "stdafx.h"
#include "Transform.h"
#include "Const.h"

void Transform::clamp(float low, float & now, float max)
{
	if (low > now) now = low;
	if (max < now) now = max;
}

Transform::Transform() :tx(0), ty(0),tz(0), sx(1), sy(1), dgr(0),sz(1)
{
}


Transform::Transform(float x, float y,float z, float dgr, float sx, float sy, float sz)
	:tx(x), ty(y),tz(z), sx(sx), sy(sy), dgr(dgr),sz(sz)
{
}

Transform::~Transform()
{
}

void Transform::getTransform(float & x, float & y, float &z)
{
	x = this->tx;
	y = this->ty;
	z = this->tz;
}

void Transform::getScale(float & sx, float & sy, float & sz)
{
	sx = this->sx;
	sy = this->sy;
	sz = this->sz;
}

void Transform::getDegree(float & degree)
{
	degree = this->dgr;
}

void Transform::setLocation(float x, float y, float z)
{
	this->tx = x;
	this->ty = y;
	this->tz = z;
}

void Transform::setTransform(float x, float y,float z)
{
	this->tx += x;
	this->ty += y;
	this->tz += z;
	clamp(-HALF_MAP_WIDTH-2 , this->tx, HALF_MAP_WIDTH + 2);
	clamp(-HALF_MAP_HEIGHT-2 , this->ty, HALF_MAP_HEIGHT + 2);
}


void Transform::setDegree(float dgr)
{
	this->dgr += dgr;
}

void Transform::setScale(float sx, float sy, float sz)
{
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}
