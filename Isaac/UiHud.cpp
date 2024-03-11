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

void UiHud::SetHp(int hp, int max)
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
	imgHp2.Init();
	textFps.Init();

	float topY = 100.f;
	
	
	imgHp.SetTexture("graphics/FullHp.png");
	imgHp.SetOrigin(Origins::BL);
	imgHp.SetPosition({ 100.f, topY });

	imgHp2.SetTexture("graphics/HalfHp.png");
	imgHp2.SetOrigin(Origins::BL);
	imgHp2.SetPosition({ 100.f + 25, topY });
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
}

void UiHud::Update(float dt)
{
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
	imgHp2.Draw(window);

}
