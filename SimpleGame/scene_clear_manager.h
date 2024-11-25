#pragma once
#include "Object.h"
class SceneClearMGR :
	public Object
{
public:
	SceneClearMGR();
	virtual ~SceneClearMGR();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

