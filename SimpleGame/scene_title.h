#pragma once
#include "Object.h"
class SceneTitle :
	public Object
{
	GLuint animation[2];
	int animation_frame_number = 0;
	float animation_timer = 0;

	bool flag = false;
public:
	SceneTitle();
	virtual ~SceneTitle();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;
	void animate();
};

