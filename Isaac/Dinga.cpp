#include "pch.h"
#include "Dinga.h"
#include "SceneDev1.h"
#include "SpriteGoEffect.h"
#include "PlayerIsaac.h"

Dinga::Dinga(const std::string& name)
	:MonsterMgr(name,200,25,100)
{
}

Dinga::~Dinga()
{
}

void Dinga::Init()
{
	MonsterMgr::Init();
	animator.SetTarget(&sprite);
	hasHitBox = true;

}

void Dinga::Reset()
{
	MonsterMgr::Reset();
	animator.Play("animators/DingaMove.csv");
	SetOrigin(Origins::MC);
	SetFlipX(false);
}

void Dinga::Update(float dt)
{
	MonsterMgr::Update(dt);
	animator.Update(dt);

    float randomDirectionX = Utils::RandomValue();    // 0.0f ~ 1.0f
    float randomDirectionY = Utils::RandomValue();

    sf::Vector2f pos = position + direction * speed * dt;
    if (directionChangeTimer <= 0)
    {
        direction.x = randomDirectionX;
        direction.y = randomDirectionY;

        directionChangeTimer = 3.f;
    }
    directionChangeTimer -= dt;
 

    
    dashTimer += dt;
    if (dashTimer > dashInterval)
    {
        isDash = true;
    }
    if (isDash)
    {
        direction = player->GetPosition() - position;
        float distance = Utils::Magnitude(direction);
        Utils::Normalize(direction);
        speed = 250;
        --dashTimer;
    }
    if (dashInterval < 0.f)
    {
        speed = 150;
        dashTimer = 0.f;
        isDash = false;
    }

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
