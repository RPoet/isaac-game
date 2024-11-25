#pragma once
#include "Object.h"
class Duke :
	public Object
{
	static GLuint animation_idle[4];
	static bool image;

	int animation_frame_number = 0;
	float animation_timer = 0;

	float resound_timer = 10;
	float jump_timer = 0;
	static int sound_num;

	Object* target;
	Object* manager;
	float distance = 4;

	float targeted_tear_timer = 0;

	float targeted_tear_timer2 = 0;
public:
	Duke(Object* other, Object* mgr);
	virtual~Duke();
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

/*

		for (int i = 0; i < 360; i+=10) {
			getSceneMGR()->addObj(new RedTear(i), x, y, z, 0.2, 0.2, 0.2, 5*cosf(i*3.141592/180), 5*sinf(i*3.141592 / 180), 0, KIND_ENEMY_BULLET, 1, false);
		}*/