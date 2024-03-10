#include "pch.h"
#include "Dip.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"
#include "PlayerIsaac.h"

//std::string Dip::DipMove = "animators/DipMove.csv";

Dip::Dip(const std::string& name)
	:MonsterMgr(name, 40, 5, 100.f)
{
}

Dip::~Dip()
{
}

void Dip::Init()
{
    MonsterMgr::Init();

	animator.SetTarget(&sprite);
	hasHitBox = true;
}

void Dip::Reset()
{
    MonsterMgr::Reset();
	animator.Play("animators/DipMove.csv");
	SetOrigin(Origins::MC);
	SetPosition({ -100.f,100.f });
	SetFlipX(false);

}

void Dip::Update(float dt)
{
    MonsterMgr::Update(dt);
    animator.Update(dt);
    float randomDirectionX = Utils::RandomValue();    // 0.0f ~ 1.0f
    float randomDirectionY = Utils::RandomValue();

    SetScale({ 1.5, 1.5 });
    sf::Vector2f pos = position + direction * speed * dt;
    if (directionChangeTimer <= 0)
    {
        direction.x = randomDirectionX;
        direction.y = randomDirectionY;

        directionChangeTimer = 2.f;
    }
    directionChangeTimer -= dt;

    if (sceneDev1 != nullptr)
    {
        sf::Vector2f roomBound = sceneDev1->ClampByMap(pos);

        if (pos != roomBound)
        {
            if (pos.x == roomBound.x)  //y축 경계와 충돌
                direction.y *= -1;
            if (pos.y == roomBound.y)  //x축 경계와 충돌
                direction.x *= -1;

        }
    }
    SetPosition(pos);
}

void Dip::FixedUpdate(float dt)
{
    MonsterMgr::FixedUpdate(dt);
}

void Dip::OnDie()
{
    if (!isAlive)
        return;

    isAlive = false;
    SetActive(false);
    sceneDev1->RemoveGo(this);

    SpriteGoEffect* effectBlood = new SpriteGoEffect();
    effectBlood->Init();
    effectBlood->SetOrigin(Origins::MC);
    effectBlood->SetTexture("graphics/dipBlood.png");
    effectBlood->Reset();
    effectBlood->sortLayer = -1;
    effectBlood->sortOrder = 1;
    effectBlood->SetPosition(position);
    effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));

    sceneDev1->AddGo(effectBlood);
}
