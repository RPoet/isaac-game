#pragma once
#include "Object.h"

enum {
	AIR,POOP1,POOP2,POOP3,POOP4,POOP5,STONE1,STONE2,STONE3,STONE4,STONE5
};
class Tile :
	public Object
{

	static GLuint tile[11];
	static bool resource;
	int frame_number;
public:
	Tile(int Tile);
	virtual ~Tile();

	virtual void init() override;
	void fetchImage();
	virtual void update() override;
	virtual void onCollision(Object*)override;
	virtual void onTrigger()override;
	void animate();
};

