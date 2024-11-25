#pragma once
#include "Object.h"
class explosion_red_tear :
	public Object
{
	static GLuint tear_animation[17];
	static bool image;

	bool isBombed = false;

	int animation_frame_number = 0;
	float animation_timer = 0;



public:
	explosion_red_tear();
	virtual~explosion_red_tear();

	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};


