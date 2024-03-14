#include "pch.h"
#include "SceneIntro.h"
#include "Intro.h"

SceneIntro::SceneIntro(SceneIds id)
	:Scene(id)
{
}

SceneIntro::~SceneIntro()
{
}

void SceneIntro::Init()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	AddGo(new Intro());
	Scene::Init();
}

void SceneIntro::Release()
{
	Scene::Release();
}

void SceneIntro::Enter()
{
	Scene::Enter();
}

void SceneIntro::Exit()
{
	Scene::Exit();
}

void SceneIntro::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev1);
	}
	if(InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneMapTool);
	}
}
