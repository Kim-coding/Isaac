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
�̵� 
1. ���� �̵�
2. ���� (���� �� ��ֹ� �浹 X)

���� ����
1. �÷��̾ �ִ� �������� �͹�� ����
2. ���� ������ �÷��̾�� ����
3. ���� ������ �÷��̾�� ���� �� �ֺ��� ���� ���� �͹�� ����
*/