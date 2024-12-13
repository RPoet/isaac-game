#pragma once
#include "Dependencies\glew.h"
#include "Transform.h"
#include "Collider.h"
#include "Const.h"
class Transform;

//언리얼에서 1 이 10cm


// 쏘는 방향을 받아야하고,
// ScrMgr 에서 AddObject로 추가해야 된다.

class Object
{
	float colorR, colorG, colorB, colorA = 1;

	float forceX=0;
	float forceY=0;
	float forceZ=0;

	float mass = 1;

	float velX = 0;
	float velY = 0;
	float velZ = 0;

	float accX = 0;
	float accY = 0;
	float accZ = 0;

	float fricX = 0;
	float fricY = 0;
	float fricZ = 0;

	float fricCoef = 2;
	float roughness = 1;

	float collision_half_width, collision_half_height, collision_half_depth =0;


	friend void calcFrictionalForce(Object& rhs, float time);
	friend void calcGravimetricUnit(Object&, float);

	bool is_to_be_deleted = false;


	void Object::updateComponet();
protected:	
	Rect collision_area_rect;
	Box collision_area_box;

	GLuint* current_frame_image = nullptr;
	int health_point;
	int dir = NONE;
	float timer = 0;
	int tag;

	bool air = false;
	int sound_slot;
	virtual void updateCollisionArea();
	void clamp(float low, float & now, float max)
	{
		if (low > now) now = low;
		if (max < now) now = max;
	}
public:
	Transform transform;
	Transform prev_transform;
	float animX = 0;
	float animY = 0;
	Object(); 

	Object(Transform& x);
	Object(float x,float y ,float z, float dgr,float sx,float sy,float sz);
	virtual ~Object();
	
	void move();
	inline void setCollisionParams(float width, float height, float depth)
	{
		this->collision_half_width = width/2;
		this->collision_half_height = height/2;
		this->collision_half_depth = depth/2;
	}
	inline void getCollisionParams(float& width, float& height, float& depth)
	{
		width = this->collision_half_width;
		height = this->collision_half_height;
		depth = this->collision_half_depth;
	}
	inline void addForce(float x, float y, float z)
	{
		this-> forceX = x;
		this-> forceY = y;
		this->forceZ = z;
	}
	inline void getForce(float&x, float&y, float& z)
	{
		 x = this->forceY;
		 y = this->forceX;
		 z = this->forceZ;
	}
	void getVelocity(float&x, float&y, float& z) {
		x = this->velX;
		y = this->velY;
		z = this->velZ;
	}
	void setVelocity(float x, float y, float z) {
		this->velX += x;
		this->velY += y;
		this->velZ += z;
	}
	void setVelocityZeroXY() {
		this->velX = 0;
		this->velY = 0;
	}

	inline void setAccelation(float x, float y, float z) {
		this->accX = x;
		this->accY = y;
		this->accZ = z;
	}

	inline void getAccelation(float &x, float& y, float &z) {
		x = this->accX;
		y = this->accY;
		z = this->accZ;
	}

	void setColor(float r, float g, float b, float a) {
		colorA = a;
		colorB = b;
		colorG = g;
		colorR = r;
	}

	void getColor(float& r, float& g, float& b, float& a)
	{
		r = colorR;
		g = colorG;
		b = colorB;
		a = colorA;
	}

	void setRoughness(float rhs) { this->roughness = rhs; }
	void getRoughness(float&rhs) { rhs = this->roughness; }

	void setMass(int rhs) { this->mass = rhs; }
	void getMass(int& rhs) { rhs = this->mass; }
	void setTag(int tag) { this->tag = tag;  }
	int  getTag() { return this->tag; }
	

	void setHeathPoint(int hp) {
		this->health_point = hp;
	}
	void getHealthPoint(int& hp) {
		hp = this->health_point;
	}
	void setFrictionalCoef(float rhs) { this->fricCoef = rhs; };
	void getFrictionalCoef(float &rhs) { rhs = this->fricCoef; }

	Rect getArea() const {
		return this->collision_area_rect;
	}
	Box getAreaBox() const {
		return this->collision_area_box;
	}

	inline bool isFlying() {
		return this->air;
	};



	virtual void init();
	virtual void update();
	virtual void onCollision(Object*);
	virtual void onTrigger();
	virtual void exitDo();
	void onDelete() {
		this->is_to_be_deleted = true;
	}
	bool isDeleted() {
		return this->is_to_be_deleted;
	}


	GLuint* getCurrentFrameImage();

};

void calcFrictionalForce(Object&,float);

void calcGravimetricUnit(Object&, float);