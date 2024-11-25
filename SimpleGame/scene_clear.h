#pragma once
#include "Object.h"
class SceneClear :
	public Object
{
	GLuint animation;
	int animation_frame_number = 0;
	float animation_timer = 0;

	int sound;
public:
	SceneClear();
	virtual ~SceneClear();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

