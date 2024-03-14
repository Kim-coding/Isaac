#include "pch.h"
#include "SceneIntro.h"

SceneIntro::SceneIntro(SceneIds id)
	:Scene(id)
{
}

SceneIntro::~SceneIntro()
{
}

void SceneIntro::Init()
{
}

void SceneIntro::Release()
{
}

void SceneIntro::Enter()
{
}

void SceneIntro::Exit()
{
}

void SceneIntro::Update(float dt)
{

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev1);
	}
	if(InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneMapTool);
	}
}

void SceneIntro::Draw(sf::RenderWindow& window)
{
}
