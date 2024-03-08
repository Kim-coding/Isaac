#pragma once
#include "SpriteGo.h"

class SceneDev1;
class Animator;

class MonsterMgr : public SpriteGo
{
protected:
	bool isAlive = true;

	int maxHp;
	int hp;

	Animator animator;
	SceneDev1* sceneDev1;
public:
	MonsterMgr(const std::string& name = "");
	~MonsterMgr() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void FixedUpdate(float dt) override;

	virtual void OnDamage(int damage);
	virtual void OnDie();
};

