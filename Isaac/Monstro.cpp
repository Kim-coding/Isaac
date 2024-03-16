#include "pch.h"
#include "Monstro.h"
#include "blood.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"

Monstro::Monstro(const std::string& name)
	:MonsterMgr(name,1000,20,130)
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
			if (pos.x == roomBound.x)  //y�� ���� �浹
				direction.y *= -1;
			if (pos.y == roomBound.y)  //x�� ���� �浹
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

	////////////////// ���� ���� 1 : �÷��̾� �������� �͹�� ����/////////////////////////////// OK
	sf::Vector2f dir = player->GetPosition() - position;
	float distance = Utils::Magnitude(dir);
	Utils::Normalize(dir);

	AttackTimer += dt;
	if (AttackTimer > 2.5f)
	{
		Fire(dir);
		AttackTimer = 0.f;
	}
	///////////////// ���� ���� 2 : �÷��̾� �������� ���� ���� �� �ڽ��� �ֺ��� �͹�� ����////////


}

void Monstro::FixedUpdate(float dt)
{
	MonsterMgr::FixedUpdate(dt);
}

void Monstro::Fire(sf::Vector2f dir)
{
	float spreadAngle = 65.0f; // ���� ����
	int numberOfTears = 15;
	float angleBetweenTears = spreadAngle / (numberOfTears - 1); // ���� ������ ����

	for (int i = 0; i < numberOfTears; ++i)
	{
		float angle = -spreadAngle / 2 + angleBetweenTears * i; // �� ������ ����
		sf::Vector2f newDir = Utils::Rotate(dir, angle); // Utils�� ���� �߰��� �Լ�

		blood* tears = new blood();
		tears->Init();
		tears->Reset();
		tears->SetPosition(position);
		tears->BloodAttack(newDir, 150 + rand() % 50 - 25, 10); // �ణ�� ���� �ӵ�
		sceneDev1->AddGo(tears);

		SOUND_MGR.PlaySfx("sound/Tears_Fire_2.mp3");
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
