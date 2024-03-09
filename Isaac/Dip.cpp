#include "pch.h"
#include "Dip.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"
#include "PlayerIsaac.h"

std::string Dip::DipMove = "animators/DipMove.csv";

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
	animator.Play(DipMove);
	SetOrigin(Origins::MC);
	SetPosition({ -100.f,100.f });
	SetFlipX(false);

}

void Dip::Update(float dt)
{
    MonsterMgr::Update(dt);
    animator.Update(dt);
    int randomDirection = Utils::RandomRange(0, 4);

    SetScale({ 1.5, 1.5 });
    sf::Vector2f pos = position + direction * speed * dt;
    if (directionChangeTimer <= 0)
    {
        switch (randomDirection)
        {
        case 0: // 위쪽 방향
            direction.x = 0;
            direction.y = -1;
            animator.Play(DipMove);
            break;
        case 1: // 아래쪽 방향
            direction.x = 0;
            direction.y = 1;
            animator.Play(DipMove);
            break;
        case 2: // 왼쪽 방향
            direction.x = -1;
            direction.y = 0;
            SetFlipX(true);
            animator.Play(DipMove);
            break;
        case 3: // 오른쪽 방향
            direction.x = 1;
            direction.y = 0;
            SetFlipX(false);
            animator.Play(DipMove);
            break;
        }
        directionChangeTimer = 1.5f;
    }

    directionChangeTimer -= dt;

    if (sceneDev1 != nullptr)
    {
        pos = sceneDev1->ClampByMap(pos); //벽과 충돌
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
