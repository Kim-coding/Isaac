#include "pch.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"
#include "Charger.h"
#include "SpriteGo.h"
#include "Dip.h"

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

sf::Vector2f SceneDev1::ClampByMap(const sf::Vector2f point)   //시작 방 바닥 경계검사
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
					sf::Vector2f pos;
					pos.x = (currentFloor->GetSize().x) * 2;
					pos.y = (currentFloor->GetSize().y) * 2;
					auto dip = new Dip("monster");
					dip->Init();
					dip->Reset();

					dip->SetPosition(pos);
					AddGo(dip);
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

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

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

	currentFloor = spriteGoBackgroundfloor;

	/////////////////////////////////
	for (int i = 0; i < 3; ++i)
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

	AddGo(new PlayerIsaac("Isaac"));
	for (int i = 0; i < 2; ++i)
	{
		AddGo(new Charger("monster"));
		AddGo(new Dip("monster"));
	}
	Scene::Init();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{
	Scene::Enter();
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

	for (auto& door : doors) {
		door->SetTexture(doorTexture);
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))  
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneTitle);
	}

}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}