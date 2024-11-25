#pragma once
#include "Object.h"
class BlackFly :
	public Object
{

	static GLuint left[2];
	static GLuint right[2];
	static bool image;

	int dir;
	int animation_frame_number = 0;
	float animation_timer = 0;


	static int sound_num;

	Box real_collision_box;

	Object* target;
	Object* manager;
	float distance = 3;
public:
	BlackFly(Object* other,Object* mgr);
	virtual ~BlackFly();
	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();

	void wander();
};

