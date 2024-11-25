#pragma once
#include "Object.h"
class HealthItem :
	public Object
{
	static GLuint tile;
	static bool resource;
	int frame_number;

	static int sound;

public:
	HealthItem();
	virtual ~HealthItem();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};


