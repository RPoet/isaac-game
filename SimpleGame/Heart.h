#pragma once
#include "Object.h"
class Heart :
	public Object
{
	static GLuint heart_image[2];
	static bool image;

	int animation_frame_number = 0;
	float animation_timer = 0;

public:
	Heart();
	virtual ~Heart();

	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;
	void animate();

	void modifyHeart();
	void heal();
};

