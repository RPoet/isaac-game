#pragma once
#include <float.h>
namespace CST {
	const float const_gravity = 9.80665;

	const float const_epsilon = FLT_EPSILON;

	const int kMaxObj = 300;
	const int kHero = 0;


	const double kFrmaeTime = 0.016;


}
enum dir {
	UP, DOWN, RIGHT, LEFT, NONE
};

enum SCENE_NUMBER {
	CREDIT,TITLE,STAGE1,STAGE2,STAGE3,CLEAR,GAMEOVER
};

#define HALF_MAP_WIDTH 8
#define HALF_MAP_HEIGHT 5


#define BULLET_HP 50
#define HERO_ID 0
#define MAX_OBJECTS 300
#define SHOOT_NONE -1
#define SHOOT_RIGHT 1
#define SHOOT_UP 2
#define SHOOT_LEFT 3
#define SHOOT_DOWN 4

#define KIND_HERO 0
#define KIND_BULLET 1
#define KIND_BUILDING 2
#define KIND_BACKGROUND 3
#define KIND_ENEMY 4
#define KIND_BILLBOARD 5
#define KIND_MGR 6
#define KIND_DEBUGGER_COLLISION 7
#define KIND_CLOSED_DOOR 8
#define KIND_OPEN_DOOR 9
#define KIND_ENEMY_BULLET 10

#define KIND_BOSS_MGR 11
#define KIND_STAGE2_MGR 12
#define KIND_PENETRATING_TILE 13
#define KIND_NOT_PENETRATING_TILE 14
#define KIND_ITEM 15

#define KIND_EFFECT 100

#define KIND_UI 101
