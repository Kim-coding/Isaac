#pragma once
#include "SpriteGo.h"

class SceneDev1;
class Animator;

class MonsterMgr : public SpriteGo
{
protected:
	Animator animator;
	SceneDev1* sceneDev1 = nullptr;

	int maxHp;
	int hp;
	float speed;

	bool isAlive = true;
public:
	MonsterMgr(const std::string& name,int maxHp, float speed);
	~MonsterMgr();

	virtual void Init() ;
	virtual void Release() ;
	virtual void Reset() ;
	virtual void Update(float dt) ;
	virtual void FixedUpdate(float dt) ;

	virtual void OnDamage(int damage);
	virtual void OnDie();
};

