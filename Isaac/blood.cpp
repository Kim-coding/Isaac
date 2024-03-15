#include "pch.h"
#include "blood.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"

blood::blood(const std::string& name)
	:SpriteGo(name)
{
}

blood::~blood()
{
}

void blood::BloodAttack(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
}

void blood::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bloodTear.png");
	SetOrigin(Origins::MC);
	hasHitBox = true;
}

void blood::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
}

void blood::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	if (sceneDev1 != nullptr)
	{
		if (!sceneDev1->IsInMap(position))
		{
			SetActive(false);
			sceneDev1->RemoveGo(this);
		}
	}
}

void blood::FixedUpdate(float dt)              //핏방울 - 플레이어 충돌 처리
{
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->OnDamage(damage);
		SetActive(false);
		sceneDev1->RemoveGo(this);
	}
}
