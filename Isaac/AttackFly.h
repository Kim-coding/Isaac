#pragma once
#include "MonsterMgr.h"

class AttackFly : public MonsterMgr
{
protected:
	sf::Vector2f direction;

public:
	AttackFly(const std::string& name = "");
	~AttackFly() override;

	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

