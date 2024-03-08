#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneDev1;

class Charger : public SpriteGo
{
protected:
	Animator animator;
	SceneDev1* sceneDev1 = nullptr;

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

	int maxHp = 100;
	int hp;
	float speed = 100.f;

	bool isAlive = true;

public:
	Charger(const std::string& name = "");
	~Charger() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void OnDamage(int damage);
	void OnDie();

};

