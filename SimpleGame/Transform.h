#pragma once
class Transform
{
	float tx, ty,tz, sx, sy,sz, dgr;

	void clamp(float low, float &now, float max);
public:
	Transform();
	Transform(float x, float y,float z,float dgr, float sx,float sy,float sz);
	~Transform();
	void getTransform(float& x, float& y, float& z);
	void getScale(float& sx, float& sy, float& sz);
	void getDegree(float& degree);
	void setLocation(float x, float y, float z);//fixed loc
	void setTransform(float x, float y, float z);//affine translation
	void setDegree(float dgr);
	void setScale(float sx, float sy, float sz);
};

