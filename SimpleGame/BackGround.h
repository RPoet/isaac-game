#pragma once
#include "Object.h"
class BackGround :
	public Object
{
	static GLuint back_ground_image;
	static bool image;


	static BackGround* instance;
public:
	BackGround();
	virtual ~BackGround();

	void fetchImage();
	virtual void init() override;
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	virtual void exitDo() override;


	static BackGround* getInstance();
};

