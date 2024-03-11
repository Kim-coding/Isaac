#include "pch.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"
#include "Charger.h"
#include "SpriteGo.h"
#include "Dip.h"
#include "AttackFly.h"
#include "BoomFly.h"

SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

bool SceneDev1::IsInMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = currentFloor->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, currentFloor->GetSize());

	return rect.contains(point);
}

sf::Vector2f SceneDev1::ClampByMap(const sf::Vector2f point)   //방 바닥 경계검사
{
	sf::FloatRect rect = currentFloor->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, currentFloor->GetSize());

	return Utils::Clamp(point, rect);
}


bool SceneDev1::crashDoor(const sf::Vector2f point)
{
	if (!monsterList.empty()) 
		return false;            // 몬스터가 남아있다면 문과 충돌 X

	for (auto& door : doors)
	{ 
		sf::FloatRect rect = door->GetGlobalBounds();
		rect = Utils::ResizeRect(rect, door->GetSize());
		if (rect.contains(point)) 
		{
			return true; 
		}
	}
	return false; 
}



void SceneDev1::nextRoom(const sf::Vector2f point)
{
	for (auto& door : doors)
	{
		sf::FloatRect rect = door->GetGlobalBounds();
		rect = Utils::ResizeRect(rect, door->GetSize());
		if (rect.contains(point))
		{
			//충돌한 문 인덱스 찾기
			//인덱스번호 홀수 -> 시작방
			//인덱스/2 -> Rooms[인덱스/2]에 저장된 해당 방으로
			size_t doorIndex = std::distance(doors.begin(), std::find(doors.begin(), doors.end(), door));
			if (doorIndex % 2 == 1)
			{
				currentFloor = spriteGoBackgroundfloor;
				sf::Vector2f centerPosition = spriteGoBackgroundfloor->GetPosition() + (spriteGoBackgroundfloor->GetSize() / 2.0f);
				worldView.setCenter(centerPosition);
			}
			else
			{
				currentFloor = Rooms[doorIndex / 2];
				sf::Vector2f centerPosition = currentFloor->GetPosition() + (currentFloor->GetSize() / 2.0f);
				worldView.setCenter(centerPosition);

				if (currentFloor != spriteGoBackgroundfloor)     // 시작 방이 아닌 방에서 몬스터 생성
				{
					sf::Vector2f roomSize = currentFloor->GetSize();
					sf::Vector2f roomPosition = currentFloor->GetPosition();

					sf::Vector2f pos = roomPosition + (roomSize / 2.0f);

					Dip* dip = new Dip("monster");
					dip->Init();
					dip->Reset();
					dip->SetPosition(pos);
					AddGo(dip);
					
					Charger* charger = new Charger("monster");
					charger->Init();
					charger->Reset();
					charger->SetPosition(pos);
					AddGo(charger);

					BoomFly* boomFly = new BoomFly("monster");
					boomFly->Init();
					boomFly->Reset();
					boomFly->SetPosition(pos);
					AddGo(boomFly);


					AttackFly* attackFly = new AttackFly("monster");
					attackFly->Init();
					attackFly->Reset();
					attackFly->SetPosition(pos);
					AddGo(attackFly);
				}
				
			}

		}
	}

}




void SceneDev1::Init()
{
	doorPosition = {
		{0, { 0.f, -210.f}},
		{90, {380.f, 0.f}},
		{180, {0.f, 210.f}},
		{270, { -380.f, 0.f}}
	};
	nextDoorPosition = {
		{0, { 0.f, -440.f}},
		{90, {620.f, 0.f}},
		{180, {0.f, 440.f}},
		{270, { -620.f, 0.f}}
	};
	Room =
	{
		{0, {0, -650}},
		{1, {1000,0}},
		{2, {0, 650} },
		{3, {-1000,0}}
	};

	//방

	SpriteGo* spriteGoBackground = new SpriteGo("StartRoom");
	spriteGoBackground->SetTexture("graphics/StartRoom.png");
	spriteGoBackground->SetOrigin(Origins::MC);
	spriteGoBackground->SetScale({2,2});
	spriteGoBackground->SetPosition({ 0.f, 0.f });
	spriteGoBackground->sortLayer = -1;
	AddGo(spriteGoBackground);

	spriteGoBackgroundfloor = new SpriteGo("StartRoomFloor");
	spriteGoBackgroundfloor->SetTexture("graphics/StartRoomFloor.png");
	spriteGoBackgroundfloor->SetOrigin(Origins::MC);
	spriteGoBackgroundfloor->SetScale({ 2, 2 });
	spriteGoBackgroundfloor->SetPosition({ 0.f, 0.f });
	spriteGoBackgroundfloor->sortLayer = -1;
	AddGo(spriteGoBackgroundfloor);


	/////////////////////////////////
	int roomNum = Utils::RandomRange(1, 4);
	for (int i = 0; i < roomNum; ++i)
	{
		int rand = Utils::RandomRange(0, 4);              // 0, 1, 2, 3 선택
		sf::Vector2f doorpos = doorPosition[rand * 90];
		sf::Vector2f nextdoorpos = nextDoorPosition[rand * 90];
		sf::Vector2f Roompos = Room[rand];

		regularRoom = new SpriteGo("RegularRoom");
		regularRoom->SetTexture("graphics/Catacombs.png");
		regularRoom->SetOrigin(Origins::MC);
		regularRoom->SetScale({ 2, 2 });
		regularRoom->SetPosition(Roompos);
		regularRoom->sortLayer = -1;
		AddGo(regularRoom);

		regularRoomfloor = new SpriteGo("regularRoomfloor");
		regularRoomfloor->SetTexture("graphics/CatacombsFloor.png");
		regularRoomfloor->SetOrigin(Origins::MC);
		regularRoomfloor->SetScale({ 2, 2 });
		regularRoomfloor->SetPosition(Roompos);
		regularRoomfloor->sortLayer = -1;
		AddGo(regularRoomfloor);
		Rooms.push_back(regularRoomfloor);

		door = new SpriteGo("door");
		door->SetTexture("graphics/door.png");
		door->SetOrigin(Origins::BC);
		door->SetScale({ 2, 2 });
		door->SetRotation(rand * 90);
		door->SetPosition(doorpos);
		AddGo(door);
		doors.push_back(door);                          
	
		door = new SpriteGo("door");                       //생성된 문에 맞게 다음 문 생성.
		door->SetTexture("graphics/door.png");
		door->SetOrigin(Origins::BC);
		door->SetScale({ 2, 2 });
		door->SetRotation(rand * 90 + 180);
		door->SetPosition(nextdoorpos);
		AddGo(door);
		doors.push_back(door);
	}  
	player = new PlayerIsaac("Isaac");
	player->sortLayer = 1;
	AddGo(player);

	Scene::Init();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{
	Scene::Enter();
	SetStatus(Status::Game);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	currentFloor = spriteGoBackgroundfloor;

	player->SetPosition({ 0.f,0.f });
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	
	FindGoAll("monster", monsterList, Layers::World);

	std::string doorTexture = monsterList.empty() ? "graphics/door.png" : "graphics/closeDoor.png";

	for (auto& door : doors) 
	{
		door->SetTexture(doorTexture);
	}

	switch (currStatus)
	{
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneDev1::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SetStatus(Status::Pause);
		return;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneTitle);
	}
	if (SCENE_MGR.GetDeveloperMode() && InputMgr::GetKeyDown(sf::Keyboard::Delete))
	{
		for (auto go : monsterList)
		{
			MonsterMgr* monster = dynamic_cast<MonsterMgr*>(go);
			monster->OnDie();
		}
	}
}

void SceneDev1::UpdateGameOver(float dt)
{
	for (auto obj : monsterList)    //플레이어가 사망 시 남아있는 몬스터 삭제  // 이전에는 생성된 몬스터가 죽지 않고 재 시작 시 시작방으로 넘어옴.
	{
		gameObjects.remove(obj);
		delete obj;
	}
	monsterList.clear();

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneDev1);
	}
}

void SceneDev1::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev1::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case SceneDev1::Status::Game:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case SceneDev1::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneDev1::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}
