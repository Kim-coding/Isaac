#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneDev1;

class Monster : public SpriteGo
{
public:
	enum class Types
	{
		Dinga,
		Dip,
		Charger,
		Fatty,
		Monstro,
		Dingle,
	};
	

protected:
	int damage;
	float attackInterval;

	int maxHp;
	int hp;
	float speed;

public:
	Monster(const std::string& name = "");
	~Monster() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage);
	void OnDie();

};

