#pragma once
#include "MonsterMgr.h"
#include "Animator.h"

class Charger : public MonsterMgr
{
protected:

	static std::string ChargerDashDown;
	static std::string ChargerDashSide;
	static std::string ChargerDashUp;
	static std::string ChargerMoveDown;
	static std::string ChargerMoveSide;
	static std::string ChargerMoveUp;


	float directionChangeTimer;

	sf::Vector2f velocity;
	sf::Vector2f direction;

	int damage;
	float attackInterval;


	float dashTimer = 0.f;
	float dashInterval = 2.f;

	bool isDash = false;

public:
	Charger(const std::string& name = "");
	~Charger() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void OnDie() override;

};

