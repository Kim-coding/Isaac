#include "pch.h"
#include "Tears.h"
#include "SceneDev1.h"
#include "MonsterMgr.h"
#include "Poop.h"

Tears::Tears(const std::string& name)
{
}

Tears::~Tears()
{
}

void Tears::Cry(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;
}

void Tears::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/tear.png");
	SetOrigin(Origins::MC);
	//SetScale({ 0.4,0.4 });
	hasHitBox = true;
}

void Tears::Reset()
{
	SpriteGo::Reset();

	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void Tears::Update(float dt)
{
	SetPosition(position + direction * speed * dt);     // 甘苞 面倒 贸府
	if (sceneDev1 != nullptr)                       
	{
		if (!sceneDev1->IsInMap(position))
		{
			SetActive(false);
			sceneDev1->RemoveGo(this);

			SOUND_MGR.PlaySfx("sound/TearImpacts0.mp3");
		}
	}
}

void Tears::FixedUpdate(float dt)                       //阁胶磐客 面倒 贸府, mapobject客 面倒 贸府
{
	const std::list<GameObject*>& list = sceneDev1->GetMonsterList();
	const std::vector<SpriteGo*>& obj = sceneDev1->GetMapObject();

	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false);
			sceneDev1->RemoveGo(this);

			auto monster = dynamic_cast<MonsterMgr*>(go);
			if (monster != nullptr)
				monster->OnDamage(damage);
		}
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
			
			SOUND_MGR.PlaySfx("sound/TearImpacts0.mp3");
		}
	}
	
}
