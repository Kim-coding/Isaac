#include "pch.h"
#include "PlayerIsaac.h"
#include "Tears.h"
#include "SceneDev1.h"

std::string PlayerIsaac::IdleUp = "animators/IdleUP.csv";
std::string PlayerIsaac::IdleSide = "animators/IdleSide.csv";
std::string PlayerIsaac::IdleDown = "animators/IdleDown.csv";
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

	clipInfos.push_back({ IdleDown, MoveSide, true, Utils::GetNormal({-1,-1}) });
	clipInfos.push_back({ IdleDown, MoveUp, false, {0, -1} });
	clipInfos.push_back({ IdleDown, MoveSide, false, Utils::GetNormal({1,-1}) });

	clipInfos.push_back({ IdleDown, MoveSide, true, {-1, 0} });
	clipInfos.push_back({ IdleDown, MoveSide, false, {1, 0} });

	clipInfos.push_back({ IdleDown, MoveSide, true, Utils::GetNormal({-1,1}) });
	clipInfos.push_back({ IdleDown, MoveDown, false, {0, 1} });
	clipInfos.push_back({ IdleDown, MoveSide, false, Utils::GetNormal({1, 1}) });

	cryTimer = cryInterval;

	directionMap = {
		{sf::Keyboard::Left, {-1, 0}},
		{sf::Keyboard::Right, {1, 0}},
		{sf::Keyboard::Up, {0, -1}},
		{sf::Keyboard::Down, {0, 1}}
	};



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
	if (sceneDev1->crashDoor(pos) && !timer /*&& !monsterCount*/)	//문과 충돌 //타이머 //몬스터 수 체크 후 0이면 충돌 가능
	{
		sceneDev1->nextRoom();
		timer = 0.3;
		doorCrash = true;
	}
	else if (sceneDev1 != nullptr && !doorCrash)  //벽과 충돌
	{
		pos = sceneDev1->ClampByMap(pos);
		timer -= dt;
	}
	else
	{
		doorCrash = false;
	}
	SetPosition(pos);

	if (timer < 0.f) 
	{
		timer = 0.f;
	}



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

	for (auto& pair : directionMap) //키 입력에 따른 공격방향
	{
		if (InputMgr::GetKeyDown(pair.first)) 
		{
			isCrying = true;
			Cry(pair.second);
		}
		if (InputMgr::GetKeyUp(pair.first))
		{
			isCrying = false;
		}
	}
}

void PlayerIsaac::Cry(sf::Vector2f direction) 
{
	sf::Vector2f pos;            
	pos.x = position.x;
	pos.y = position.y - 30;

	//animator.Play();

	Tears* tears = new Tears();
	tears->Init();
	tears->Reset();
	tears->SetPosition(pos);
	tears->Cry(direction, tearsSpeed, tearsDamage);
	sceneDev1->AddGo(tears);
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
