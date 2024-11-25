#include "stdafx.h"
#include <string>
#include "SimpleGame.h"
#include "Tile.h"
#include "explosion2.h"
#include "HealthItem.h"
#include <stdlib.h>
GLuint Tile::tile[11]; 
bool Tile::resource = false;

Tile::Tile(int Tile)
{
	if (!this->resource)fetchImage();

	this->frame_number = Tile;
	this->current_frame_image = &this->tile[Tile];
}

Tile::~Tile()
{
	float x, y, z;
	this->transform.getTransform(x, y, z);
	getSceneMGR()->addObj(new Explosion2(), x, y, z, 1, 1, 1, 0, 0, 0, KIND_EFFECT, 1, false);

	if (rand() % 2 == 0) {
		getSceneMGR()->addObj(new HealthItem(), x, y, z, 0.5, 0.5, 0.5, 0, 0, 0, KIND_ITEM, 1, false);
	}
}

void Tile::init()
{
	float sx, sy, sz;

	this->transform.getScale(sx, sy, sz);
	this->setCollisionParams(sx / 100, sy / 100, sz / 100);
	Object::update();
}


void Tile::fetchImage()
{
	using namespace std;
	for (int i = 0; i < 11; ++i) {
		string path("assets/Tile/Tile");
		path += to_string(i);
		path += (".png");
		Tile::tile[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}

	this->resource = true;
}

void Tile::update()
{
}

void Tile::onCollision(Object* other)
{
	if (KIND_BULLET == other->getTag()) {
		this->health_point--;
		other->onTrigger();
	}
}

void Tile::onTrigger()
{
}

void Tile::animate()
{
}
