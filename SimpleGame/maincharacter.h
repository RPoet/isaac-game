#pragma once
#include "Object.h"
#include "Heart.h"

class MainCharacter :
	public Object
{
	static GLuint down_animation[3];
	static GLuint right_animation[3];
	static GLuint left_animation[3];
	static GLuint up_animation[3];
	static bool image;
	
	int animation_frame_number = 0;
	float animation_timer = 0;


	static int sound_number;
	static int sound_hit;

	float overwhelming_timer = 10;
	
	static MainCharacter* instance;

	Heart* hp[10];

public:
	MainCharacter();
	MainCharacter(Transform& x);
	MainCharacter(float x, float y, float z, float dgr, float sx, float sy, float sz);
	void fetchImage();
	virtual ~MainCharacter();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void updateCollisionArea() override;
	void animate();


	void definedKeyAct();


	virtual void init() override;
	static MainCharacter* getInstance();
};

