#pragma once
#include "Dependencies\glew.h"
#include "Const.h"
#include "Collider.h"
class Renderer;
class Object;

class SceneManager
{



	Renderer* renderer;
	GLuint  back_ground_texture;
	GLuint  main_char_texture;
	GLuint  shading_room_texture;
	//GLuint  snow_texture;
	GLuint  shadow;
	GLuint  shadowTexture;//DrawTextureRectHeight
	GLuint  forBuilding;//DrawTextureRectHeight

	Object* credit_scene;
	Object* poolOfObjects[GAMEOVER+1][CST::kMaxObj];
	static unsigned int current_scene_number;

	float Timer = 0.0f;
	float TimerForAnim = 0.0;
	int Frame = 0;

	int objNumber = 0;


public:
	GLuint  snow_texture;
	SceneManager();
	~SceneManager();
	
	void init();

	void renderScene();
	void update();
	void doCollisionTest();
	void processCollision();
	void addObj(Object*,float, float, float, float, float, float, float, float, float, int, int, bool,int sceneNumber = current_scene_number);
	void deleteObject(int);
	void fetchEmptySlot(int &,int);
	void garbageCollector(void);

	void shoot(int shootid, Object& player);
	

	bool collide(Rect&, Rect&);
	bool collide(Box&, Box&);


	void onSceneChange(int);
};

