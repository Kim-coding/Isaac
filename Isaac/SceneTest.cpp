#include "pch.h"
#include "SceneTest.h"
#include "SpriteGo.h"


SceneTest::SceneTest(SceneIds id)
	:Scene(id)
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
	mapinfo.LoadFromFile("animators/Map.csv");

	SpriteGo* spriteGoBackground = new SpriteGo("StartRoom");
	spriteGoBackground->SetTexture(mapinfo.roomTexId);
	spriteGoBackground->SetOrigin(Origins::MC);
	spriteGoBackground->SetPosition({ 0.f, 0.f });
	spriteGoBackground->sortLayer = -1;
	AddGo(spriteGoBackground);

	SpriteGo* spriteGoBackgroundfloor = new SpriteGo("StartRoomFloor");
	spriteGoBackgroundfloor->SetTexture(mapinfo.roomFloorTexId);
	spriteGoBackgroundfloor->SetOrigin(Origins::MC);
	spriteGoBackgroundfloor->SetPosition({ 0.f, 0.f });
	spriteGoBackgroundfloor->sortLayer = -1;
	AddGo(spriteGoBackgroundfloor);
}

void SceneTest::Release()
{
	Scene::Release();
}

void SceneTest::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
}

void SceneTest::Exit()
{
	Scene::Exit();
}

void SceneTest::Update(float dt)
{
	Scene::Update(dt);

}

void SceneTest::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneTest::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
