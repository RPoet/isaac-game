#pragma once
#include "Object.h"
class explosion_tear :
	public Object
{
	static GLuint tear_animation[16];
	static bool image;

	bool isBombed = false;

	int animation_frame_number = 0;
	float animation_timer = 0;



public:
	explosion_tear();
	virtual~explosion_tear();

	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};


