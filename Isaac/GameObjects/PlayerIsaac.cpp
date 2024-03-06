#include "pch.h"
#include "PlayerIsaac.h"
#include "Tears.h"
#include "SceneDev1.h"

std::string PlayerIsaac::IdleDown = "animators/IdleDown.csv";
std::string PlayerIsaac::IdleSide = "animators/IdleSide.csv";
std::string PlayerIsaac::IdleUp = "animators/IdleUP.csv";
std::string PlayerIsaac::MoveDown = "animators/MoveDown.csv";
std::string PlayerIsaac::MoveSide = "animators/MoveSide.csv";
std::string PlayerIsaac::MoveUp = "animators/MoveUp.csv";

PlayerIsaac::PlayerIsaac(const std::string& name)
	:SpriteGo(name)
{
}

PlayerIsaac::~PlayerIsaac()
{
}

void PlayerIsaac::TestInstance()
{
}

void PlayerIsaac::TestStaic()
{
}

void PlayerIsaac::Init()
{
	SpriteGo::Init();

	SetScale({ 1.5,1.5 });

	animator.SetTarget(&sprite);

	clipInfos.push_back({ IdleSide, MoveSide, true, Utils::GetNormal({-1,-1}) });
	clipInfos.push_back({ IdleUp, MoveUp, false, {0, -1} });
	clipInfos.push_back({ IdleSide, MoveSide, false, Utils::GetNormal({1,-1}) });

	clipInfos.push_back({ IdleSide, MoveSide, true, {-1, 0} });
	clipInfos.push_back({ IdleSide, MoveSide, false, {1, 0} });

	clipInfos.push_back({ IdleSide, MoveSide, true, Utils::GetNormal({-1,1}) });
	clipInfos.push_back({ IdleDown, MoveDown, false, {0, 1} });
	clipInfos.push_back({ IdleSide, MoveSide, false, Utils::GetNormal({1, 1}) });

	cryTimer = cryInterval;

	hasHitBox = true;
}

void PlayerIsaac::Reset()
{
	animator.Play(IdleDown);
	SetOrigin(Origins::BC);
	SetPosition({0.f,0.f});
	SetFlipX(false);

	currentClipInfo = clipInfos[6];

	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void PlayerIsaac::Update(float dt)
{
	animator.Update(dt);

	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);

	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)          
	{
		direction /= mag;
	}

	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneDev1 != nullptr)
	{
		pos = sceneDev1->ClampByMap(pos);

	}
	SetPosition(pos);

	if (direction.x != 0.f || direction.y != 0.f)    
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),  
			[this](const ClipInfo& lhs, const ClipInfo& rhs)            
			{
				return Utils::Distance(direction, lhs.point) < Utils::Distance(direction, rhs.point);
			});
		currentClipInfo = *min;                                         
	}

	SetFlipX(currentClipInfo.filpX);                                   

	const std::string& clipId = (direction.x != 0.f || direction.y != 0.f) ?
		currentClipInfo.move : currentClipInfo.idle;    

	if (animator.GetCurrentCilpId() != clipId)
	{
		animator.Play(clipId);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		isCrying = true;
		left = true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		isCrying = true;
		Right = true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		isCrying = true;
		Up = true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		isCrying = true;
		Down = true;
	}
	
	if (InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right) ||
		InputMgr::GetKeyUp(sf::Keyboard::Up) || InputMgr::GetKeyUp(sf::Keyboard::Down))
	{
		isCrying = false;
		left = false;
		Right = false;
		Up = false;
		Down = false;

	}
	if (isCrying)
	{
		cryTimer += dt;
		if (cryTimer > cryInterval)
		{
			Cry();
			cryTimer = 0.f;
		}
	}
}

void PlayerIsaac::Cry() //АјАн
{
	if (left)
	{
		Tears* tears = new Tears();
		tears->Init();
		tears->Reset();

		tears->SetPosition(position);
		tears->Cry({-1,0}, tearsSpeed, tearsDamage);
		sceneDev1->AddGo(tears);
	}
	if (Right)
	{
		Tears* tears = new Tears();
		tears->Init();
		tears->Reset();

		tears->SetPosition(position);
		tears->Cry({ 1,0 }, tearsSpeed, tearsDamage);
		sceneDev1->AddGo(tears);
	}
	if (Up)
	{
		Tears* tears = new Tears();
		tears->Init();
		tears->Reset();

		tears->SetPosition(position);
		tears->Cry({ 0,-1 }, tearsSpeed, tearsDamage);
		sceneDev1->AddGo(tears);
	}
	if (Down)
	{
		Tears* tears = new Tears();
		tears->Init();
		tears->Reset();

		tears->SetPosition(position);
		tears->Cry({ 0,1 }, tearsSpeed, tearsDamage);
		sceneDev1->AddGo(tears);
	}
}

void PlayerIsaac::OnDamage(int damage)
{
	if (!isAlive || isNoDamage)
		return;

	hp -= damage;

	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void PlayerIsaac::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
}
