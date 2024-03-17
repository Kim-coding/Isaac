#include "pch.h"
#include "UiHud.h"
#include "PlayerIsaac.h"
#include "SceneDev1.h"

UiHud::UiHud(const std::string& name)
	:GameObject(name)
{
}

void UiHud::SetResolution(const sf::Vector2f resolution)
{
}

void UiHud::SetMessage(const std::string& msg)
{
}

void UiHud::SetMessageActive(bool active)
{
}

void UiHud::SetFps(int fps)
{
	textFps.SetString(formatFps + std::to_string(fps));
}

void UiHud::Init()
{
	imgHp.Init();
	textFps.Init();

	float topY = 100.f;
	
	imgHp.SetTexture("graphics/uiHearts1.png");
	imgHp.SetOrigin(Origins::BL);
	imgHp.SetPosition({ 100.f, topY });
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	player = dynamic_cast<PlayerIsaac*>(SCENE_MGR.GetCurrentScene()->FindGo("Isaac"));
}

void UiHud::Update(float dt)
{
	int hp = player->GetHp();
	if (hp <= 0)
	{
		imgHp.SetTexture("graphics/uiHearts7.png");
	}
	else if (hp <= 15)
	{
		imgHp.SetTexture("graphics/uiHearts6.png");
	}
	else if (hp <= 30 )
	{
		imgHp.SetTexture("graphics/uiHearts5.png");
	}
	else if (hp <= 45)
	{
		imgHp.SetTexture("graphics/uiHearts4.png");
	}
	else if (hp <= 60)
	{
		imgHp.SetTexture("graphics/uiHearts3.png");
	}
	else if (hp <= 75)
	{
		imgHp.SetTexture("graphics/uiHearts2.png");
	}
	else
	{
		imgHp.SetTexture("graphics/uiHearts1.png");
	}
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::FixedUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	imgHp.Draw(window);
}
