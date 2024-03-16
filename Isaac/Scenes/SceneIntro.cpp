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

	backGround = new SpriteGo("BackGround");
	backGround->SetTexture("graphics/IntroBackground.png");
	backGround->SetOrigin(Origins::MC);
	backGround->SetPosition({0,0});
	backGround->sortLayer = -1;
	AddGo(backGround);
	sf::Font& font = RES_MGR_FONT.Get("fonts/Isaac.ttf");

	startText.Set(font, "1. Start", 60, sf::Color::Black);
	startText.SetOrigin(Origins::MC);
	startText.SetPosition({ centerPos.x, centerPos.y + 80.f });

	mapEditor.Set(font, "2. Map Editor", 60, sf::Color::Black);
	mapEditor.SetOrigin(Origins::MC);
	mapEditor.SetPosition({ centerPos.x, centerPos.y + 150.f });

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
	SOUND_MGR.PlayBgm("sound/Intro.mp3",true);
}

void SceneIntro::Exit()
{
	Scene::Exit();
}

void SceneIntro::Update(float dt)
{
	Scene::Update(dt);
	
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SOUND_MGR.StopBgm();
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev1);
	}
	if(InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SOUND_MGR.StopBgm();
		SceneMgr::Instance().ChangeScene(SceneIds::SceneMapTool);
	}
}

void SceneIntro::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	startText.Draw(window);
	mapEditor.Draw(window);
}
