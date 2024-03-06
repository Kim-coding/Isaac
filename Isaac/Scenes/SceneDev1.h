#pragma once

class SpriteGo;

class SceneDev1 : public Scene
{
protected:
	SpriteGo* spriteGoBackground;
	SpriteGo* spriteGoBackgroundfloor;
public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	bool IsInMap(const sf::Vector2f& point);
	sf::Vector2f ClampByMap(const sf::Vector2f point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

