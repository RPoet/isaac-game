#pragma once
#include "Object.h"
class SceneGameOver :
	public Object
{
	GLuint animation;
	int animation_frame_number = 0;
	float animation_timer = 0;
	int sound;
public:
	SceneGameOver();
	virtual ~SceneGameOver();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

