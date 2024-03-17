#pragma once
#include "SpriteGo.h"
#include "PlayerIsaac.h"

class SceneDev1;

class blood : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;
	int damage = 0;

	static std::string tear;

	SceneDev1* sceneDev1 = nullptr;
	PlayerIsaac* player = nullptr;

public:
	blood(const std::string& name = "");
	~blood() override;

	void BloodAttack(const sf::Vector2f& dir, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

