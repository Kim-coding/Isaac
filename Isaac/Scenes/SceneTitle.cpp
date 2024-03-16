#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	SOUND_MGR.PlayBgm("sound/7689.mp3");

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	spriteTitle = new SpriteGo("StartRoom");
	spriteTitle->SetTexture("graphics/isaacTitle.png");
	spriteTitle->SetOrigin(Origins::MC);
	spriteTitle->SetPosition({ 0.f,0.f });
	AddGo(spriteTitle);

	Scene::Init();
}

void SceneTitle::Release()
{
	Scene::Release();
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	timer += dt;
	if (timer > changSceneTime || InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneIntro);
		timer = 0;
	}
}
