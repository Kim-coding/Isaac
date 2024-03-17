#pragma once
#include "MonsterMgr.h"
class Monstro : public MonsterMgr
{
protected:

	sf::Vector2f velocity;
	sf::Vector2f direction;

	float gravity = 100.f;       
	bool isGround = true;

	float AttackTimer = 0.f;
	float AttackInterval = 10.f;

	float directionChangeTimer;
	bool isRock = false;
	bool isFire = false;
public:
	Monstro(const std::string& name = "");
	~Monstro() override;

	void TestInstance();
	void TestStaic();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void Fire(sf::Vector2f dir);

	void OnDamage(int damage) override;
	void OnDie() override;

};

/*
이동 
1. 자유 이동
2. 점프 (점프 시 장애물 충돌 X)

공격 패턴
1. 플레이어가 있는 방향으로 핏방울 분출
2. 낮은 점프로 플레이어에게 접근
3. 높은 점프로 플레이어에게 접근 후 주변에 많은 양의 핏방울 분출
*/