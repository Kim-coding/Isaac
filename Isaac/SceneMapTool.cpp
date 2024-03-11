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
	// Determine the length of the converted string 
	int strLength
		= WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1,
			nullptr, 0, nullptr, nullptr);

	// Create a std::string with the determined length 
	std::string str(strLength, 0);

	// Perform the conversion from LPCWSTR to std::string 
	WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, &str[0],
		strLength, nullptr, nullptr);

	// Return the converted std::string 
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

	/*sf::Font& font = RES_MGR_FONT.Get("fonts/Isaac.ttf");
	button.Set(font, "BackGround", 30, sf::Color::White);
	button.SetOrigin(Origins::TL);
	button.SetPosition({ 5, 5 });*/




	
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

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneTitle);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) 
	{
		std::wstring filePathW = SelectFile();
		if (!filePathW.empty()) 
		{
			std::string filePath = ConvertLPCWSTRToString(filePathW.c_str()); // 경로를 std::string으로 변환

			if (imageTexture.loadFromFile(filePath)) 
			{ 
				imageSprite.setTexture(imageTexture);
				imageSprite.setPosition(FRAMEWORK.GetWindowSize().x / 2 - imageTexture.getSize().x / 2,
					FRAMEWORK.GetWindowSize().y / 2 - imageTexture.getSize().y / 2);
			}
			else 
			{
				std::cerr << "Image could not be loaded." << std::endl;
			}
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
	button.Draw(window);
	window.draw(imageSprite);
}
