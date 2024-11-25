#pragma once
#include "SceneManager.h"
#include "Renderer.h"
#include "Sound.h"
static SceneManager* SceneMGR;
SceneManager* getSceneMGR();
static Renderer *renderer;
Renderer* getRenderer();

static Sound* soundMGR;
Sound* getSoundMGR();
