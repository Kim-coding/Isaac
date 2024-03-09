#include "pch.h"
#include "AttackFly.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"
#include "PlayerIsaac.h"      //플레이어 추적

AttackFly::AttackFly(const std::string& name)
	:MonsterMgr(name, 30, 150.f)
{
}

AttackFly::~AttackFly()
{
}

void AttackFly::Init()
{
	MonsterMgr::Init();

	animator.SetTarget(&sprite);
	hasHitBox = true;
}

void AttackFly::Reset()
{
	MonsterMgr::Reset();
	animator.Play("animators/AttackFlyMove.csv");
	SetPosition({100,100});
	SetOrigin(Origins::MC);

	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
}

void AttackFly::Update(float dt)
{
	MonsterMgr::Update(dt);
	animator.Update(dt);

	direction = player->GetPosition() - position;
	float distance = Utils::Magnitude(direction);
	Utils::Normalize(direction);

	sf::Vector2f pos = position + direction * speed * dt;

	if (sceneDev1 != nullptr)
	{
		pos = sceneDev1->ClampByMap(pos);
	}
	SetPosition(pos);

}

void AttackFly::FixedUpdate(float dt)
{
	MonsterMgr::FixedUpdate(dt);

}