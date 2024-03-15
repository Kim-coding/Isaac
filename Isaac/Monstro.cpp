#include "pch.h"
#include "Monstro.h"
#include "blood.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"

Monstro::Monstro(const std::string& name)
	:MonsterMgr(name,500,25,100)
{
}

Monstro::~Monstro()
{
}

void Monstro::TestInstance()
{
}

void Monstro::TestStaic()
{
}

void Monstro::Init()
{
	MonsterMgr::Init();
}

void Monstro::Reset()
{
	MonsterMgr::Reset();
	animator.ClearEvent();
	std::function<void()> funlnstance = std::bind(&Monstro::TestInstance, this);
	animator.AddEvent("animators/MonstroMove.csv",4,funlnstance);
	
	
	animator.Play("animators/MonstroMove.csv");
	SetOrigin(Origins::BC);
	SetScale({ 2,2 });
}

void Monstro::Update(float dt)
{
	MonsterMgr::Update(dt);

	float randomDirectionX = (float)(rand() - RAND_MAX / 2) / (RAND_MAX / 2);    // -1.f ~ 1.f
	float randomDirectionY = (float)(rand() - RAND_MAX / 2) / (RAND_MAX / 2);

	sf::Vector2f prevPos = position;

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

		if (sceneDev1->crashMapobject(pos))
		{
			isRock = true;
		}
		else
		{
			isRock = false;
		}
		if (isRock)
		{
			direction.x *= -1;
			direction.y *= -1;
		}
	}
	SetPosition(pos);

	////////////////// 공격 패턴 1 : 플레이어 방향으로 핏방울 분출/////////////////////////////// OK
	sf::Vector2f dir = player->GetPosition() - position;
	float distance = Utils::Magnitude(dir);
	Utils::Normalize(dir);

	AttackTimer += dt;
	if (AttackTimer > 1.f)
	{
		Fire(dir);
		AttackTimer = 0.f;
	}


}

void Monstro::FixedUpdate(float dt)
{
	MonsterMgr::FixedUpdate(dt);
}

void Monstro::Fire(sf::Vector2f dir)
{
	float spreadAngle = 45.0f; // 퍼짐 각도
	int numberOfTears = 12;
	float angleBetweenTears = spreadAngle / (numberOfTears - 1); // 눈물 사이의 각도

	for (int i = 0; i < numberOfTears; ++i)
	{
		float angle = -spreadAngle / 2 + angleBetweenTears * i; // 각 눈물의 각도
		sf::Vector2f newDir = Utils::Rotate(dir, angle); // Utils에 새로 추가한 함수

		blood* tears = new blood();
		tears->Init();
		tears->Reset();
		tears->SetPosition(position);
		tears->BloodAttack(newDir, 150 + rand() % 50 - 25, 10); // 약간의 랜덤 속도
		sceneDev1->AddGo(tears);
	}
}

void Monstro::OnDamage(int damage)
{
	MonsterMgr::OnDamage(damage);
}

void Monstro::OnDie()
{
	MonsterMgr::OnDie();
}
