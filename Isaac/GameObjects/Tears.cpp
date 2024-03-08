#include "pch.h"
#include "Tears.h"
#include "Charger.h"
#include "Dip.h"
#include "SceneDev1.h"

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
		}
	}
}

void Tears::FixedUpdate(float dt)                       //阁胶磐客 面倒 贸府
{
	const std::list<GameObject*>& list = sceneDev1->GetMonsterList();

	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false);
			sceneDev1->RemoveGo(this);

			Charger* charger = dynamic_cast<Charger*>(go);
			if (charger != nullptr)
				charger->OnDamage(damage);

		}
		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false);
			sceneDev1->RemoveGo(this);

			Dip* dip = dynamic_cast<Dip*>(go);
			if (dip != nullptr)
				dip->OnDamage(damage);

		}
	}
}
