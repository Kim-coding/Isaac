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
    SetTexture("graphics/Dinga1.png");
	animator.SetTarget(&sprite);
	hasHitBox = true;

}

void Dinga::Reset()
{
	MonsterMgr::Reset();
    SetTexture("graphics/Dinga1.png");
	SetOrigin(Origins::MC);
	SetFlipX(false);
}

void Dinga::Update(float dt)
{
	MonsterMgr::Update(dt);
	animator.Update(dt);


 
    sf::Vector2f pos = position + direction * speed * dt;
    
    dashTimer += dt;
    if (dashTimer > 5)
    {
        isDash = true;
    }
    else
    {
        speed = 50;
        isDash = false;


        float randomDirectionX = (float)(rand() - RAND_MAX / 2) / (RAND_MAX / 2);    // -1.f ~ 1.f
        float randomDirectionY = (float)(rand() - RAND_MAX / 2) / (RAND_MAX / 2);

        if (directionChangeTimer <= 0)
        {
            direction.x = randomDirectionX;
            direction.y = randomDirectionY;

            directionChangeTimer = 3.f;
        }
        directionChangeTimer -= dt;
    }

    if (dashTimer > dashInterval)
    {
        dashTimer = 0.f;
        isDash = false;
    }

    if (isDash)
    {
        direction = player->GetPosition() - position;
        float distance = Utils::Magnitude(direction);
        Utils::Normalize(direction);
        speed = 250;
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

            isDash = false;
        }
        if (sceneDev1->crashMapobject(pos))  //게임 오브젝트 충돌
        {
            if (direction.x != 0)
            {
                direction.x *= -1;
            }
            if (direction.y != 0)
            {
                direction.y *= -1;
            }

            isDash = false;
        }
    }
    SetPosition(pos);
}

void Dinga::OnDie()
{
    animator.Play("animators/DingaMove.csv");

    MonsterMgr::OnDie();
}
