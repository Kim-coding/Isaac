#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
protected:

public:
	SceneTitle(SceneIds id);
	~SceneTitle() override;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

