
#include "stdafx.h"

#include "SimpleGame.h"

#include "SceneManager.h"

#include "scene_credit_manager.h"
#include "scene_title_manager.h"
#include "GameScene1.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "scene_clear_manager.h"
#include "scene_gameover_manager.h"


#include "Renderer.h"
#include "Object.h"
#include "Keyinput.h"
#include "Const.h"
#include "RPtimer.h"
#include "Keyinput.h"
#include "maincharacter.h"
#include "tear.h"
#include "explosion.h"
#include "enemy_red.h"

#include <gl/GL.h>
int g_shoot = SHOOT_NONE;

unsigned int SceneManager::current_scene_number = 0;

SceneManager::SceneManager()
{
	this->renderer = getRenderer();
	this->back_ground_texture = renderer->CreatePngTexture("assets/bg.png");
	this->snow_texture = renderer->CreatePngTexture("assets/snow_texture.png");
	this->shadow = renderer->CreatePngTexture("assets/CharacterBG.png");
	this->forBuilding = renderer->CreatePngTexture("assets/ia.png");
	this->shadowTexture = renderer->CreatePngTexture("assets/shadow.png");


	this->shading_room_texture = renderer->CreatePngTexture("assets/shading.png");


	if (!renderer->IsInitialized()) std::cout << "Renderer could not be initialized.. \n";


	for (int i = 0; i < GAMEOVER+1; ++i) {
		for (int j = 0; j < CST::kMaxObj; ++j)
			this->poolOfObjects[i][j] = nullptr;
	}

}


SceneManager::~SceneManager()
{
	for (int j = 0; j < CST::kMaxObj; ++j) {
		for (int i = 0; i < CST::kMaxObj; ++i) {
			if (nullptr != this->poolOfObjects[j][i]) {
				delete poolOfObjects[j][i];
			}
		}
	}
}

void SceneManager::init()
{
	this->addObj(new SceneCreditMGR(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_MGR, 1000, false, CREDIT);

	this->addObj(new SceneTitleMGR(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_MGR, 1000, false, TITLE);

	this->addObj(new GameScene1(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_MGR, 1000, false, STAGE1);

	this->addObj(new GameScene2(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_STAGE2_MGR, 1000, false, STAGE2
	);

	this->addObj(new GameScene3(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_BOSS_MGR, 1000, false, STAGE3
	);

	this->addObj(new SceneClearMGR(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_MGR, 1000, false, CLEAR
	);

	this->addObj(new SceneGameOverMGR(), 1.f, 0.f, 0.5f,
		1, 1, 1,
		0.f, 0.f, 0.0f, KIND_MGR, 1000, false, GAMEOVER
	);

}

void SceneManager::renderScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0, 0, 1);


	//CST::kMaxObj
	for (int i = 0; i < CST::kMaxObj; ++i) {
		if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][i]) {

			/////////////////////////
			float x, y, z, dgr, sx, sy, sz, r, g, b, a;
			float newX, newY, newZ, newW, newH;

			this->poolOfObjects[SceneManager::current_scene_number][i]->transform.getTransform(x, y, z);
			this->poolOfObjects[SceneManager::current_scene_number][i]->transform.getDegree(dgr);
			this->poolOfObjects[SceneManager::current_scene_number][i]->transform.getScale(sx, sy, sz);
			this->poolOfObjects[SceneManager::current_scene_number][i]->getColor(r, g, b, a);
			newX = x * 100.0f;
			newY = y * 100.0f;
			newZ = z * 100.0f;

			newW = sx * 100.0f; // 1당 화면의 1미터로 잡고 거기에 100픽셀을 곱해준격.
			newH = sy * 100.0f;
			///////////////////////// 

			switch (this->poolOfObjects[this->current_scene_number][i]->getTag()) {
			case KIND_BILLBOARD:
				this->renderer->DrawTextureRect(0, 0, 0,
					sx, sy,			//백그라운드는 사이즈 그대로 그려주면 된다.
					r, g, b, a, *this->poolOfObjects[SceneManager::current_scene_number][i]->getCurrentFrameImage());

				break;
			case KIND_PENETRATING_TILE:
			case KIND_NOT_PENETRATING_TILE:
			case KIND_EFFECT:
			case KIND_ENEMY:
			case KIND_HERO:
			case KIND_BULLET:
			case KIND_OPEN_DOOR:
			case KIND_CLOSED_DOOR:
			case KIND_ENEMY_BULLET:
			case KIND_ITEM:
				this->renderer->DrawTextureRectHeight(newX, newY - newH/1.45, 0.5,
					newW  * 0.75, newH * 0.75,										//그리는 케릭터의 사이즈에 알맞게 축소되고 커지고 한다.
					r, g, b, a,
					this->shadow,
					newZ);
				this->renderer->DrawTextureRectSeqXYHeight(newX, newY - newH / 1.45, 0.5,
					newW  *2 , newH  * 2,
					r, g, b, a,
					*this->poolOfObjects[SceneManager::current_scene_number][i]->getCurrentFrameImage(),0,0,
					1,1,
					newZ-40);

				break;
			case KIND_UI:
				this->renderer->DrawTextureRectDepth(x, y, z,
					sx*25, sy*25,
					1, 1, 1, 1,
					*this->poolOfObjects[SceneManager::current_scene_number][i]->getCurrentFrameImage(),
					-1);
				break;

			case KIND_BACKGROUND:
				this->renderer->DrawTextureRectDepth(0, 0, -100,
					sx, sy,
					1, 1, 1, 1,
					*this->poolOfObjects[SceneManager::current_scene_number][i]->getCurrentFrameImage(),
					100.0f);
				this->renderer->DrawTextureRectDepth(0, 0, -100,
					sx, sy,
					1, 1, 1, 1,
					this->shading_room_texture,
					99.9f);
				break;

			case KIND_DEBUGGER_COLLISION:
				//this->renderer->DrawSolidRect(newX, newY, 0,
				//	sx, sy,			//백그라운드는 사이즈 그대로 그려주면 된다.
				//	1, 0,0, 1);

				break;

			}

			switch (this->current_scene_number) {
			case STAGE2:
				this->renderer->DrawParticleClimate(0, 0, 0,
					5,//파티클 사이즈
					1, 1, 1, 1,
					sinf(RP::RpTimer::getPlayTime()), cosf(RP::RpTimer::getPlayTime()),		//파티클의 방향
					this->snow_texture,
					0.3f,  // 파티클에 대한 비율
					RP::RpTimer::getPlayTime());
				break;
			case STAGE3:
				this->renderer->DrawParticleClimate(0, 0, 0,
					5,//파티클 사이즈
					1, 1, 1, 1,
					sinf(RP::RpTimer::getPlayTime()), cosf(RP::RpTimer::getPlayTime()),		//파티클의 방향
					this->snow_texture,
					1.f,  // 파티클에 대한 비율
					RP::RpTimer::getPlayTime());
				break;
			}

			//
			//this->renderer->DrawTextureRectHeight(newX, newY - newH/1.45, 0.5,
			//	newW  * 1, newH * 1,
			//	r, g, b, a,
			//	*this->poolOfObjects[SceneManager::current_scene_number][i]->getCurrentFrameImage(),
			//	newZ
			//);


			//this->renderer->DrawSolidRectGauge(newX, newY - newH / 1.45, 0.5,
			//	newW / 100 * 50, newH / 100 * 25,
			//	r, g, b, a,
			//	newZ,
			//	0.5f // 게이지 차있는 계수
			//);

			//this->renderer->DrawTextureRectSeqXYHeight(newX, newY - newH / 1.45, 0.5,
			//	newW  * 2, newH  *2,
			//	r, g, b, a,
			//	*this->poolOfObjects[SceneManager::current_scene_number][i]->getCurrentFrameImage(),0,0,
			//	1,1,
			//	newZ-15);

			//this->renderer->DrawParticleClimate(0, 0, 0, 
			//	5,//파티클 사이즈
			//	1, 1, 1, 1,
			//	sinf(RP::RpTimer::getPlayTime()), cosf(RP::RpTimer::getPlayTime()),		//파티클의 방향
			//	this->snow_texture,
			//	1.f,  // 파티클에 대한 비율
			//	RP::RpTimer::getPlayTime());
		}
	}

}

void SceneManager::update()
{
	KeyIO::update();
	
	for (int i = 0; i < CST::kMaxObj; ++i) {
		if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][i]) {
			this->poolOfObjects[SceneManager::current_scene_number][i]->update();
			
		}
	}	
	this->processCollision();
	this->garbageCollector();
}

void SceneManager::doCollisionTest()
{
	for (int i = 0; i < CST::kMaxObj; ++i) {
		if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][i]) {
			for (int j = i + 1; j < CST::kMaxObj; ++j) {
				if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][j]) {
					if (this->collide(this->poolOfObjects[SceneManager::current_scene_number][i]->getArea(), this->poolOfObjects[SceneManager::current_scene_number][j]->getArea())) {
						poolOfObjects[SceneManager::current_scene_number][j]->setColor(0, 0, 0, 1);
					}
				}
			}
		}
	}
}

void SceneManager::processCollision()
{
	for (int i = 0; i < CST::kMaxObj-1; ++i) {
		if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][i]) {
			int col = 0;
			for (int j = i + 1; j < CST::kMaxObj; ++j) {
				if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][j]) {

					if (this->collide(this->poolOfObjects[SceneManager::current_scene_number][i]->getAreaBox(), this->poolOfObjects[SceneManager::current_scene_number][j]->getAreaBox())) {
						if (poolOfObjects[SceneManager::current_scene_number][i]->getTag() != poolOfObjects[SceneManager::current_scene_number][j]->getTag()) {

						
							//std::cout << debug << std::endl;

							poolOfObjects[this->current_scene_number][i]->onCollision(this->poolOfObjects[this->current_scene_number][j]);
							//if (poolOfObjects[SceneManager::current_scene_number][j]->getTag() == KIND_OPEN_DOOR) break;
							poolOfObjects[this->current_scene_number][j]->onCollision(this->poolOfObjects[this->current_scene_number][i]);
							
							
							col++;
						}
					}
				}
			}

			//if (col > 0) poolOfObjects[SceneManager::current_scene_number][i]->setColor(1, 0, 0, 1);
			//else poolOfObjects[SceneManager::current_scene_number][i]->setColor(1, 1, 1, 1);
		}
	}
}


void SceneManager::addObj(Object* obj, float x, float y, float z, float sx, float sy, float sz,
	float vx, float vy, float vz,
	int kind, int hp, bool air,
	int sceneNum)
{
	using namespace std;

	int slotnum;
	SceneManager::fetchEmptySlot(slotnum,sceneNum);
	if (slotnum < 0)return;


	obj->transform.setLocation(x, y, z);
	obj->transform.setScale(sx, sy, sz);
	obj->setVelocity(vx, vy, vz);
	obj->setAccelation(0, 0, 0);
	obj->setMass(1);
	obj->setFrictionalCoef(1);
	obj->setColor(1, 1, 1, 1);
	obj->setTag(kind);
	obj->setHeathPoint(hp);

	this->poolOfObjects[sceneNum][slotnum] = obj;
}

void SceneManager::deleteObject(int idx)
{
	if (this->poolOfObjects[SceneManager::current_scene_number][idx] != nullptr)
	{
		delete this->poolOfObjects[SceneManager::current_scene_number][idx];
		this->poolOfObjects[SceneManager::current_scene_number][idx] = nullptr;
	}
}

void SceneManager::fetchEmptySlot(int &id,int SceneNumber)
{
	for (int i = 0; i < CST::kMaxObj; ++i) {
		if (this->poolOfObjects[SceneNumber][i] == nullptr) {
			id = i;
			return;
		}
	}
	std::cout << "no more empty slot" << std::endl;
	id = 1;
}

void SceneManager::garbageCollector(void)
{
	for (int i = 1; i < CST::kMaxObj; ++i) {
		if (nullptr != this->poolOfObjects[SceneManager::current_scene_number][i]) {
			int hp;
			this->poolOfObjects[SceneManager::current_scene_number][i]->getHealthPoint(hp);
			if (hp <= 0 && this->poolOfObjects[SceneManager::current_scene_number][i]->getTag() != KIND_HERO) {
			
				this->deleteObject(i);
				continue;
			}

			if (this->poolOfObjects[SceneManager::current_scene_number][i]->isDeleted()) {
				this->deleteObject(i);
				continue;
			}
			if (this->poolOfObjects[SceneManager::current_scene_number][i]->getTag() == KIND_BULLET ||
				this->poolOfObjects[SceneManager::current_scene_number][i]->getTag() == KIND_ENEMY_BULLET ) {
				float velx, vely, velZ;
				this->poolOfObjects[SceneManager::current_scene_number][i]->getVelocity(velx, vely, velZ);


				if (int(velx) == 0 && int(vely == 0)) {
					//this->deleteObject(i);
					this->poolOfObjects[SceneManager::current_scene_number][i]->onTrigger();
					continue;
				}
			}

			float x, y, z;
			this->poolOfObjects[SceneManager::current_scene_number][i]->transform.getTransform(x, y, z);

			if (x > 8 || x <-8 || y>5 || y < -5) {
				//this->deleteObject(i);
				this->poolOfObjects[SceneManager::current_scene_number][i]->onTrigger();
				continue;
			}
		}
	}
}


void SceneManager::shoot(int shootid, Object& Player)
{
	if (shootid == dir::NONE) return;
	float amount =4.0f;
	float bvX, bvY,bvZ;
	bvX = 0.f;
	bvY = 0.f;
	bvZ = 0.f;
	switch (shootid) {
	case dir::RIGHT:
		bvX = amount;
		bvY = 0;
		bvZ = 0.f;
		break;
	case dir::LEFT:
		bvX = -amount;
		bvY = 0.f;
		bvZ = 0.f;
		break;
	case dir::DOWN:
		bvX = 0;
		bvY = -amount;
		bvZ = 0.f;
		break;
	case dir::UP:
		bvX = 0.f;
		bvY = amount;
		bvZ = 0.f;
		break;
	}

	float px, py , pz;


	Player.transform.getTransform(px, py, pz);

	float vx, vy, vz;
	Player.getVelocity(vx, vy, vz);
	

	bvX += vx;
	bvY += vy;
	bvZ += vz;
	addObj(new Tear(),px, py, pz, 0.7, 0.7,0.7, bvX, bvY,bvZ,KIND_BULLET,BULLET_HP,true);
}


bool SceneManager::collide(Rect& a, Rect& b)
{
	if (a.max_x < b.min_x) return false;
	if (a.max_y < b.min_y) return false;
	if (a.min_x > b.max_x) return false;
	if (a.min_y > b.max_y) return false;

	return true;
}



bool SceneManager::collide(Box& a, Box& b)
{
	if (a.max_x < b.min_x) return false;
	if (a.max_y < b.min_y) return false;
	if (a.max_z < b.min_z) return false;
	if (a.min_x > b.max_x) return false;
	if (a.min_y > b.max_y) return false;
	if (a.min_z > b.max_z) return false;

	return true;
}

void SceneManager::onSceneChange(int i)
{

	for (int i = 0; i < CST::kMaxObj; ++i) {
		if(nullptr!= this->poolOfObjects[this->current_scene_number][i])	this->poolOfObjects[this->current_scene_number][i]->exitDo();
	}
	this->current_scene_number = i;
	for (int i = 0; i < CST::kMaxObj; ++i) {
		if (nullptr != this->poolOfObjects[this->current_scene_number][i])	this->poolOfObjects[this->current_scene_number][i]->init();
	}
}
