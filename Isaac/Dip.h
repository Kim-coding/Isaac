#pragma once
#include "MonsterMgr.h"

class Dip : public MonsterMgr
{
protected:
	//static std::string DipMove;

	float directionChangeTimer;

	sf::Vector2f direction;

	int damage;
	float attackInterval;

public:
	Dip(const std::string& name = "");
	~Dip() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void OnDie() override;
};

