#pragma once
#include "SpriteGo.h"
class PlayerIsaac : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed = 500.f;

	int maxHp = 1000;
	int hp;
	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTime = 0.5f;
	float noDamageTimer = 0.f; public:

	PlayerIsaac(const std::string& name = "");
	~PlayerIsaac() override;

	void Init() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Cry();           //발사체 : 눈물 공격

	void OnDamage(int damage);
	void OnDie();

};

