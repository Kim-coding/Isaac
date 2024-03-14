#include "pch.h"
#include "SceneMapTool.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "rapidcsv.h"
#include "MapInfo.h"
#include <filesystem>

namespace fs = std::filesystem;

std::string SceneMapTool::ToRelativePath(const std::string& originalPath, const std::string& basePath) 
{
	fs::path relativePath = fs::relative(fs::path(originalPath), fs::path(basePath));
	return relativePath.string();
}

std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr)
{
	int strLength
		= WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1,
			nullptr, 0, nullptr, nullptr);

	std::string str(strLength, 0);

	WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, &str[0],
		strLength, nullptr, nullptr);

	return str;
}

SceneMapTool::SceneMapTool(SceneIds id)
	:Scene(id)
{
}

SceneMapTool::~SceneMapTool()
{
}

void SceneMapTool::Init()
{
	backGround = new SpriteGo("BackGround");
	backGround->SetTexture("graphics/background.png");
	backGround->SetOrigin(Origins::MC);
	backGround->SetPosition({ 0.f, 0.f });
	backGround->sortLayer = -1;
	AddGo(backGround);
	//////////////////button/////////////////////
	buttonFloor = new SpriteGo("button");
	buttonFloor->SetTexture("graphics/button.png");
	buttonFloor->SetOrigin(Origins::TL);
	buttonFloor->SetPosition({ -500.f, -350.f });
	AddGo(buttonFloor);

	buttonRoom = new SpriteGo("button");
	buttonRoom->SetTexture("graphics/button.png");
	buttonRoom->SetOrigin(Origins::TL);
	buttonRoom->SetPosition({ -340.f, -350.f });
	AddGo(buttonRoom);
	//////////////////
	buttonRock = new SpriteGo("button");
	buttonRock->SetTexture("graphics/button.png");
	buttonRock->SetOrigin(Origins::TL);
	buttonRock->SetPosition({ -180.f, -350.f });
	AddGo(buttonRock);
	
	buttonWep = new SpriteGo("button");
	buttonWep->SetTexture("graphics/button.png");
	buttonWep->SetOrigin(Origins::TL);
	buttonWep->SetPosition({ -20.f, -350.f });
	AddGo(buttonWep);

	buttonPoop = new SpriteGo("button");
	buttonPoop->SetTexture("graphics/button.png");
	buttonPoop->SetOrigin(Origins::TL);
	buttonPoop->SetPosition({ 140.f, -350.f });
	AddGo(buttonPoop);
	/////////////////
	buttonAFly = new SpriteGo("button");
	buttonAFly->SetTexture("graphics/button.png");
	buttonAFly->SetOrigin(Origins::TL);
	buttonAFly->SetPosition({ -500.f, -300.f });
	AddGo(buttonAFly);

	buttonBFly = new SpriteGo("button");
	buttonBFly->SetTexture("graphics/button.png");
	buttonBFly->SetOrigin(Origins::TL);
	buttonBFly->SetPosition({ -340.f, -300.f });
	AddGo(buttonBFly);

	buttonCharger = new SpriteGo("button");
	buttonCharger->SetTexture("graphics/button.png");
	buttonCharger->SetOrigin(Origins::TL);
	buttonCharger->SetPosition({ -180.f, -300.f });
	AddGo(buttonCharger);

	buttonDip = new SpriteGo("button");
	buttonDip->SetTexture("graphics/button.png");
	buttonDip->SetOrigin(Origins::TL);
	buttonDip->SetPosition({ -20.f, -300.f });
	AddGo(buttonDip);

	buttonDinga = new SpriteGo("button");
	buttonDinga->SetTexture("graphics/button.png");
	buttonDinga->SetOrigin(Origins::TL);
	buttonDinga->SetPosition({ 140.f, -300.f });
	AddGo(buttonDinga);

	buttonObjDelete = new SpriteGo("button");
	buttonObjDelete->SetTexture("graphics/button.png");
	buttonObjDelete->SetOrigin(Origins::TL);
	buttonObjDelete->SetPosition({ -340, 300.f });
	AddGo(buttonObjDelete);
	
	buttonMonsterDelete = new SpriteGo("button");
	buttonMonsterDelete->SetTexture("graphics/button.png");
	buttonMonsterDelete->SetOrigin(Origins::TL);
	buttonMonsterDelete->SetPosition({ -180, 300.f });
	AddGo(buttonMonsterDelete);

	buttonSave = new SpriteGo("button");
	buttonSave->SetTexture("graphics/button.png");
	buttonSave->SetOrigin(Origins::TL);
	buttonSave->SetPosition({ -500.f, 300.f });
	AddGo(buttonSave);

	/////////////////////////////////////////////////
	sf::Font& font = RES_MGR_FONT.Get("fonts/Isaac.ttf");
	FloorButtonText.Set(font, "Floor", 25, sf::Color::Red);
	FloorButtonText.SetOrigin(Origins::TL);
	FloorButtonText.SetPosition({35,0});

	RoomButtonText.Set(font, "Room", 25, sf::Color::Red);
	RoomButtonText.SetOrigin(Origins::TL);
	RoomButtonText.SetPosition({ 205,0 });
	/////////////////////////////
	RockButtonText.Set(font, "Rock", 25, sf::Color::Red);
	RockButtonText.SetOrigin(Origins::TL);
	RockButtonText.SetPosition({ 365,0 });

	WebButtonText.Set(font, "Web", 25, sf::Color::Red);
	WebButtonText.SetOrigin(Origins::TL);
	WebButtonText.SetPosition({ 530,0 });

	PoopButtonText.Set(font, "Poop", 25, sf::Color::Red);
	PoopButtonText.SetOrigin(Origins::TL);
	PoopButtonText.SetPosition({ 685,0 });
	///////////////////////////////

	AFlyButtonText.Set(font, "AttackFly", 25, sf::Color::Red);
	AFlyButtonText.SetOrigin(Origins::TL);
	AFlyButtonText.SetPosition({ 5,55 });

	BFlyButtonText.Set(font, "BoomFly", 25, sf::Color::Red);
	BFlyButtonText.SetOrigin(Origins::TL);
	BFlyButtonText.SetPosition({ 180,55 });

	ChargerButtonText.Set(font, "Charger", 25, sf::Color::Red);
	ChargerButtonText.SetOrigin(Origins::TL);
	ChargerButtonText.SetPosition({ 340,55 });

	DipButtonText.Set(font, "Dip", 25, sf::Color::Red);
	DipButtonText.SetOrigin(Origins::TL);
	DipButtonText.SetPosition({ 530,55 });

	DingaButtonText.Set(font, "Dinga", 25, sf::Color::Red);
	DingaButtonText.SetOrigin(Origins::TL);
	DingaButtonText.SetPosition({ 680,55 });

	///////////////////////////////
	SaveButtonText.Set(font, "Save", 25, sf::Color::Red);
	SaveButtonText.SetOrigin(Origins::MC);
	SaveButtonText.SetPosition({ 75,660 });

	DeleteButtonText.Set(font, "Delete", 25, sf::Color::Red);
	DeleteButtonText.SetOrigin(Origins::MC);
	DeleteButtonText.SetPosition({ 235,660 });

	Scene::Init();
}

std::wstring SceneMapTool::SelectFloor()
{
	wchar_t save[260];
	GetCurrentDirectory(MAX_PATH, save);


	OPENFILENAME ofn;
	wchar_t szFile[260]; 
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL; 
	ofn.lpstrFile = szFile; 
	ofn.lpstrFile[0] = L'\0'; 
	ofn.nMaxFile = sizeof(szFile); 
	ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0"; 
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL; 
	ofn.nMaxFileTitle = 0; 
	ofn.lpstrInitialDir = NULL; 
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		SetCurrentDirectory(save);
		return ofn.lpstrFile;
	}
	else
	{
		SetCurrentDirectory(save);
		return L"";
	}
}

std::wstring SceneMapTool::SelectRoom()
{
	wchar_t save[260];
	GetCurrentDirectory(MAX_PATH, save);

	OPENFILENAME ofn;
	wchar_t szFile[260];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = L'\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		SetCurrentDirectory(save);
		return ofn.lpstrFile;
	}
	else
	{
		SetCurrentDirectory(save);
		return L"";
	}
}

void SceneMapTool::Release()
{
	Scene::Release();

}

void SceneMapTool::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

}

void SceneMapTool::Exit()
{
	Scene::Exit();

}

void SceneMapTool::Update(float dt)
{
	Scene::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneTitle);
	}


	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (buttonFloor->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::wstring filePathW = SelectFloor();
			if (!filePathW.empty())
			{
				std::string filePath = ConvertLPCWSTRToString(filePathW.c_str());
				if (imageFloor.loadFromFile(filePath))
				{
					spriteFloor.setTexture(imageFloor);
					spriteFloor.setPosition(FRAMEWORK.GetWindowSize().x / 2 - imageFloor.getSize().x / 2, FRAMEWORK.GetWindowSize().y / 2 - imageFloor.getSize().y / 2);
					spriteFloor.setColor(sf::Color(255, 255, 255, 50));

					std::string relativePath = ToRelativePath(filePath, fs::current_path().string());
					mapInfo.roomFloorTexId = relativePath;
				}
				else
				{
					std::cerr << "Image could not be loaded." << std::endl;
				}
			}
		}

		if (buttonRoom->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::wstring filePathW = SelectFloor();
			if (!filePathW.empty())
			{
				std::string filePath = ConvertLPCWSTRToString(filePathW.c_str());

				if (imageRoom.loadFromFile(filePath))
				{
					spriteRoom.setTexture(imageRoom);
					spriteRoom.setPosition(FRAMEWORK.GetWindowSize().x / 2 - imageRoom.getSize().x / 2,
						FRAMEWORK.GetWindowSize().y / 2 - imageRoom.getSize().y / 2);
					spriteRoom.setColor(sf::Color(255, 255, 255, 50));

					std::string relativePath = ToRelativePath(filePath, fs::current_path().string());
					mapInfo.roomTexId = relativePath;
				}
				else
				{
					std::cerr << "Image could not be loaded." << std::endl;
				}
			}
		}
		///////////////////// 맵 오브젝트 /////////////////////////////////
		if (buttonRock->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Rock" << std::endl;
			SpriteGo* obj = new SpriteGo("rock");
			obj->SetTexture("graphics/Rock.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			mapObjects.push_back(obj);
		}
		if (buttonWep->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Web" << std::endl;
			SpriteGo* obj = new SpriteGo("web");
			obj->SetTexture("graphics/Web.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			mapObjects.push_back(obj);
		}
		if (buttonPoop->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Poop" << std::endl;
			SpriteGo* obj = new SpriteGo("poop");
			obj->SetTexture("graphics/Poop1.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			mapObjects.push_back(obj);
		}

		//////////////////////몬스터///////////////////////////////////////

		if (buttonAFly->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Attack Fly" << std::endl;
			SpriteGo* obj = new SpriteGo("attackfly");
			obj->SetTexture("graphics/AttackFly1.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			monsterList.push_back(obj);
		}
		if (buttonBFly->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Boom Fly" << std::endl;
			SpriteGo* obj = new SpriteGo("boomfly");
			obj->SetTexture("graphics/BoomFly1.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			monsterList.push_back(obj);
		}
		if (buttonCharger->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Charger" << std::endl;
			SpriteGo* obj = new SpriteGo("charger");
			obj->SetTexture("graphics/Charger1.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			monsterList.push_back(obj);
		}
		if (buttonDip->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Dip" << std::endl;
			SpriteGo* obj = new SpriteGo("dip");
			obj->SetTexture("graphics/Dip1.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			monsterList.push_back(obj);
		}
		if (buttonDinga->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::cout << "Dinga" << std::endl;
			SpriteGo* obj = new SpriteGo("dinga");
			obj->SetTexture("graphics/Dinga1.png");
			obj->SetOrigin(Origins::MC);
			obj->SetPosition({ 0,0 });
			AddGo(obj);
			monsterList.push_back(obj);
		}


		if (buttonSave->GetGlobalBounds().contains(mouseWorldPos))
		{
			SaveMapCSV();
		}
		if (buttonObjDelete->GetGlobalBounds().contains(mouseWorldPos))
		{
			DeleteObj();
		}
		
		if (buttonMonsterDelete->GetGlobalBounds().contains(mouseWorldPos))
		{
			DeleteMonster();
		}

		for (auto& go : mapObjects)
		{
			if (go->GetGlobalBounds().contains(mouseWorldPos))
			{
				selectedObject = go;
				isDragging = true;
				break;
			}
		}
		for (auto& go : monsterList)
		{
			if (go->GetGlobalBounds().contains(mouseWorldPos))
			{
				selectedObject = go;
				isDragging = true;
				break;
			}
		}
	}

	if (isDragging && selectedObject != nullptr)
	{
		if (InputMgr::GetMouseButton(sf::Mouse::Left))
		{
			selectedObject->SetPosition(mouseWorldPos);
		}
		else
		{
			isDragging = false;
			selectedObject = nullptr;
		}
	}
}

void SceneMapTool::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);

}

void SceneMapTool::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);

}

void SceneMapTool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(spriteRoom);
	window.draw(spriteFloor);
	FloorButtonText.Draw(window);
	RoomButtonText.Draw(window);
	SaveButtonText.Draw(window);
	RockButtonText.Draw(window);
	WebButtonText.Draw(window);
	PoopButtonText.Draw(window);
	AFlyButtonText.Draw(window);
	BFlyButtonText.Draw(window);
	ChargerButtonText.Draw(window);
	DipButtonText.Draw(window);
	DingaButtonText.Draw(window);
	DeleteButtonText.Draw(window);
}

void SceneMapTool::SaveMapCSV()
{
	for (auto& obj : mapObjects)
	{
		MapObjectInfo info;
		info.name = obj->name;
		info.objectType = "mapObj";
		info.position.x = obj->GetPosition().x;
		info.position.y = obj->GetPosition().y;

		mapInfo.objectList.push_back(info);
	}

	for (auto& monster : monsterList)
	{
		MonsterInfo info;
		info.name = monster->name;
		info.monsterType = "monster";
		info.position.x = monster->GetPosition().x;
		info.position.y = monster->GetPosition().y;

		mapInfo.monsterList.push_back(info);
	}

	std::string fileName;	// = "map/Test.csv";

	std::cout << "File Name : ";
	std::cin >> fileName;
	std::cout << "File Path : map/" << fileName << ".csv" << std::endl;

	std::string filePath = "map/" + fileName + ".csv";

	mapInfo.SaveToFile(filePath);
}

void SceneMapTool::DeleteObj()
{
	if (!mapObjects.empty()) 
	{
		SpriteGo* lastMapObj = mapObjects.back();
		lastMapObj->SetActive(false);
		mapObjects.pop_back();
		//delete lastMapObj;
	}
	else 
	{
		std::cout << "삭제할 오브젝트가 없습니다." << std::endl;
	}
}

void SceneMapTool::DeleteMonster()
{
	if (!monsterList.empty())
	{
		SpriteGo* lastMonster = monsterList.back();
		lastMonster->SetActive(false);
		monsterList.pop_back();
		//delete lastMonster;
	}
	else
	{
		std::cout << "삭제할 몬스터가 없습니다." << std::endl;
	}
}
