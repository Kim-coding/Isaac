#include "pch.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"
#include "SpriteGo.h"

SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

bool SceneDev1::IsInMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = spriteGoBackgroundfloor->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, spriteGoBackground->GetSize());

	return rect.contains(point);
}

sf::Vector2f SceneDev1::ClampByMap(const sf::Vector2f point)   //시작 방 바닥 경계검사
{
	sf::FloatRect rect = spriteGoBackgroundfloor->GetGlobalBounds();      
	rect = Utils::ResizeRect(rect, spriteGoBackgroundfloor->GetSize());

	return Utils::Clamp(point, rect);
}

bool SceneDev1::crashDoor(const sf::Vector2f point)
{
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

void SceneDev1::nextRoom()
{
	//카메라 위치 조정
	//바닥 경계검사 대상 변경
}

void SceneDev1::Init()
{
	doorPosition = {
		{0, { 0.f, -210.f}},
		{90, {380.f, 0.f}},
		{180, {0.f, 210.f}},
		{270, { -380.f, 0.f}}
	};


	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	//방
	spriteGoBackground = new SpriteGo("StartRoom");
	spriteGoBackground->SetTexture("graphics/StartRoom.png");
	spriteGoBackground->SetOrigin(Origins::MC);
	spriteGoBackground->SetScale({2,2});
	spriteGoBackground->SetPosition({ 0.f, 0.f });
	//spriteGoBackground->SetRotation(90);
	AddGo(spriteGoBackground);

	spriteGoBackgroundfloor = new SpriteGo("StartRoomFloor");
	spriteGoBackgroundfloor->SetTexture("graphics/StartRoomFloor.png");
	spriteGoBackgroundfloor->SetOrigin(Origins::MC);
	spriteGoBackgroundfloor->SetScale({ 2, 2 });
	spriteGoBackgroundfloor->SetPosition({ 0.f, 0.f });
	//spriteGoBackgroundfloor->SetRotation(90);
	AddGo(spriteGoBackgroundfloor);

	///////////////////////////////////
	regularRoom = new SpriteGo("RegularRoom");
	regularRoom->SetTexture("graphics/Catacombs.png");
	regularRoom->SetOrigin(Origins::MC);
	regularRoom->SetScale({ 2, 2 });
	regularRoom->SetPosition({ -1000.f, 0.f });
	AddGo(regularRoom);

	regularRoomfloor = new SpriteGo("regularRoomfloor");
	regularRoomfloor->SetTexture("graphics/CatacombsFloor.png");
	regularRoomfloor->SetOrigin(Origins::MC);
	regularRoomfloor->SetScale({ 2, 2 });
	regularRoomfloor->SetPosition({ -1000.f, 0.f });
	AddGo(regularRoomfloor);

	regularRoom = new SpriteGo("RegularRoom");
	regularRoom->SetTexture("graphics/Catacombs.png");
	regularRoom->SetOrigin(Origins::MC);
	regularRoom->SetScale({ 2, 2 });
	regularRoom->SetPosition({ 1000.f, 0.f });
	AddGo(regularRoom);

	regularRoomfloor = new SpriteGo("regularRoomfloor");
	regularRoomfloor->SetTexture("graphics/CatacombsFloor.png");
	regularRoomfloor->SetOrigin(Origins::MC);
	regularRoomfloor->SetScale({ 2, 2 });
	regularRoomfloor->SetPosition({ 1000.f, 0.f });
	AddGo(regularRoomfloor);
	/////////////////////////////////
	
	for (int i = 0; i < 2; ++i)                           // 문 위치 랜덤 생성
	{
		int rand = Utils::RandomRange(0, 4);              // 0, 1, 2, 3 선택
		sf::Vector2f doorpos = doorPosition[rand * 90];

		door = new SpriteGo("door");
		door->SetTexture("graphics/door.png");
		door->SetOrigin(Origins::BC);
		door->SetScale({ 2, 2 });
		door->SetRotation(rand * 90);
		door->SetPosition(doorpos);
		AddGo(door);
		doors.push_back(door);                            //플레이어 - 문 충돌 처리를 하기 위함
	}

	AddGo(new PlayerIsaac());
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
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))  
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneTitle);
	}
}
