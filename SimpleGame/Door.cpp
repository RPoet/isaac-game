#include "stdafx.h"
#include "Door.h"
#include "SimpleGame.h"
#include <string>

using namespace std;
GLuint Door::door_texture[8] = { 0, };
bool Door::resource = false;
int Door::sound_door[2] = { 0, };
enum {
	DOWN_DOOR = 1,LEFT_DOOR =3,RIGHT_DOOR =5, UP_DOOR = 7
};
Door::Door(int door_dir,int next):Object()
{
	if (!this->resource)fetchImage();

	this->next_stage = next;

	switch (door_dir) {

	case dir::DOWN:
		animation_frame_number = DOWN_DOOR;
		break;
	case dir::LEFT:
		animation_frame_number = LEFT_DOOR;
		break;

	case dir::RIGHT:
		animation_frame_number = RIGHT_DOOR;
		break;

	case dir::UP:
		animation_frame_number = UP_DOOR;
		break;


	}
	this->current_frame_image = &this->door_texture[animation_frame_number];

}


Door::~Door()
{
}

void Door::fetchImage()
{
	this->sound_door[0] = getSoundMGR()->CreateSound("assets/sounds/doorOpen.mp3");
	this->sound_door[1] = getSoundMGR()->CreateSound("assets/sounds/doorClose.mp3");
	for (int i = 0; i < 8; ++i) {
		string path("assets/Tile/Tile");
		path += to_string(i+11);
		path += (".png");
		Door::door_texture[i] = getRenderer()->CreatePngTexture(const_cast<char*>(path.c_str()));
	}

	this->resource = true;
}

void Door::init()
{
	float sx, sy, sz;

	this->transform.getScale(sx, sy, sz);
	this->setCollisionParams(sx / 100, sy / 100, sz / 100);
	//this->transform.setScale(this->sizeX, this->sizeY,1);
	Object::update();

}

void Door::update()
{
	if (KIND_CLOSED_DOOR == this->tag) {
			
	}
	else if (KIND_OPEN_DOOR== this->tag) {

	}
}

void Door::onCollision(Object* other)
{
	if (KIND_HERO == other->getTag()) {
		if (this->tag == KIND_OPEN_DOOR)
		{
			cout << "DOOR NEXT = " << this->next_stage << endl;
			//getSoundMGR()->PlaySoundW(this->sound_door[1], false, 1.0f);
			getSceneMGR()->onSceneChange(this->next_stage);
		}
	}
}

void Door::onTrigger()
{
	if (this->tag != KIND_OPEN_DOOR)
	{
		this->tag = KIND_OPEN_DOOR;
		this->current_frame_image = &this->door_texture[--animation_frame_number];
		getSoundMGR()->PlaySoundW(this->sound_door[0], false, 1.0f);
	}
}

void Door::exitDo()
{
	//getSoundMGR()->DeleteSound(this->sound_slot);
}

void Door::animate()
{
}
