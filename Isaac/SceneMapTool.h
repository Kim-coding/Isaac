#pragma once
#include "Scene.h"
#include "TextGo.h"

class SpriteGo;

class SceneMapTool : public Scene
{
protected:
	SpriteGo* backGround;
	SpriteGo* button;
	TextGo buttonText;

	SpriteGo* rock;

	sf::Texture imageTexture;
	sf::Sprite imageSprite;

	bool isDragging = false;
public:
	SceneMapTool(SceneIds id);
	~SceneMapTool() override;

	void Init();
	void Release();

	std::wstring SelectFile();


	void Enter();
	void Exit();

	void Update(float dt);
	void SavePosition(const std::wstring& filePath);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);
};

