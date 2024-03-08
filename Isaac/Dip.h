#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneDev1;

class Dip : public SpriteGo
{
protected:
	Animator animator;
	SceneDev1* sceneDev1 = nullptr;

	static std::string DipMove;

	float directionChangeTimer;

	sf::Vector2f velocity;
	sf::Vector2f direction;

	int damage;
	float attackInterval;

	int maxHp = 50;
	int hp;
	float speed = 100.f;

	bool isAlive = true;
public:
	Dip(const std::string& name = "");
	~Dip() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void OnDamage(int damage);
	void OnDie();
};

