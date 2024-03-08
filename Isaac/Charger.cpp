#include "pch.h"
#include "Charger.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"
#include "PlayerIsaac.h"      //플레이어가 몬스터 진행 방향에 있으면 dash

std::string Charger::ChargerDashDown = "animators/ChargerDashDown.csv";
std::string Charger::ChargerDashSide = "animators/ChargerDashSide.csv";
std::string Charger::ChargerDashUp = "animators/ChargerDashUp.csv";
std::string Charger::ChargerMoveDown = "animators/ChargerMoveDown.csv";
std::string Charger::ChargerMoveSide = "animators/ChargerMoveSide.csv";
std::string Charger::ChargerMoveUp = "animators/ChargerMoveUp.csv";


Charger::Charger(const std::string& name)
	:SpriteGo(name)
{
}

Charger::~Charger()
{
}

void Charger::Init()
{
	SpriteGo::Init();
    
	animator.SetTarget(&sprite);
    hasHitBox = true;
}

void Charger::Release()
{
	SpriteGo::Release();

}

void Charger::Reset()
{
	SpriteGo::Reset();
	animator.Play(ChargerMoveDown);
	SetOrigin(Origins::MC);
	SetPosition({ 100.f,100.f });
	SetFlipX(false);

    hp = maxHp;

    sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void Charger::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);
	int randomDirection = Utils::RandomRange(0, 4);
	
    SetScale({ 3, 3 });
    sf::Vector2f pos = position + direction * speed * dt;
    if (directionChangeTimer <= 0)
    {
        switch (randomDirection)
        {
        case 0: // 위쪽 방향
            direction.x = 0;
            direction.y = -1;
            animator.Play(ChargerMoveUp);
            break;
        case 1: // 아래쪽 방향
            direction.x = 0;
            direction.y = 1;
            animator.Play(ChargerMoveDown);
            break;
        case 2: // 왼쪽 방향
            direction.x = -1;
            direction.y = 0;
            SetFlipX(true);
            animator.Play(ChargerMoveSide);
            break;
        case 3: // 오른쪽 방향
            direction.x = 1;
            direction.y = 0;
            SetFlipX(false);
            animator.Play(ChargerMoveSide);
            break;
        }
        directionChangeTimer = 1.f;
    }

    directionChangeTimer -= dt;
	
    if (sceneDev1 != nullptr) 
    {
        pos = sceneDev1->ClampByMap(pos); //벽과 충돌
    }
    SetPosition(pos);
}

void Charger::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

}

void Charger::OnDamage(int damage)
{
    if (!isAlive)
        return;

    hp -= damage;

    if (hp < 0)
    {
        OnDie();
    }
}

void Charger::OnDie()
{
    if (!isAlive)
        return;

    isAlive = false;
    SetActive(false);
    sceneDev1->RemoveGo(this);

    SpriteGoEffect* effectBlood = new SpriteGoEffect();
    effectBlood->Init();
    effectBlood->SetOrigin(Origins::MC);
    effectBlood->SetTexture("graphics/blood.png");
    effectBlood->Reset();
    effectBlood->sortLayer = -1;
    effectBlood->sortOrder = 1;
    effectBlood->SetPosition(position);
    effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));

    sceneDev1->AddGo(effectBlood);
}
