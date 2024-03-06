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
	rect = Utils::ResizeRect(rect, spriteGoBackground->GetScale());

	return rect.contains(point);
}

sf::Vector2f SceneDev1::ClampByMap(const sf::Vector2f point)
{
	sf::FloatRect rect = spriteGoBackgroundfloor->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, spriteGoBackgroundfloor->GetScale());

	return Utils::Clamp(point, rect);
}

void SceneDev1::Init()
{
	spriteGoBackground = new SpriteGo("StartRoom");
	spriteGoBackground->SetTexture("graphics/StartRoom.png");
	spriteGoBackground->SetOrigin(Origins::MC);
	spriteGoBackground->SetScale({2,2});
	spriteGoBackground->SetPosition({ 0.f,0.f });
	AddGo(spriteGoBackground);

	spriteGoBackgroundfloor = new SpriteGo("StartRoomFloor");
	spriteGoBackgroundfloor->SetTexture("graphics/StartRoomFloor.png");
	spriteGoBackgroundfloor->SetOrigin(Origins::MC);
	spriteGoBackgroundfloor->SetScale({ 2,2 });
	spriteGoBackgroundfloor->SetPosition({ 0.f,0.f });
	AddGo(spriteGoBackgroundfloor);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

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

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))  //모든 몬스터 처치 + 문과 충돌 시 ~
	//{
	//	SceneMgr::Instance().ChangeScene(SceneIds::SceneDev2);
	//}
}
