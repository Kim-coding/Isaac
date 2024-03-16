#include "pch.h"
#include "MonsterMgr.h"
#include "Animator.h"
#include "SceneDev1.h"

MonsterMgr::MonsterMgr(const std::string& name, int maxHp, int damage, float speed)
	:SpriteGo(name), maxHp(maxHp), damage(damage), speed(speed)
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
	hp = maxHp;
	isAlive = true;

	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
}

void MonsterMgr::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
}

void MonsterMgr::FixedUpdate(float dt)
{
	AttackTimer += dt;
	if (AttackTimer > AttackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnDamage(damage);
			AttackTimer = 0.f;
		}
	}
	
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
