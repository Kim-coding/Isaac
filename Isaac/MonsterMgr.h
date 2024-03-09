#pragma once
#include "SpriteGo.h"
#include "PlayerIsaac.h"

class SceneDev1;
class Animator;

class MonsterMgr : public SpriteGo
{
protected:
	Animator animator;
	SceneDev1* sceneDev1 = nullptr;
	PlayerIsaac* player = nullptr;

	int maxHp;
	int hp;
	int damage;
	float speed;

	float AttackTimer;
	float AttackInterval = 1.f;

	bool isAlive = true;
public:
	MonsterMgr(const std::string& name,int maxHp, int damage, float speed);
	~MonsterMgr();

	virtual void Init() ;
	virtual void Release() ;
	virtual void Reset() ;
	virtual void Update(float dt) ;
	virtual void FixedUpdate(float dt) ;

	virtual void OnDamage(int damage);
	virtual void OnDie();
};

