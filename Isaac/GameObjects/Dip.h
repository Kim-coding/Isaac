#pragma once
#include "MonsterMgr.h"

class Dip : public MonsterMgr
{
protected:
	float directionChangeTimer;

	sf::Vector2f direction;

	float attackInterval;
	bool isRock = false;
public:
	Dip(const std::string& name = "");
	~Dip() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void OnDie() override;
};

