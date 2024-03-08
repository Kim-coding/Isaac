#include "pch.h"
#include "Monster.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"

std::string Monster::ChargerDashDown = "animators/ChargerDashDown.csv";
std::string Monster::ChargerDashSide = "animators/ChargerDashSide.csv";
std::string Monster::ChargerDashUp = "animators/ChargerDashUp.csv";
std::string Monster::ChargerMoveDown = "animators/ChargerMoveDown.csv";
std::string Monster::ChargerMoveSide = "animators/ChargerMoveSide.csv";
std::string Monster::ChargerMoveUp = "animators/ChargerMoveUp.csv";


Monster::Monster(const std::string& name)
	:SpriteGo(name)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	SpriteGo::Init();
    
	animator.SetTarget(&sprite);
    hasHitBox = true;
}

void Monster::Release()
{
	SpriteGo::Release();

}

void Monster::Reset()
{
	SpriteGo::Reset();
	animator.Play(ChargerMoveDown);
	SetOrigin(Origins::MC);
	SetPosition({ 100.f,100.f });
	SetFlipX(false);

    hp = maxHp;

    sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void Monster::Update(float dt)
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
        default:
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

void Monster::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

}

void Monster::OnDamage(int damage)
{
    if (!isAlive)
        return;

    hp -= damage;

    if (hp < 0)
    {
        OnDie();
    }
}

void Monster::OnDie()
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
