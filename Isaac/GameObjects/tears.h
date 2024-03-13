#pragma once
#include "SpriteGo.h"

class SceneDev1;

class Tears : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;
	int damage = 0;

	static std::string tear;

	SceneDev1* sceneDev1;
public:
	Tears(const std::string& name = "");
	~Tears() override;

	void Cry(const sf::Vector2f& dir, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

