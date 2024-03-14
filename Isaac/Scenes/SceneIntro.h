#pragma once
#include "Scene.h"
#include "Animator.h"

class SceneIntro : public Scene
{
protected:
	Animator animator;

public:
	SceneIntro(SceneIds id);
	virtual ~SceneIntro();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

