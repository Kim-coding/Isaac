#include "pch.h"
#include "SceneMapTool.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iostream>

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



	button = new SpriteGo("button");
	button->SetTexture("graphics/button.png");
	button->SetOrigin(Origins::TL);
	button->SetPosition({ -500.f, -350.f });
	button->sortLayer = -1;
	AddGo(button);

	sf::Font& font = RES_MGR_FONT.Get("fonts/Isaac.ttf");
	buttonText.Set(font, "background", 25, sf::Color::Blue);
	buttonText.SetOrigin(Origins::TL);
	buttonText.SetPosition({ 0,0 });



	LoadMapFromCSV(L"animators/Map.csv");
	Scene::Init();
}

std::wstring SceneMapTool::SelectFile()
{
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
		return ofn.lpstrFile;
	}
	else
	{
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


	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		if (button->GetGlobalBounds().contains(mouseWorldPos))
		{
			std::wstring filePathW = SelectFile();
			if (!filePathW.empty())
			{
				std::string filePath = ConvertLPCWSTRToString(filePathW.c_str());

				if (imageTexture.loadFromFile(filePath))
				{
					imageSprite.setTexture(imageTexture);
					imageSprite.setPosition(FRAMEWORK.GetWindowSize().x / 2 - imageTexture.getSize().x / 2,
						FRAMEWORK.GetWindowSize().y / 2 - imageTexture.getSize().y / 2);
					imageSprite.setColor(sf::Color(255, 255, 255, 128));
				}
				else
				{
					std::cerr << "Image could not be loaded." << std::endl;
				}
			}
		}
	}
}

void SceneMapTool::LoadMapFromCSV(const std::wstring& filePath)
{
	std::wifstream file(filePath);
	std::wstring line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::wistringstream iss(line);
		std::wstring type, imagePath;
		float x, y;

		std::getline(iss, type, L',');
		std::getline(iss, imagePath, L',');
		iss >> x >>  y;

		if (type == L"Room")
		{
			auto room = new SpriteGo("");
			room->SetTexture(ConvertLPCWSTRToString(imagePath.c_str()));
			room->SetOrigin(Origins::MC);
			room->SetPosition({ x, y });
			AddGo(room);
		}
		if (type == L"RoomFloor")
		{
			auto roomFloor = new SpriteGo("");
			roomFloor->SetTexture(ConvertLPCWSTRToString(imagePath.c_str()));
			roomFloor->SetOrigin(Origins::MC);
			roomFloor->SetPosition({ x, y });
			AddGo(roomFloor);
		}
		if (type == L"rock")
		{
			auto rock = new SpriteGo("");
			rock->SetTexture(ConvertLPCWSTRToString(imagePath.c_str()));
			rock->SetOrigin(Origins::MC);
			rock->SetPosition({ x, y });
			AddGo(rock);
		}
		if (type == L"monster")
		{
			auto monster = new SpriteGo("monster");
			monster->SetTexture(ConvertLPCWSTRToString(imagePath.c_str()));
			monster->SetPosition({ x, y });
			AddGo(monster);
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
	window.draw(imageSprite);
	buttonText.Draw(window);
}
