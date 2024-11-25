#pragma once
#include "Object.h"


// % 0 is closed door , % 1 is open 
class Door:public Object
{
	static GLuint door_texture[8];
	static bool resource;
	

	int next_stage;

	int animation_frame_number = 0;
	float animation_timer = 0;
	static int sound_door[2];
public:
	Door(int door_number,int next);
	virtual ~Door();

	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;
	void animate();

};

