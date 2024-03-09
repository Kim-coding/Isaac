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
	:MonsterMgr(name, 100, 100.f)
{
}

Charger::~Charger()
{
}

void Charger::Init()
{
    MonsterMgr::Init();
    
	animator.SetTarget(&sprite);
    SetScale({ 3, 3 });
    hasHitBox = true;
}


void Charger::Reset()
{
    MonsterMgr::Reset();
	animator.Play(ChargerMoveDown);
	SetOrigin(Origins::MC);
	SetFlipX(false);


    player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
}

void Charger::Update(float dt)
{
    MonsterMgr::Update(dt);
	//animator.Update(dt);
	int randomDirection = Utils::RandomRange(0, 4);
	
    sf::Vector2f pos = position + direction * speed * dt;
    if (!isDash && directionChangeTimer <= 0)
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

    sf::Vector2f toPlayer = player->GetPosition() - GetPosition();
    sf::Vector2f normalizedToPlayer = Utils::GetNormal(toPlayer);

    float angleCos = direction.x * normalizedToPlayer.x + direction.y * normalizedToPlayer.y;

    if (angleCos > 0.95f)
    {
        isDash = true;
        speed = 500;

        if (direction.y == -1)
        {
            animator.Play(ChargerDashUp);
        }
        else if(direction.y == 1)
        {
            animator.Play(ChargerDashDown);
        }
        else
        {
            animator.Play(ChargerDashSide);
        }
    }

    if (isDash)
    {
        dashTimer += dt;
        if (dashTimer > dashInterval)
        {
            speed /= 10;
            isDash = false;
            dashTimer = 0.f;
        }
    }

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
