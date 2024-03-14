#pragma once
#include "Scene.h"
#include "TextGo.h"

class SpriteGo;

class SceneIntro : public Scene
{
protected:
	SpriteGo* backGround;
	SpriteGo* startButton;
	SpriteGo* EditorButton;
	
	TextGo startText;
	TextGo mapEditor;

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

