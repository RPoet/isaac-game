#pragma once
#include "Object.h"
class Tear :
	public Object
{

	static GLuint tear_animation[16];
	static bool resource;

	bool isBombed = false;

	int animation_frame_number = 0;
	float animation_timer = 0;
	static int sound_number[2];
public:
	Tear();
	virtual ~Tear();
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

