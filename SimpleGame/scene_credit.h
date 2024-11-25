#pragma once
#include "Object.h"
class SceneCredit :
	public Object
{
	GLuint animation;
	int animation_frame_number = 0;
	float animation_timer = 0;
public:
	SceneCredit();
	virtual ~SceneCredit();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

