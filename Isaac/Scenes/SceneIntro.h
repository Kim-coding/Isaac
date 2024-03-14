#pragma once
#include "Scene.h"

class SceneIntro : public Scene
{
protected:

public:
	SceneIntro(SceneIds id);
	virtual ~SceneIntro();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

