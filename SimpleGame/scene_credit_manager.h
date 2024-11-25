#pragma once
#include "Object.h"
class SceneCreditMGR :
	public Object
{
public:
	SceneCreditMGR();
	virtual ~SceneCreditMGR();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
};

