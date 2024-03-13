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

std::string SceneMapTool::ToRelativePath(const std::string& originalPath, const std::string& basePath) {
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

	buttonSave = new SpriteGo("button");
	buttonSave->SetTexture("graphics/button.png");
	buttonSave->SetOrigin(Origins::TL);
	buttonSave->SetPosition({ -500.f, 300.f });
	AddGo(buttonSave);
	
	//buttonObj = new SpriteGo("button");
	//buttonObj->SetTexture("graphics/button.png");
	//buttonObj->SetOrigin(Origins::TL);
	//buttonObj->SetPosition({ -180.f, -350.f });
	//AddGo(buttonObj);



	sf::Font& font = RES_MGR_FONT.Get("fonts/Isaac.ttf");
	FloorButtonText.Set(font, "Floor", 25, sf::Color::Black);
	FloorButtonText.SetOrigin(Origins::MC);
	FloorButtonText.SetPosition({75,10});

	RoomButtonText.Set(font, "Room", 25, sf::Color::Black);
	RoomButtonText.SetOrigin(Origins::MC);
	RoomButtonText.SetPosition({ 235,10 });

	SaveButtonText.Set(font, "Save", 25, sf::Color::Black);
	SaveButtonText.SetOrigin(Origins::MC);
	SaveButtonText.SetPosition({ 75,660 });

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
				if (imageTexture.loadFromFile(filePath)) 
				{
					spriteFloor.setTexture(imageTexture);
					spriteFloor.setPosition(FRAMEWORK.GetWindowSize().x / 2 - imageTexture.getSize().x / 2, FRAMEWORK.GetWindowSize().y / 2 - imageTexture.getSize().y / 2);
					spriteFloor.setColor(sf::Color(255, 255, 255, 128));

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
					spriteRoom.setColor(sf::Color(255, 255, 255, 128));

					std::string relativePath = ToRelativePath(filePath, fs::current_path().string());
					mapInfo.roomTexId = relativePath;
				}
				else
				{
					std::cerr << "Image could not be loaded." << std::endl;
				}
			}
		}

		if (buttonSave->GetGlobalBounds().contains(mouseWorldPos))
		{
			SaveMapCSV();
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
}

void SceneMapTool::SaveMapCSV()
{
	std::cout << "Click Save Button" << std::endl;
	
	std::string filePath = "map/Test.csv";

	mapInfo.SaveToFile(filePath);
}
