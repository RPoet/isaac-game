#pragma once
#include "Object.h"
class SceneTitleMGR :
	public Object
{

public:
	SceneTitleMGR();
	virtual ~SceneTitleMGR();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;

	virtual void exitDo() override final;
};

