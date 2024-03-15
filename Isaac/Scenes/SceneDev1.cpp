#include "pch.h"
#include "SceneDev1.h"
#include "PlayerIsaac.h"
#include "Charger.h"
#include "SpriteGo.h"
#include "Dip.h"
#include "AttackFly.h"
#include "BoomFly.h"
#include "Dinga.h"
#include "Rock.h"
#include "Web.h"
#include "Poop.h"
#include "Monstro.h"
#include "UiHud.h"
#include <filesystem>
#include <random>

SceneDev1::SceneDev1(SceneIds id)
	: Scene(id)
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

sf::Vector2f SceneDev1::ClampByMap(const sf::Vector2f point)
{
	sf::FloatRect rect = currentFloor->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, currentFloor->GetSize());

	return Utils::Clamp(point, rect);
}


bool SceneDev1::crashDoor(const sf::Vector2f point)
{
	if (!monsterList.empty()) 
		return false;

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

bool SceneDev1::crashMapobject(const sf::Vector2f point)
{
	for (auto& obj : mapObjects)
	{
		if (obj->name == "rock")
		{
			sf::FloatRect rects = obj->GetGlobalBounds();
			rects = Utils::ResizeRect(rects, obj->GetSize());
			if (rects.contains(point))
			{
				return true;
			}
		}
		if (obj->name == "poop")
		{
			auto go = dynamic_cast<Poop*>(obj);
			if (go->GetCount() > 6)
			{
				return false;
			}

			sf::FloatRect rects = obj->GetGlobalBounds();
			rects = Utils::ResizeRect(rects, obj->GetSize());
			if (rects.contains(point))
			{
				return true;
			}
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
				for (auto obj : mapObjects)
				{
					gameObjects.remove(obj);
					delete obj;
				}
				mapObjects.clear();
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

					for (auto obj : mapinfo.objectList)
					{
						if (obj.name == "rock")
						{
							Rock* mapObj = new Rock("rock");
							mapObj->SetTexture("graphics/Rock.png");
							mapObj->SetOrigin(Origins::MC);
							mapObj->SetPosition(pos + obj.position);
							AddGo(mapObj);
							mapObjects.push_back(mapObj);
						}
						if (obj.name == "web")
						{
							Web* web = new Web("web");
							web->SetTexture("graphics/web.png");
							web->SetOrigin(Origins::MC);
							web->SetPosition(pos + obj.position);
							AddGo(web);
							mapObjects.push_back(web);
						}
						if (obj.name == "poop")
						{
							Poop* poop = new Poop("poop");
							poop->SetTexture("graphics/Poop1.png");
							poop->SetOrigin(Origins::MC);
							poop->SetPosition(pos + obj.position);
							AddGo(poop);
							mapObjects.push_back(poop);
						}
					}

					for (auto obj : mapinfo.monsterList)
					{
						if (obj.name == "attackfly")
						{
							AttackFly* attackFly = new AttackFly("monster");
							attackFly->Init();
							attackFly->Reset();
							attackFly->SetPosition(pos + obj.position);
							AddGo(attackFly);
						}
						if (obj.name == "dip")
						{
							Dip* dip = new Dip("monster");
							dip->Init();
							dip->Reset();
							dip->SetPosition(pos + obj.position);
							AddGo(dip);
						}
						if (obj.name == "charger")
						{
							Charger* charger = new Charger("monster");
							charger->Init();
							charger->Reset();
							charger->SetPosition(pos + obj.position);
							AddGo(charger);
						}
						if (obj.name == "dinga")
						{
							Dinga* dinga = new Dinga("monster");
							dinga->Init();
							dinga->Reset();
							dinga->SetPosition(pos + obj.position);
							AddGo(dinga);
						}
						if (obj.name == "boomfly")
						{
							BoomFly* boomFly = new BoomFly("monster");
							boomFly->Init();
							boomFly->Reset();
							boomFly->SetPosition(pos + obj.position);
							AddGo(boomFly);
						}
					}
					
				}
				
			}

		}
	}

}

void SceneDev1::LoadRandomMap(/*MapInfo& mapInfo*/)
{
	namespace fs = std::filesystem;

	std::string path = "map/";

	// map 폴더 내의 모든 .csv 파일
	for (const auto& entry : fs::directory_iterator(path)) 
	{
		if (entry.path().extension() == ".csv") 
		{
			csvFiles.push_back(entry.path().string()); // CSV 파일 경로 저장
		}
	}

	if (!csvFiles.empty()) 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, csvFiles.size() - 1);

		int index = distrib(gen);
		mapinfo.LoadFromFile(csvFiles[index]); // 랜덤한 CSV 파일 로드
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


	////////////////////////////////////////

	LoadRandomMap();

	//방
	SpriteGo* spriteGoBackground = new SpriteGo("StartRoom");
	spriteGoBackground->SetTexture("graphics/StartRoom.png");
	spriteGoBackground->SetOrigin(Origins::MC);
	spriteGoBackground->SetPosition({ 0.f, 0.f });
	spriteGoBackground->sortLayer = -1;
	AddGo(spriteGoBackground);

	spriteGoBackgroundfloor = new SpriteGo("StartRoomFloor");
	spriteGoBackgroundfloor->SetTexture("graphics/StartRoomFloor.png");
	spriteGoBackgroundfloor->SetOrigin(Origins::MC);
	spriteGoBackgroundfloor->SetPosition({ 0.f, 0.f });
	spriteGoBackgroundfloor->sortLayer = -1;
	AddGo(spriteGoBackgroundfloor);
	
	///////////////////////////////////////////
	int roomNum = Utils::RandomRange(1, 4);
	for (int i = 0; i < roomNum; ++i)
	{
		RoomInfo roomInfo;

		//LoadRandomMap(roomInfo.mapInfo);

		int attempts = 0;
		bool positionFound = false;
		int rand = 0;

		while (!positionFound && attempts < 10)
		{
			rand = Utils::RandomRange(0, 4);
			if (usedPositions.find(rand) == usedPositions.end())
			{
				positionFound = true;
				usedPositions.insert(rand);
			}
			attempts++;
		}

		if (!positionFound)
		{
			std::cout << "Available positions exhausted." << std::endl;
			break;
		}

		sf::Vector2f doorpos = doorPosition[rand * 90];
		sf::Vector2f nextdoorpos = nextDoorPosition[rand * 90];
		sf::Vector2f Roompos = Room[rand];

		regularRoom = new SpriteGo("RegularRoom");
		regularRoom->SetTexture("graphics/Catacombs.png");
		regularRoom->SetOrigin(Origins::MC);
		regularRoom->SetPosition(Roompos);
		regularRoom->sortLayer = -1;
		AddGo(regularRoom);

		regularRoomfloor = new SpriteGo("regularRoomfloor");
		regularRoomfloor->SetTexture("graphics/CatacombsFloor.png");
		regularRoomfloor->SetOrigin(Origins::MC);
		regularRoomfloor->SetPosition(Roompos);
		regularRoomfloor->sortLayer = -1;
		AddGo(regularRoomfloor);
		Rooms.push_back(regularRoomfloor);

		door = new SpriteGo("door");
		door->SetTexture("graphics/door.png");
		door->SetOrigin(Origins::BC);
		door->SetRotation(rand * 90);
		door->SetPosition(doorpos);
		AddGo(door);
		doors.push_back(door);                          
	
		door = new SpriteGo("door");                       //생성된 문에 맞게 다음 문 생성.
		door->SetTexture("graphics/door.png");
		door->SetOrigin(Origins::BC);
		door->SetRotation(rand * 90 + 180);
		door->SetPosition(nextdoorpos);
		AddGo(door);
		doors.push_back(door);

		//roomsInfo.push_back(roomInfo);
	}  
	player = new PlayerIsaac("Isaac");
	player->sortLayer = 1;
	AddGo(player);

	AddGo(new Monstro("monster"));  //보스 몬스터 : monstro 테스트

	uiHud = new UiHud("UI HUD");
	AddGo(uiHud, Layers::Ui);

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
		player->ReSetHp();

		for (auto go : monsterList)
		{
			MonsterMgr* monster = dynamic_cast<MonsterMgr*>(go);
			monster->OnDie();
		}
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
	for (auto obj : monsterList)    //플레이어가 사망 시 남아있는 몬스터 & 오브젝트 삭제 
	{
		gameObjects.remove(obj);
		delete obj;
	}
	monsterList.clear();
	
	for (auto obj : mapObjects)
	{
		gameObjects.remove(obj);
		delete obj;
	}
	mapObjects.clear();

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		player->ReSetHp();
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
	GameOverText.Draw(window);
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
