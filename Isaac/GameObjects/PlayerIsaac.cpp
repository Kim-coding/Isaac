#include "pch.h"
#include "PlayerIsaac.h"
#include "Tears.h"
#include "SpriteGoEffect.h"
#include "SceneDev1.h"

std::string PlayerIsaac::IdleUp = "animators/IdleUP.csv";
std::string PlayerIsaac::IdleRight = "animators/IdleRight.csv";
std::string PlayerIsaac::IdleLeft = "animators/IdleLeft.csv";
std::string PlayerIsaac::IdleDown = "animators/IdleDown.csv";
std::string PlayerIsaac::MoveDown = "animators/MoveDown.csv";
std::string PlayerIsaac::MoveRight = "animators/MoveRight.csv";
std::string PlayerIsaac::MoveLeft = "animators/MoveLeft.csv";
std::string PlayerIsaac::MoveUp = "animators/MoveUp.csv";
std::string PlayerIsaac::DamageMove = "animators/DamegeMove.csv";

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
	hp = maxHp;

	SetScale({ 1.5,1.5 });

	animator.SetTarget(&sprite);

	clipInfos.push_back({ IdleDown, MoveLeft, false, Utils::GetNormal({-1,-1}) });
	clipInfos.push_back({ IdleDown, MoveUp, false, {0, -1} });
	clipInfos.push_back({ IdleDown, MoveRight, false, Utils::GetNormal({1,-1}) });

	clipInfos.push_back({ IdleDown, MoveLeft, false, {-1, 0} });
	clipInfos.push_back({ IdleDown, MoveRight, false, {1, 0} });

	clipInfos.push_back({ IdleDown, MoveLeft, false, Utils::GetNormal({-1,1}) });
	clipInfos.push_back({ IdleDown, MoveDown, false, {0, 1} });
	clipInfos.push_back({ IdleDown, MoveRight, false, Utils::GetNormal({1, 1}) });
	
	tearDirection = {                   //눈물 방향
		{sf::Keyboard::Left, {-1, 0}},
		{sf::Keyboard::Right, {1, 0}},
		{sf::Keyboard::Up, {0, -1}},
		{sf::Keyboard::Down, {0, 1}}
	};
	cryDirection =                      //눈물 방향에 따른 바라보는 방향 변경
	{
		{sf::Keyboard::Left, IdleLeft},
		{sf::Keyboard::Right, IdleRight},
		{sf::Keyboard::Up, IdleUp},
		{sf::Keyboard::Down, IdleDown }
	};


	hasHitBox = true;
}

void PlayerIsaac::Release()
{
	SpriteGo::Release();
}

void PlayerIsaac::Reset()
{
	animator.Play(IdleDown);
	SetOrigin(Origins::BC);
	SetFlipX(false);

	isAlive = true;
	currentClipInfo = clipInfos[6];
	hp = maxHp;

	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());

}

void PlayerIsaac::Update(float dt)
{
	if (!isAlive)
		return;

	animator.Update(dt);

	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);

	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)          
	{
		direction /= mag;
	}

	sf::Vector2f prevPos = position;
	sf::Vector2f pos = position + direction * speed * dt;

	if (sceneDev1->crashDoor(pos) && !timer /*&& !monsterCount*/)	//문과 충돌 //타이머 //몬스터 수 체크 후 0이면 충돌 가능
	{
		sceneDev1->nextRoom(pos);
		timer = 0.3f;
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


	for (auto& pair : cryDirection)
	{
		if (InputMgr::GetKey(pair.first))
		{
			animator.Play(pair.second);
		}
	}

	cryTimer += dt;
	for (auto& pair : tearDirection) //키 입력에 따른 공격방향
	{
		if (InputMgr::GetKey(pair.first) && cryTimer > cryInterval) 
		{
			isCrying = true;
			Cry(pair.second);
			cryTimer = 0;
		}
	}

	if (sceneDev1->crashMapobject(pos))
	{
		isRook = true;
	}
	else
	{
		isRook = false;
	}

	if (sceneDev1->crashMapobject(pos) && isRook)
	{
		pos = prevPos;
	}
	SetPosition(pos);
}

void PlayerIsaac::Cry(sf::Vector2f direction) 
{
	sf::Vector2f pos;            
	pos.x = position.x;
	pos.y = position.y - 30;

	Tears* tears = new Tears();
	tears->Init();
	tears->Reset();
	tears->SetPosition(pos);
	tears->Cry(direction, tearsSpeed, tearsDamage);
	sceneDev1->AddGo(tears);
}

void PlayerIsaac::OnDamage(int damage)
{
	if (!isAlive)
		return;

	hp -= damage;
	timer = 0.5f;

	animator.Play(DamageMove); 
	
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}

	SpriteGoEffect* effectBlood = new SpriteGoEffect();
	effectBlood->Init();
	effectBlood->SetOrigin(Origins::MC);
	effectBlood->SetTexture("graphics/blood.png");
	effectBlood->Reset();
	effectBlood->sortLayer = -1;
	effectBlood->sortOrder = 1;
	effectBlood->SetPosition(position);

	sceneDev1->AddGo(effectBlood);
}

void PlayerIsaac::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	sceneDev1->SetStatus(SceneDev1::Status::GameOver);
}
