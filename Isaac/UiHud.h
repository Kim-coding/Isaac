#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "PlayerIsaac.h"

class SceneDev1;

class UiHud : public GameObject
{
protected:
	sf::Vector2f referenceResolution = { 1000, 700 };
	sf::Vector2f resolution = referenceResolution;

	std::string formatFps = "FPS: ";

	SpriteGo imgHp;
	SpriteGo imgHp2;

	TextGo textFps;
	PlayerIsaac* player;
	SceneDev1* sceneDev1 = nullptr;

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResolution(const sf::Vector2f resolution);

	void SetMessage(const std::string& msg);
	void SetMessageActive(bool active);

	void SetFps(int fps);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

