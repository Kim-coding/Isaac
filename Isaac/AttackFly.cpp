#include "pch.h"
#include "AttackFly.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"

AttackFly::AttackFly(const std::string& name)
	:MonsterMgr(name, 50, 10, 150.f)
{
}

AttackFly::~AttackFly()
{
}


void AttackFly::Reset()
{
	MonsterMgr::Reset();
	animator.Play("animators/AttackFlyMove.csv");
	SetPosition({100,100});
	SetOrigin(Origins::MC);

}

void AttackFly::Update(float dt)
{
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