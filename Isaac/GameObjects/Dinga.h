#pragma once
#include "MonsterMgr.h"
class Dinga : public MonsterMgr
{
protected:
	sf::Vector2f direction;
	float directionChangeTimer;

	bool isDash = false;
	float dashTimer = 0.f;
	float dashInterval = 5.f;

public:

	Dinga(const std::string& name = "");
	~Dinga() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	void OnDie() override;
};

