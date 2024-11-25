#pragma once
#include "Object.h"
class Explosion2 :
	public Object
{
	static GLuint effect_explosion_animation[19];
	static bool image;
	static int sound_num;

	int animation_frame_number = 0;
	float animation_timer = 0;
public:
	Explosion2();
	virtual~Explosion2();
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();

};



