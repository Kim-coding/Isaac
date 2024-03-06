#pragma once
#include "SpriteGo.h"
class tears : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;
	int damage = 0;

public:
	tears(const std::string& name = "");
	~tears() override;

	void Cry(const sf::Vector2f& dir, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

