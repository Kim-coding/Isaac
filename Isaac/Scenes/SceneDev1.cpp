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
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	//방
	spriteGoBackground = new SpriteGo("StartRoom");
	spriteGoBackground->SetTexture("graphics/StartRoom.png");
	spriteGoBackground->SetOrigin(Origins::MC);
	spriteGoBackground->SetScale({2,2});
	spriteGoBackground->SetPosition({ 0.f, 0.f });
	//spriteGoBackground->SetRotation(90);
	AddGo(spriteGoBackground);

	spriteGoBackgroundfloor = new SpriteGo("StartRoomFloor");
	spriteGoBackgroundfloor->SetTexture("graphics/StartRoomFloor.png");
	spriteGoBackgroundfloor->SetOrigin(Origins::MC);
	spriteGoBackgroundfloor->SetScale({ 2, 2 });
	spriteGoBackgroundfloor->SetPosition({ 0.f, 0.f });
	//spriteGoBackgroundfloor->SetRotation(90);
	AddGo(spriteGoBackgroundfloor);
	
	regularRoom = new SpriteGo("RegularRoom");
	regularRoom->SetTexture("graphics/Catacombs.png");
	regularRoom->SetOrigin(Origins::MC);
	regularRoom->SetScale({ 2, 2 });
	regularRoom->SetPosition({1000.f,0.f});
	AddGo(regularRoom);


	//문 생성  :  어떤 방향의 문으로 들어갔는 지 다음 방에게 넘겨 줘야함.
	//문 위치  :  바닥 각 변의 중앙 값
	int rand = Utils::RandomRange(2, 5);  //2, 3 ,4 : 문의 개수
	switch (rand)
	{
	case 2:
		door = new SpriteGo("door");
		//door->SetTexture();
		door->SetOrigin(Origins::BC);
		//door->SetPosition();        

		break;
	case 3:

		break;
	case 4:

		break;
	}


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
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))  
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneTitle);
	}
}
