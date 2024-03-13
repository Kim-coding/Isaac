#pragma once
#include "Scene.h"

class SpriteGo;

class SceneTitle : public Scene
{
protected:
	SpriteGo* spriteTitle;

	float changSceneTime = 2.f;
	float timer = 0.f;
public:
	SceneTitle(SceneIds id);
	~SceneTitle() override;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

