#pragma once
#include "MonsterMgr.h"
#include "PlayerIsaac.h"

class AttackFly : public MonsterMgr
{
protected:
	PlayerIsaac* player = nullptr;

	sf::Vector2f direction;

public:
	AttackFly(const std::string& name = "");
	~AttackFly() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

