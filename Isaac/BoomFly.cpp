#include "pch.h"
#include "BoomFly.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"
#include "PlayerIsaac.h" 


BoomFly::BoomFly(const std::string& name)
	:MonsterMgr(name, 80, 30, 120.f)
{
}

BoomFly::~BoomFly()
{
}

void BoomFly::Init()
{
	MonsterMgr::Init();

    SetScale({2,2});
	animator.SetTarget(&sprite);
	hasHitBox = true;
}

void BoomFly::Reset()
{
	MonsterMgr::Reset();
	animator.Play("animators/BoomFlyMove.csv");
	SetPosition({ -100,-100 });
	SetOrigin(Origins::MC);

	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
}

void BoomFly::Update(float dt)
{
	MonsterMgr::Update(dt);
	animator.Update(dt);

    int randomDirection = Utils::RandomRange(0, 4);

    sf::Vector2f pos = position + direction * speed * dt;
    if (directionChangeTimer <= 0)
    {
        switch (randomDirection)
        {
        case 0:
            direction.x = 1;
            direction.y = -1;
            break;
        case 1:
            direction.x = 1;
            direction.y = 1;
            break;
        case 2:
            direction.x = -1;
            direction.y = 1;
            break;
        case 3:
            direction.x = -1;
            direction.y = -1;
            break;
        }
        directionChangeTimer = 5.f;
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

void BoomFly::FixedUpdate(float dt)
{
    MonsterMgr::FixedUpdate(dt);


    AttackTimer += dt;
    if (AttackTimer > AttackInterval)
    {
        if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
        {
            player->OnDamage(damage);
            AttackTimer = 0.f;
        }
    }
    
}

void BoomFly::OnDie()
{
    if (!isAlive)
        return;

    isAlive = false;
    SetActive(false);
    sceneDev1->RemoveGo(this);

    SpriteGoEffect* effectBlood = new SpriteGoEffect();
    effectBlood->Init();
    effectBlood->SetOrigin(Origins::MC);
    effectBlood->SetTexture("graphics/boomBlood.png");
    effectBlood->SetScale({2,2});
    effectBlood->Reset();
    effectBlood->sortLayer = -1;
    effectBlood->sortOrder = 1;
    effectBlood->SetPosition(position);
    effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));

    sceneDev1->AddGo(effectBlood);

    const float damageRadius = 100.0f; // 폭발 범위
    float distanceToPlayer = Utils::Distance(position, player->GetPosition());

    if (distanceToPlayer <= damageRadius)
    {
        int BoomDamage = damage * 2; 
        player->OnDamage(BoomDamage);
    }
}
