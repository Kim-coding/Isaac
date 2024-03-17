#include "pch.h"
#include "blood.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"
#include "Poop.h"

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

			SOUND_MGR.PlaySfx("sound/TearImpacts2.mp3");
		}
	}
}

void blood::FixedUpdate(float dt)              //핏방울 - 플레이어 충돌 처리
{
	const std::vector<SpriteGo*>& obj = sceneDev1->GetMapObject();

	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->OnDamage(damage);
		SetActive(false);
		sceneDev1->RemoveGo(this);

		SOUND_MGR.PlaySfx("sound/TearImpacts2.mp3");
	}

	for (auto& go : obj)
	{

		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			if (go->name == "rock")
			{
				SetActive(false);
				sceneDev1->RemoveGo(this);

			}

			if (go->name == "poop")
			{
				SetActive(false);
				sceneDev1->RemoveGo(this);

				auto obj = dynamic_cast<Poop*>(go);
				if (obj != nullptr)
				{
					obj->AddCount();
				}

			}

		}
	}
}
