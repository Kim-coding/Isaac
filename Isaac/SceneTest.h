#pragma once
#include "Scene.h"

class SceneTest : public Scene
{
protected:


public:
	SceneTest(SceneIds id);
	virtual ~SceneTest();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);
};

