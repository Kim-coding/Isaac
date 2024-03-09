#include "pch.h"
#include "MonsterMgr.h"
#include "Animator.h"
#include "SceneDev1.h"

MonsterMgr::MonsterMgr(const std::string& name, int maxHp, float speed)
	:SpriteGo(name), maxHp(maxHp), speed(speed)
{
}

MonsterMgr::~MonsterMgr()
{
}

void MonsterMgr::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);
	hasHitBox = true;
}

void MonsterMgr::Release()
{
}

void MonsterMgr::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
}

void MonsterMgr::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}

void MonsterMgr::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);
}

void MonsterMgr::OnDamage(int damage)
{
	if (!isAlive)
		return;

	hp -= damage;

	if (hp < 0)
	{
		OnDie();
	}
}

void MonsterMgr::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
	sceneDev1->RemoveGo(this);
}
