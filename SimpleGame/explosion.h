#pragma once
#include "Object.h"
class Explosion :
	public Object
{
	static GLuint effect_explosion_animation[11];
	static bool image;
	static int sound_num;

	int animation_frame_number = 0;
	float animation_timer = 0;
public:
	Explosion();
	virtual~Explosion();
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();

};



