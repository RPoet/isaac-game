#pragma once

#include "TransForm.h"

enum {
	RECTANGLE,ELLIPSE
};

struct Rect {
public:
	float min_x,  min_y,  max_x,  max_y;
};

struct Box {
public:
	float min_x, min_y,min_z, max_x, max_y, max_z;
};
