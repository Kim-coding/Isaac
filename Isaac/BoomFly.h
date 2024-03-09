#pragma once
#include "MonsterMgr.h"
#include "PlayerIsaac.h"

class BoomFly : public MonsterMgr
{
protected:
	PlayerIsaac* player = nullptr;

	sf::Vector2f direction;
	float directionChangeTimer;

public:
	BoomFly(const std::string& name = "");
	~BoomFly() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void OnDie() override;
};

