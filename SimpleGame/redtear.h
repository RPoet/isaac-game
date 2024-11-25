#pragma once
#include "Object.h"
class RedTear :
	public Object
{

	static GLuint tear_animation[17];
	static bool resource;

	bool isBombed = false;

	int animation_frame_number = 0;
	float animation_timer = 0;
	static int sound_number[2];

	
public:
	RedTear(float degree);
	virtual ~RedTear();
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

