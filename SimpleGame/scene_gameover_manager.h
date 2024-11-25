#pragma once
#include "Object.h"
class SceneGameOverMGR :
	public Object
{
public:
	SceneGameOverMGR();
	virtual ~SceneGameOverMGR();
	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

